cmake_minimum_required(VERSION 3.13...3.27)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
SET(PICO_SDK_FETCH_FROM_GIT ON)
SET(PICOTOOL_FETCH_FROM_GIT_PATH ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    INCLUDE(${picoVscode})
endif()

SET(PICO_DISASM_OBJDUMP_ARGS "-Sg")
set(PICO_BOARD pico CACHE STRING "Board type")

INCLUDE(cmake/pico_sdk_import.cmake)

PROJECT(PicoGraphicVisual CXX C ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# initialize the Raspberry Pi Pico SDK
PICO_SDK_INIT()

##################################################################################
# SET compiler options for build types
##################################################################################
IF(CMAKE_BUILD_TYPE MATCHES Release)
   SET(CMAKE_C_FLAGS_RELEASE "-Os")
   SET(CMAKE_CXX_FLAGS_RELEASE "-Os")
ENDIF(CMAKE_BUILD_TYPE MATCHES Release)

IF(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
   SET(CMAKE_C_FLAGS_RELWITHDEBINFO "-Os -g3") 
   SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Os -g3")
ENDIF(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)

IF(CMAKE_BUILD_TYPE MATCHES Debug)
   SET(CMAKE_C_FLAGS_DEBUG "-O0 -g3")
   SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")
ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)


##############################
#
##############################
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/firmware)
