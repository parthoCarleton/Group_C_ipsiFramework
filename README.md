# Inter Process Service Interface- IPSI framework
IPSI framework is a library that allows multiple applications to connect and perform a service request. This framework abstracts the complex low-level system’s communication protocol by revealing a simplified service interface that can be used by the applications to invoke service requests to other applications.
## Product
**libipsi.so** - is our product that can be found in ipsi/bin
## Dependencies
Our product exclusively provide functionality under Operating System with Linux Kernel environment that has Dbus component. 
## Authors
* Partho Ghosal -     partho.ghosal@cmail.carleton.ca
* Ashwini Upasani -   ashwini.upasani@cmail.carleton.ca
* Deepti Guruprasad-  deeptiguruprasad@cmail.carleton.ca
* Rajdeep Virdi -     rajdeepvirdi@cmail.carleton.ca

## Usability
It is recommended for the new user to run the usability steps in **freshly installed Ubuntu 20.04 LTS system.**

Clone this project using command
```bash
git clone https://github.com/parthoCarleton/Group_C_ipsiFramework.git
```
To familiarize with what this project has to offer follow the below steps 
```bash
cd Group_C_ipsiFramework
sh runIPSI.sh
```
## File Structure
Project file Structure description
```
|── demo                            -> Demo Application
│   ├── Controller                  -> Controller - Service Requester Application Folder 
│   │   ├── bin                     -> Binary of Controller Application
│   │   │   └── Controller
│   │   ├── inc                     -> Controller Application include folder
│   │   │   └── controllerApp.hpp   -> Controller Application header file
│   │   ├── Makefile                -> Makefile to build Contorller Application
│   │   ├── run.sh                  -> Script to run Controller Application
│   │   └── src                     -> Source folder 
│   │       └── controllerApp.cpp   -> C++ Controller application source file 
│   ├── runDemo.sh                  -> Run All the demo Applications in Xterm 
│   ├── Service1                    -> Service1 - Service Provider Demo Application Folder
│   │   ├── bin                     -> Binary of Service 1 Application
│   │   │   └── Service1
│   │   ├── inc                     -> Service 1 Application include folder
│   │   │   └── service1App.hpp     -> Service 1 Application header file
│   │   ├── Makefile                -> Makefile to build Service 1 Application
│   │   ├── media                   -> Test video that will be played by Service 1 application
│   │   │   └── test.mp4            -> Test Video File
│   │   ├── run.sh                  -> Script to run Service 1 Application
│   │   └── src                     -> Source folder
│   │       └── service1App.cpp     -> C++ Service 1 Application source file
│   └── Service2                    -> Service2 - Service Provider Demo Application Folder
│       ├── bin                     -> Binary of Service 2 Application
│       │   └── Service2
│       ├── inc                     -> Service 2 Application include folder
│       │   └── service2App.hpp     -> Service 2 Application header file
│       ├── Makefile                -> Makefile to build Service 2 Application
│       ├── media                   -> Test video that will be played by Service 2 application
│       │   └── test.mp4            -> Test Video File
│       ├── run.sh                  -> Script to run Service 1 Application
│       └── src                     -> Source folder
│           └── service2App.cpp     -> C++ Service 2 Application source file
├── ipsi                            -> Inter Process Service Interface- IPSI framework folder
│   ├── bin                         -> Shared library folder
│   │   └── libipsi.so              -> IPSI product
│   ├── inc                         -> IPSI include folder
│   │   └── ipsi.h                  -> IPSI header file.
│   ├── Makefile                    -> Build IPSI library
│   ├── obj                         -> Pre-compilation directory for building shared library
│   │   └── libipsi.o               -> IPSI object file.
│   └── src                         -> IPSI source folder
│       └── ipsi.c                  -> C IPSI source file
├── ipsiSetup                       -> Pre-Environment Setup Folder
│   └── ipsiEnvSetup.sh             -> IPSI setup Script
├── ipsiTest                        -> IPSI unit test folder
│   ├── runUT.sh                    -> Run Unit test cases to test IPSI source file and show line coverage
│   └── ut_test                     -> Folder that contains all the Unit test cases.
│       ├── Makefile                -> Build all the test cases and generate executable
│       ├── stub_UT.c               -> Stub file that will stub out DBUS API
│       ├── unitTest_ipsiConnectionType_UT.c -> Unit Test case strategy 1
│       ├── unitTest_ipsiListen_UT.c         -> Unit Test case strategy 2
│       ├── unitTest_ipsiMethodCall_UT.c     -> Unit Test case strategy 3
│       ├── unitTest_ipsiRegisterFunction_UT.c -> Unit Test case strategy 4
│       ├── unitTest_isCaller_UT.c            -> Unit Test case strategy 5
│       ├── unitTest_isServer_UT.c            -> Unit Test case strategy 6
│       └── UT_IPSI_UT.hpp
├── README.md                               -> Contains the Project Description 
└── runIPSI.sh                              -> Greeting Page- single point to access all the project features.

```
