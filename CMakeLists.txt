cmake_minimum_required(VERSION 3.5)

# Using C17 and C++20 by default.
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

# Comment these lines accordingly based on the board you are using!
set(PICO_BOARD pico)
# set(PICO_BOARD pico2)
# set(PICO_BOARD pico_w)
# set(PICO_BOARD pico2_w)

# Below is how we determine which board we are using for both our code, and the compiler.
if (PICO_BOARD STREQUAL "pico")
add_compile_definitions(USING_PICO)
set(PICO_PLATFORM rp2040)
set(PICO_LABEL RPI-RP2)
elseif(PICO_BOARD STREQUAL "pico_w")
add_compile_definitions(USING_PICO_W)
set(PICO_PLATFORM rp2040)
set(PICO_LABEL RPI-RP2)
elseif(PICO_BOARD STREQUAL "pico2")
add_compile_definitions(USING_PICO_2)
set(PICO_PLATFORM rp2350)
set(PICO_LABEL RP2350)
elseif(PICO_BOARD STREQUAL "pico2_w")
add_compile_definitions(USING_PICO_2_W)
set(PICO_PLATFORM rp2350)
set(PICO_LABEL RP2350)
endif()

# Enable and disable features here.
option(USING_PRINT "Enable printing to stdout. Use this while testing and debugging." ON) # Switch to OFF when project is complete.
option(USING_MULTICORE "Enable use of the Pico's second core. Enable this for parallel processing or separate tasks." OFF)

# Add theses definitions to your IDE.
if (USING_PRINT)    
add_compile_definitions(USING_PRINT=1)
set(USE_PRINT_CMAKE 1)
else()
set(USE_PRINT_CMAKE 0)
endif()
if (USING_MULTICORE)
add_compile_definitions(USING_MULTICORE=1)
set(USE_MULTICORE_CMAKE 1)
else()
set(USE_MULTICORE_CMAKE 0)
endif()

include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)

# Change the first argument with your project name!
project(ExampleProject C CXX ASM)

set(PICO_CXX_ENABLE_RTTI 1)

pico_sdk_init()

add_subdirectory(lib/ZipsPicoLib)

# Be sure to add any other .c or .cpp files if needed.
add_executable(${CMAKE_PROJECT_NAME} src/main.c)

target_link_libraries(${CMAKE_PROJECT_NAME}
    pico_stdlib
    ZipsPicoLib
)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
    include
)

pico_enable_stdio_usb(${CMAKE_PROJECT_NAME} 1)
pico_enable_stdio_uart(${CMAKE_PROJECT_NAME} 1)
pico_add_extra_outputs(${CMAKE_PROJECT_NAME})

set(ELF_PATH "${CMAKE_CURRENT_BINARY_DIR}/${TARGET_FILE}${CMAKE_PROJECT_NAME}.elf")
file(WRITE "${CMAKE_BINARY_DIR}/elf_path.txt" "${ELF_PATH}\n")

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/tmp/flash.sh
"#!/bin/bash

MOUNT_PNT=\"/mnt/pico\"

mkdir -p $MOUNT_PNT

DEVICE=$(blkid -o device -L ${PICO_LABEL})

if [ -n \"$DEVICE\" ]
then
    sudo unmount -l $MOUNT_PNT
    echo \"Found Pico at $DEVICE. Mounting...\"
    sudo mount $DEVICE $MOUNT_PNT
    echo \"Mounted $DEVICE at $MOUNT_PNT.\"
    echo \"Copying binary to board...\"
    sudo cp ${CMAKE_PROJECT_NAME}.uf2 $MOUNT_PNT/${CMAKE_PROJECT_NAME}.uf2
else
    echo \"Device not found. Be sure to hold BOOTSEL while re-powering the board to your computer.\"
fi
")

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/tmp/tty.sh
"
#!/bin/bash

DEVICE_NAME=$(sudo dmesg | grep -oP 'ttyACM[0-9]+')

if [ -z \"DEVICE_NAME\" ]
then
    echo \"Device not found, ensure serial print is enabled.\"
else
    minicom -b 115200 -o -D /dev/$DEVICE_NAME
fi
")

file(
    COPY ${CMAKE_CURRENT_BINARY_DIR}/tmp/flash.sh
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
    FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)

file(
    COPY ${CMAKE_CURRENT_BINARY_DIR}/tmp/tty.sh
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
    FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)