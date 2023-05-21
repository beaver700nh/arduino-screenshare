cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME arduino-screenshare)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_CROSSCOMPILING 1)

set(CMAKE_CXX_COMPILER avr-g++)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> qcs <TARGET> <LINK_FLAGS> <OBJECTS>")
set(CMAKE_CXX_ARCHIVE_FINISH "<CMAKE_RANLIB> <TARGET>")

set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_C_STANDARD 17)

set(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> qcs <TARGET> <LINK_FLAGS> <OBJECTS>")
set(CMAKE_C_ARCHIVE_FINISH "<CMAKE_RANLIB> <TARGET>")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib)

if("$ENV{DISABLE_LTO}" MATCHES "YES")
set(LTO_OPTION)
else()
set(LTO_OPTION -flto)
endif()

set(
  COMPILE_OPTIONS
  -g
  -CC
  -mmcu=atmega2560
  -DARDUINO=10607
  -DARDUINO_AVR_MEGA2560
  -DARDUINO_ARCH_AVR
  -D__AVR__
  -D__AVR_ATmega2560__
  -DF_CPU=16000000
  -Wall
  -Wextra
  -Wno-error=narrowing
  -fpermissive
  -fno-exceptions
  -ffunction-sections
  -fdata-sections
  -fno-threadsafe-statics
  ${LTO_OPTION}
  -Os
)

set(
  COMPILE_INCLUDES
  ${CMAKE_CURRENT_SOURCE_DIR}
  $ENV{ARDUINO_DIR}/cores/arduino
  $ENV{ARDUINO_DIR}/variants/mega
)

set(
  LINK_OPTIONS 
  -g
  -mmcu=atmega2560
  -fuse-linker-plugin
  ${LTO_OPTION}
  -O1
  -Wl,-mavr6,--gc-sections
)

project(${PROJECT_NAME})

link_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/lib
  /usr/lib/gcc/avr/${CMAKE_CXX_COMPILER_VERSION}/avr6
  /usr/avr/lib/avr6
)

################################################################
## Executable
################################################################

add_executable(
  ${PROJECT_NAME}.elf
  src/${PROJECT_NAME}.cpp
  src/xram.cpp
)

add_custom_command(
  TARGET ${PROJECT_NAME}.elf
  POST_BUILD
  COMMAND avr-objcopy
  ARGS -O ihex -R .eeprom ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.elf ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.hex
  COMMAND avr-size
  ARGS -A ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.elf
)

target_include_directories(
  ${PROJECT_NAME}.elf
  PUBLIC
  ${COMPILE_INCLUDES}
  $ENV{ARDUINO_DIR}/libraries
  $ENV{ARDUINO_DIR}/libraries/SPI/src
  $ENV{ARDUINO_DIR}/libraries/Wire/src
  $ENV{ARDUINO_DIR_3RDPARTY}/libraries
  $ENV{ARDUINO_DIR_3RDPARTY}/libraries/Adafruit_GFX_Library
  $ENV{ARDUINO_DIR_3RDPARTY}/libraries/Adafruit_BusIO
)

target_compile_options(
  ${PROJECT_NAME}.elf
  PUBLIC
  ${COMPILE_OPTIONS}
)

target_link_libraries(
  ${PROJECT_NAME}.elf
  PUBLIC
  atmega2560
  eztft
  Adafruit_GFX_Library
  MCUFRIEND_kbv
  ${LINK_OPTIONS}
)
