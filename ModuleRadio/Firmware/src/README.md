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

Then you can build the firmware:

```shell
cd ZiGate/ModuleRadio/Firmware/src/ZiGate/Build/ZigbeeNodeControlBridge
make TOOLCHAIN_PATH=ba-toolchain TOOL_COMMON_BASE_DIR=<path to folder containing ba-toolchain>
```

This will build `ZigbeeNodeControlBridge_JN5169_COORDINATOR_1000000.bin` in 
`ModuleRadio/Firmware/src/ZiGate/Build/ZigbeeNodeControlBridge` directory.

Also, you can use `BAUD` and `JENNIC_CHIP` parameters to build a firmware with 
another baudrate and chip, e.g.

```shell
make BAUD=115200 JENNIC_CHIP=JN5168 JENNIC_CHIP_FAMILY=JN516x
```

To provide a path to your python distribution (e.g., a `virtualenv`) you can pass the `PYTHON`
parameter to `make`:

```shell
make PYTHON=/usr/bin/python2.7
```
