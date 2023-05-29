cmake_minimum_required(VERSION 3.13)

# initialize pico-sdk from GIT
# (note this can come from environment, CMake cache etc)
SET(PICO_SDK_FETCH_FROM_GIT ON)

# pico_sdk_import.cmake is a single file copied from this SDK
# note: this must happen before project()
SET(PICO_BOARD pico)

include(cmake/pico_sdk_import.cmake)

project(GameConsole C CXX ASM)
#enable_language(  )

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
add_executable(gameconsole
    main.c usb_descriptors.c
)

target_include_directories(gameconsole PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

# pull in common dependencies
target_link_libraries(gameconsole pico_stdlib
    #tinyusb_device tinyusb_board
    tinyusb_device tinyusb_board
    hardware_adc
    hardware_i2c
    hardware_interp
    hardware_dma hardware_pio
    pico_multicore
)

# create map/bin/hex file etc.
pico_add_extra_outputs(gameconsole)
