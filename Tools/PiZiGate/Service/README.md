## Script as service

With update-rc.local
* Copy PiZigate in /etc/init.d
* Edit /etc/rc.local and add 
	* /etc/init.d/PiZigate start (before "exit 0") 
