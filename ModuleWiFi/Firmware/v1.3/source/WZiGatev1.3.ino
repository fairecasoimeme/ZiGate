/*
  ESP8266 WZiGate v1.30
 */

#define USE_WDT

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include "FS.h"

// application config

struct ConfigSettingsStruct
{
    String ssid;
    String password;
    String ipAddress;
    String ipMask;
    String ipGW;
    int tcpListenPort=9999;
    
};
ConfigSettingsStruct ConfigSettings;
bool configOK=false;

String modeWiFi="STA";

#define BAUD_RATE 115200

#define BUFFER_SIZE 128
#define VERSION "1.30"

ESP8266WebServer serverWeb(80);
char serverIndex[1024];
char serverIndexUpdate[512];
char serverIndexReboot[256];
const char* Style = "";


WiFiServer server(ConfigSettings.tcpListenPort);

IPAddress parse_ip_address(const char *str) {
    IPAddress result;    
    int index = 0;

    result[0] = 0;
    while (*str) {
        if (isdigit((unsigned char)*str)) {
            result[index] *= 10;
            result[index] += *str - '0';
        } else {
            index++;
            if(index<4) {
              result[index] = 0;
            }
        }
        str++;
    }
    
    return result;
}

bool loadConfig() {
  File configFile = SPIFFS.open("/config.json", "r");
  if (!configFile) {
    return false;
  }

  size_t size = configFile.size();
  if (size > 1024) {
    return false;
  }

  // Allocate a buffer to store contents of the file.
  std::unique_ptr<char[]> buf(new char[size]);

  // We don't use String here because ArduinoJson library requires the input
  // buffer to be mutable. If you don't use ArduinoJson, you may as well
  // use configFile.readString instead.
  configFile.readBytes(buf.get(), size);

  StaticJsonBuffer<512> jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(buf.get());

  if (!json.success()) {
    return false;
  }

    char ssid_[30];
    strcpy(ssid_, json["ssid"]);
    ConfigSettings.ssid = String(ssid_);
    char pass_[30];
    strcpy(pass_, json["pass"]);
    ConfigSettings.password = String(pass_);
    char ip_[30];
    strcpy(ip_, json["ip"]);
    ConfigSettings.ipAddress = String(ip_);
    char mask_[30];
    strcpy(mask_, json["mask"]);
    ConfigSettings.ipMask = String(mask_);
    char gw_[30];
    strcpy(gw_, json["gw"]);
    ConfigSettings.ipGW = String(gw_);

   
    return true;
}


void setupWifiAP()
{
  WiFi.mode(WIFI_AP);
  WiFi.disconnect();
  
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
                 String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  String AP_NameString = "ZIGATE-" + macID;

  char AP_NameChar[AP_NameString.length() + 1];
  memset(AP_NameChar, 0, AP_NameString.length() + 1);

  for (int i=0; i<AP_NameString.length(); i++)
    AP_NameChar[i] = AP_NameString.charAt(i);

  String WIFIPASSSTR = "admin"+macID;
  char WIFIPASS[WIFIPASSSTR.length()+1];
  memset(WIFIPASS,0,WIFIPASSSTR.length()+1);
  for (int i=0; i<WIFIPASSSTR.length(); i++)
    WIFIPASS[i] = WIFIPASSSTR.charAt(i);

  WiFi.softAP(AP_NameChar,WIFIPASS );
}

bool setupSTAWifi() {
  
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

    WiFi.begin(ConfigSettings.ssid.c_str(), ConfigSettings.password.c_str());

  IPAddress ip_address = parse_ip_address(ConfigSettings.ipAddress.c_str());
  IPAddress gateway_address = parse_ip_address(ConfigSettings.ipGW.c_str());
  IPAddress netmask = parse_ip_address(ConfigSettings.ipMask.c_str());
  
  WiFi.config(ip_address, gateway_address, netmask);

  int countDelay=50;
  while (WiFi.status() != WL_CONNECTED) {
#ifdef USE_WDT
    wdt_reset();
#endif
    countDelay--;
    if (countDelay==0)
    {
      return false;
    }
    delay(250);
  }
  return true;
}

void handleSaveConfig()
{
  if(!serverWeb.hasArg("WIFISSID")) {serverWeb.send(500, "text/plain", "BAD ARGS"); return;}

   String StringConfig;
    String ssid = serverWeb.arg("WIFISSID");
    String pass = serverWeb.arg("WIFIpassword");
    String ipAddress = serverWeb.arg("ipAddress");
    String ipMask = serverWeb.arg("ipMask");
    String ipGW = serverWeb.arg("ipGW");
    String tcpListenPort = serverWeb.arg("tcpListenPort");

   StringConfig = "{\"ssid\":\""+ssid+"\",\"pass\":\""+pass+"\",\"ip\":\""+ipAddress+"\",\"mask\":\""+ipMask+"\",\"gw\":\""+ipGW+"\",\"tcpListenPort\":\""+tcpListenPort+"\"}";    
   StaticJsonBuffer<512> jsonBuffer;
   JsonObject& json = jsonBuffer.parseObject(StringConfig);
 
   File configFile = SPIFFS.open("/config.json", "w");
   if (!configFile) {
   }else{
     json.printTo(configFile);
   }
  serverWeb.send(200, "text/html", "Save config OK ! <br><form method='GET' action='reboot'><input type='submit' name='reboot' value='Reboot'></form>");
  
 
}

void setup(void)
{  
#ifdef USE_WDT
  wdt_enable(1000);
#endif

  
  Serial.begin(115200);
  Serial.swap();
  

  if (!SPIFFS.begin()) {
    
    return;
  }
  
  if (!loadConfig()) {
    
  } else {
    configOK=true;
   
  }

  if (configOK)
  {
    if (!setupSTAWifi())
    {
      setupWifiAP();
      modeWiFi="AP";
    }
       
  }else{
    setupWifiAP();
    modeWiFi="AP";
  }

sprintf(serverIndex,"<h1>ZiGate WiFi Config v%s</h1><form method='POST' action='save'><br>SSID : <br><input type='text' name='WIFISSID' value='%s'><br>Password : <br><input type='password' name='WIFIpassword' value=''><br>@IP : <br><input type='text' name='ipAddress' value='%s'><br>@Mask : <br><input type='text' name='ipMask' value='%s'><br>@Gateway : <br><input type='text' name='ipGW' value='%s'><br>Server Port : <br>%d<br><br><input type='submit' name='save' value='Save'></form><br><form method='GET' action='/reboot'><input type='submit' name='reboot' value='Reboot'></form><br><br><a href='/update'>Update Firmware</a>",VERSION,ConfigSettings.ssid.c_str(),ConfigSettings.ipAddress.c_str(),ConfigSettings.ipMask.c_str(),ConfigSettings.ipGW.c_str(),ConfigSettings.tcpListenPort);
sprintf(serverIndexUpdate,"<h1>ZiGate WiFi Config v%s</h1><h2>Update Firmware</h2><form method='POST' action='/updateFile' enctype='multipart/form-data'><input type='file' name='update'><br><br><input type='submit' value='Update' onclick=\"document.getElementById('load').innerHTML='Loading ...'\"><div id='load'></div></form>",VERSION);



  
  
  serverWeb.on("/", HTTP_GET, [](){
        serverWeb.sendHeader("Connection", "close");
        serverWeb.send(200, "text/html", strcat(serverIndex,Style));
  });
  serverWeb.on("/update", HTTP_GET, [](){
        serverWeb.sendHeader("Connection", "close");
        serverWeb.send(200, "text/html", strcat(serverIndexUpdate,Style));
  });
  serverWeb.on("/reboot", HTTP_GET, [](){
        loadConfig();
        serverWeb.sendHeader("Connection", "close");
        char rebootPage[1024];
        sprintf(rebootPage,"<html><body onload=\"startTime()\">Rebooting ...<br><div id='time'></div><script language='javascript'> var s =20; function startTime() { if (s==0){window.location.href='http://%s/';} s = checkTime(s); if(s>0){ s=s-1};   document.getElementById(\"time\").innerHTML =  s +' sec';  var t = setTimeout(function(){ startTime() }, 1000);} function checkTime(i) {  if (i < 10) { i = '0' + i;  } return i;}</script></body></html>",ConfigSettings.ipAddress.c_str());
        serverWeb.send(200, "text/html", rebootPage);
        ESP.restart();
  });
  serverWeb.on("/updateFile", HTTP_POST, [](){
      loadConfig();
      serverWeb.sendHeader("Connection", "close");
      char rebootPage[1024];
      sprintf(rebootPage,"<html><body onload=\"startTime()\">Update Success ... Rebooting ...<br><div id='time'></div><script language='javascript'> var s =20; function startTime() { if (s==0){window.location.href='http://%s/';} s = checkTime(s); if(s>0){ s=s-1};  s = checkTime(s); document.getElementById(\"time\").innerHTML =  s +' sec';  var t = setTimeout(function(){ startTime() }, 1000);} function checkTime(i) {  if (i < 10) { i = '0' + i;  } return i;}</script></body></html>",ConfigSettings.ipAddress.c_str());
      if (Update.hasError())
      {
        serverWeb.send(200, "text/html", "Update Fail");
      }else{
        serverWeb.send(200, "text/html", rebootPage);
      }
      ESP.restart();
    },[](){
      HTTPUpload& upload = serverWeb.upload();
      if(upload.status == UPLOAD_FILE_START){
        
        WiFiUDP::stopAll();
        
        uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
        if(!Update.begin(maxSketchSpace)){//start with max available size
          Update.printError(Serial);
        }
      } else if(upload.status == UPLOAD_FILE_WRITE){
        if(Update.write(upload.buf, upload.currentSize) != upload.currentSize){
          Update.printError(Serial);
        }
      } else if(upload.status == UPLOAD_FILE_END){
        if(Update.end(true)){ //true to set the size to the current progress
         
        } else {
          Update.printError(Serial);
        }
      }
      yield();
  });
  serverWeb.on("/save", HTTP_POST, handleSaveConfig);

  serverWeb.begin();
  server.begin();
}

WiFiClient client;

void loop(void)
{
  size_t bytes_read;
  uint8_t net_buf[BUFFER_SIZE];
  uint8_t serial_buf[BUFFER_SIZE];
  
#ifdef USE_WDT
  wdt_reset();
#endif
  serverWeb.handleClient();
  if (modeWiFi=="STA")
  {
    if(WiFi.status() != WL_CONNECTED) {
      // we've lost the connection, so we need to reconnect
      if(client) {
        client.stop();
      }
      setupSTAWifi();
    }
  }
  
  // Check if a client has connected
  if (!client) {
    // eat any bytes in the swSer buffer as there is nothing to see them
    while(Serial.available()) {
      Serial.read();
    }
      
    client = server.available();
    if(!client) {      

      return;
    }

  }
#define min(a,b) ((a)<(b)?(a):(b))
  if(client.connected()) {
    // check the network for any bytes to send to the swSer
    int count = client.available();
    if(count > 0) {      
       
      bytes_read = client.read(net_buf, min(count, BUFFER_SIZE));
      Serial.write(net_buf, bytes_read);
      Serial.flush();
    }
    
    // now check the swSer for any bytes to send to the network
    bytes_read = 0;
    while(Serial.available() && bytes_read < BUFFER_SIZE) {
      serial_buf[bytes_read] = Serial.read();
      bytes_read++;
    }
    
    if(bytes_read > 0) {  
      client.write((const uint8_t*)serial_buf, bytes_read);
      client.flush();
    }
  } else {
      client.stop();
  }
}


