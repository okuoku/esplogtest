cmake_minimum_required(VERSION 3.14) # For RULE_LAUNCH_CUSTOM fix
project(esplogtest)

set(PORT /dev/ttyS4)
set(idf_path ${CMAKE_CURRENT_LIST_DIR}/esp-idf)
set(ENV{IDF_PATH} ${idf_path})
# set(ENV{IDF_MAINTAINER} true)

# Generate custom launcher
set(launcher_file ${CMAKE_CURRENT_BINARY_DIR}/runtool.sh)
set(launcher_src "#!/bin/sh\nexport ESPPORT=${PORT}\nexport IDF_PATH=${idf_path}\nexec \"$@\"\n")
file(WRITE ${launcher_file} ${launcher_src})
set_property(GLOBAL
    PROPERTY RULE_LAUNCH_CUSTOM
    ${launcher_file})

execute_process(COMMAND
    chmod +x ${launcher_file})


include($ENV{IDF_PATH}/tools/cmake/idf.cmake)

# ESP-IDF targets
# https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/build-system.html#using-esp-idf-in-custom-cmake-projects
idf_build_process(esp32
    # Initialize ESP-IDF (local build)
    SDKCONFIG ${CMAKE_CURRENT_LIST_DIR}/sdkconfig
    )
add_executable(check dummy.c)
target_link_libraries(check
    idf::newlib)
idf_build_executable(check)


# Custom projects for tools

add_custom_target(mon
    COMMAND
    ${PYTHON} ${idf_path}/tools/idf_monitor.py
    --port ${PORT}
    --baud 115200
    esp32test.elf
    USES_TERMINAL)

