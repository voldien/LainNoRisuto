##############################
#	USB FEATURE OPTIONS
###############################
OPTION(USB_USE_CDC OFF)
OPTION(USB_USE_VIDEO OFF)

FILE(GLOB SOURCE_FILES 
	${CMAKE_CURRENT_SOURCE_DIR}/drivers/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/gfx/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/usb/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/*.c)

FILE(GLOB HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h
${CMAKE_CURRENT_SOURCE_DIR}/drivers/*.h
${CMAKE_CURRENT_SOURCE_DIR}/gfx/*.h
									 ${CMAKE_CURRENT_SOURCE_DIR}/core/*.h)
SOURCE_GROUP(Common FILES ${HEADER_FILES} ${SOURCE_FILES})									 

# rest of your project
add_executable(pico-visual
	${SOURCE_FILES}
	${HEADER_FILES}
)

target_include_directories(pico-visual PUBLIC
		${CMAKE_CURRENT_LIST_DIR}
)


pico_enable_stdio_usb(pico-visual 0)
pico_enable_stdio_uart(pico-visual 1)

#
pico_set_program_name(pico-visual "Visual")
pico_set_program_version(pico-visual "0.1")

# pull in common dependencies
target_link_libraries(pico-visual PUBLIC
	pico_stdlib
	tinyusb_device tinyusb_board
    
    pico_float
	pico_unique_id
	hardware_adc
	hardware_spi
	hardware_dma
    hardware_pio
	pico_multicore
)

# Extract Binary
pico_add_extra_outputs(pico-visual)