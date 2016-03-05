cmake_minimum_required(VERSION 3.2)
project(arduino-milight)

set(ENV{PATH} "/usr/local/sbin:/usr/local/bin:/usr/bin:/usr/lib/jvm/default/bin:/usr/bin/site_perl:/usr/bin/vendor_perl:/usr/bin/core_perl")
set(PLATFORMIO_CMD "/usr/bin/platformio")

include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoavr/variants/standard")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoavr/cores/arduino")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoavr/libraries/SPI")
include_directories("$ENV{HOME}/.platformio/lib/RF24_ID433")
include_directories("$ENV{HOME}/dev/arduino-milight/lib/openmili")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoavr/libraries/Audio/src")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoavr/libraries/Bridge/src")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoavr/libraries/EEPROM")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoavr/libraries/Esplora/src")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoavr/libraries/Ethernet/src")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoavr/libraries/Firmata")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoavr/libraries/GSM/src")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoavr/libraries/HID")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoavr/libraries/Keyboard/src")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoavr/libraries/LiquidCrystal/src")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoavr/libraries/Mouse/src")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoavr/libraries/RobotIRremote/src")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoavr/libraries/Robot_Control/src")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoavr/libraries/Robot_Motor/src")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoavr/libraries/SD/src")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoavr/libraries/Scheduler/src")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoavr/libraries/Servo/src")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoavr/libraries/SoftwareSerial")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoavr/libraries/SpacebrewYun/src")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoavr/libraries/Stepper/src")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoavr/libraries/TFT/src")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoavr/libraries/Temboo/src")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoavr/libraries/USBHost/src")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoavr/libraries/WiFi/src")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoavr/libraries/Wire")
include_directories("$ENV{HOME}/.platformio/packages/toolchain-atmelavr/avr/include")
include_directories("$ENV{HOME}/.platformio/packages/toolchain-atmelavr/lib/gcc/avr/4.8.1/include")
include_directories("$ENV{HOME}/.platformio/packages/toolchain-atmelavr/lib/gcc/avr/4.8.1/include-fixed")

add_definitions(-DF_CPU=16000000L)
add_definitions(-DARDUINO_ARCH_AVR)
add_definitions(-DARDUINO_AVR_UNO)
add_definitions(-DARDUINO=10607)
add_definitions(-DPLATFORMIO=020804)
add_definitions(-D__AVR_ATmega328P__)

add_custom_target(
    PLATFORMIO_BUILD ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_UPLOAD ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target upload
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_CLEAN ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target clean
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_PROGRAM ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target program
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_UPLOADFS ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target uploadfs
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_UPDATE_ALL ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion update
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(arduino-milight
    src/arduino-milight.cpp
)
