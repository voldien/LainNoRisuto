cmake_minimum_required(VERSION 2.8)

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../cmake" )

SET(AVR_UPLOADTOOL avrdude)
#SET(AVR_PROGRAMMER arduino) # Program Arduino Uno Board
SET(AVR_PROGRAMMER usbasp) # USBASP Programmer
#SET(AVR_PROGRAMMER avrisp) # Using Arduino Uno as Programmer
#SET(AVR_PROGRAMMER stk500v1)
SET(AVR_UPLOADTOOL_PORT /dev/ttyUSB0)
#SET(AVR_UPLOADTOOL_PORT /dev/ttyACM0)
#SET(AVR_UPLOADTOOL_BAUDRATE 125kHz)
SET(AVR_UPLOADTOOL_OPTIONS )


#SET(AVR_MCU attiny11) #
SET(AVR_MCU attiny13a) #
#SET(AVR_MCU attiny212) #
#SET(AVR_MCU attiny25) #
#SET(AVR_MCU atmega328p) #

# AVR and fuses needs to be SET
# Atmega328P Fuses
#SET(AVR_L_FUSE 0xc3)
#SET(AVR_H_FUSE 0xd9)

# Attiny13A Fuses
SET(AVR_L_FUSE 0x6A)
SET(AVR_H_FUSE 0xFF)

INCLUDE(generic-gcc-avr)
avr_generate_fixed_targets()

PROJECT(TinyBlink)

##################################################################################
# status messages
##################################################################################
MESSAGE(STATUS "Current uploadtool is: ${AVR_UPLOADTOOL}")
MESSAGE(STATUS "Current programmer is: ${AVR_PROGRAMMER}")
MESSAGE(STATUS "Current upload port is: ${AVR_UPLOADTOOL_PORT}")
MESSAGE(STATUS "Current uploadtool options are: ${AVR_UPLOADTOOL_OPTIONS}")
MESSAGE(STATUS "Current MCU is SET to: ${AVR_MCU}")
MESSAGE(STATUS "Current H_FUSE is SET to: ${AVR_H_FUSE}")
MESSAGE(STATUS "Current L_FUSE is SET to: ${AVR_L_FUSE}")

##################################################################################
# SET build type, IF not already SET at cmake command line
##################################################################################
IF(NOT CMAKE_BUILD_TYPE)
   SET(CMAKE_BUILD_TYPE Release)
ENDIF(NOT CMAKE_BUILD_TYPE)

##################################################################################
# needs to be defined for AVR toolchain
##################################################################################
SET(MCU_SPEED "1200000UL")

##################################################################################
# some cmake cross-compile necessities
##################################################################################
IF(DEFINED ENV{AVR_FIND_ROOT_PATH})
    SET(CMAKE_FIND_ROOT_PATH $ENV{AVR_FIND_ROOT_PATH})
else(DEFINED ENV{AVR_FIND_ROOT_PATH})
    IF(EXISTS "/opt/local/avr")
      SET(CMAKE_FIND_ROOT_PATH "/opt/local/avr")
    ELSEIF(EXISTS "/usr/avr")
      SET(CMAKE_FIND_ROOT_PATH "/usr/avr")
    ELSEIF(EXISTS "/usr/lib/avr")
      SET(CMAKE_FIND_ROOT_PATH "/usr/lib/avr")
    ELSEIF(EXISTS "/usr/local/CrossPack-AVR")
      SET(CMAKE_FIND_ROOT_PATH "/usr/local/CrossPack-AVR")
    else(EXISTS "/opt/local/avr")
      MESSAGE(FATAL_ERROR "Please SET AVR_FIND_ROOT_PATH in your environment.")
    ENDIF(EXISTS "/opt/local/avr")
ENDIF(DEFINED ENV{AVR_FIND_ROOT_PATH})
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
# not added automatically, since CMAKE_SYSTEM_NAME is "generic"
SET(CMAKE_SYSTEM_INCLUDE_PATH "${CMAKE_FIND_ROOT_PATH}/include")
SET(CMAKE_SYSTEM_LIBRARY_PATH "${CMAKE_FIND_ROOT_PATH}/lib")

##################################################################################
# status messages for generating
##################################################################################
MESSAGE(STATUS "Set CMAKE_FIND_ROOT_PATH to ${CMAKE_FIND_ROOT_PATH}")
MESSAGE(STATUS "Set CMAKE_SYSTEM_INCLUDE_PATH to ${CMAKE_SYSTEM_INCLUDE_PATH}")
MESSAGE(STATUS "Set CMAKE_SYSTEM_LIBRARY_PATH to ${CMAKE_SYSTEM_LIBRARY_PATH}")

##################################################################################
# SET compiler options for build types
##################################################################################
IF(CMAKE_BUILD_TYPE MATCHES Release)
   SET(CMAKE_C_FLAGS_RELEASE "-Os")
   SET(CMAKE_CXX_FLAGS_RELEASE "-Os")
ENDIF(CMAKE_BUILD_TYPE MATCHES Release)

IF(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
   SET(CMAKE_C_FLAGS_RELWITHDEBINFO "-Os -save-temps -g3 -gdwarf-3 -gstrict-dwarf")
   SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Os -save-temps -g3 -gdwarf-3 -gstrict-dwarf")
ENDIF(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)

IF(CMAKE_BUILD_TYPE MATCHES Debug)
   SET(CMAKE_C_FLAGS_DEBUG "-O0 -save-temps -g3 -gdwarf-3 -gstrict-dwarf")
   SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -save-temps -g3 -gdwarf-3 -gstrict-dwarf")
ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)

##################################################################################
# compiler options for all build types
##################################################################################
add_definitions("-DF_CPU=${MCU_SPEED}")
add_definitions("-fpack-struct")
add_definitions("-fshort-enums")
add_definitions("-Wall")
add_definitions("-pedantic")
#add_definitions("-pedantic-errors")
add_definitions("-funsigned-char")
add_definitions("-funsigned-bitfields")
add_definitions("-ffunction-sections")
add_definitions("-c")
add_definitions("-std=gnu99")

add_avr_executable(
   tiny-blink
   animation.c
   tiny-blink-driver.c
   fuse_lock.c
)