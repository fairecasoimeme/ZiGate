# Installation des sources ZiGate

Suivre les instructions pour installer la plateforme de développement NXP beyond studio:
https://www.nxp.com/docs/en/user-guide/JN-UG-3098.pdf

Télécharger les sources dans la partie "release":
https://github.com/fairecasoimeme/ZiGate/releases

1- Dézipper et copier le sdk dans <chemin_nxp_beyond_studio>/NXP/bstudio_nxp/sdk/JN-SW-4170

2- Dézipper et copier le code source dans <chemin_nxp_beyond_studio>/NXP/bstudio_nxp/workspace/ZiGate

3- Exécuter Beyond studio puis  File --> Import --> Existing Project into workspace 

4- Sélectionner ZiGate et valider

 
# Compiling firmware from sources

## Windows

Follow the instructions to install the NXP beyond studio development platform:
https://www.nxp.com/docs/en/user-guide/JN-UG-3098.pdf

Download the sources in the "release" section:
https://github.com/fairecasoimeme/ZiGate/releases

1. Unzip and copy the SDK in `<path_nxp_beyond_studio> / NXP / bstudio_nxp / sdk / JN-SW-4170`
2. Unzip and copy the source code to `<path_nxp_beyond_studio> / NXP / bstudio_nxp / workspace / ZiGate`
3. Run Beyond studio then `File -> Import -> Existing Project into workspace`
4. Select ZiGate and confirm

## Linux

#### Requirements:

- python3 or python2.7
- `pip3 install xmltodict` (or `pip install xmltodict` for python2)


Download the toolchain for jn51XX processor from 
https://github.com/openlumi/BA2-toolchain/releases/download/20201219/ba-toolchain-20201219.tar.bz2

For non-amd64 architectures or other dependencies, one can build the toolchain
from sources: https://github.com/alephsecurity/BA2-toolchain

The firmware can then be compiled via `make`:

```shell
cd ZiGate/ModuleRadio/Firmware/src/ZiGate/Build/ZigbeeNodeControlBridge
make TOOLCHAIN_PATH=ba-toolchain \
     TOOL_COMMON_BASE_DIR=<path to folder containing ba-toolchain>
```

This will build `ZigbeeNodeControlBridge_JN5169_COORDINATOR_1000000.bin` in 
`ModuleRadio/Firmware/src/ZiGate/Build/ZigbeeNodeControlBridge` directory.

To build for the `JN5168` platform, change baud rate, or add debugging, a number of
build arguments may be supplied to do so. For instance, to receive debug messages via 
`LogMessage [0x8001]` message types from the coordinator, build for the `JN5168` chip and
run at a baud rate of 115200 configured for a 200-device network with a stack size of
5300 and chip PDM managed by the application host:

```shell
#!/usr/bin/env sh
make TOOLCHAIN_PATH=ba-toolchain \
     TOOL_COMMON_BASE_DIR=<path to folder containing ba-toolchain> \
     BAUD=115200 \  # Operating baud rate
     JENNIC_CHIP=JN5168 \  # Target chipset
     TRACE=1 \  # Log debug level
     DEBUG=UART0 \  # Log debug messages to UART0
     STACK_SIZE=5300  \  # Stack size in bytes - must be lower than default 6kb for large networks
     PDM_BUILD_TYPE=_NONE \  # Indicates that host application is responsible for managing PDM data
     PYTHON=/usr/bin/python2.7 \  # Used to specify a custom Python installation
     VERSION=0x0003031e \  # # Software release version
     SW_BUILD_ID=fabd414e \  # Software build ID; usually a Git commit hash.
     HARDWARE_VERSION=00000001  \  # Hardware release version ID
     MANUFACTURER_NAME=Nimbus9  \  # Manufacturer Name
     MANUFACTURER_CODE=0000  \  # Manufacturer ZigBee ID
```

All of the above build args save for `TOOLCHAIN_PATH` and `TOOL_COMMON_BASE` are optional.
