# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.28
cmake_policy(SET CMP0009 NEW)

# SRC_FILES at CMakeLists.txt:8 (file)
file(GLOB NEW_GLOB LIST_DIRECTORIES true "/home/kimgwanwoo/avr-vscode/atmega128a/*.c")
set(OLD_GLOB
  "/home/kimgwanwoo/avr-vscode/atmega128a/main.c"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/kimgwanwoo/avr-vscode/atmega128a/build/CMakeFiles/cmake.verify_globs")
endif()

# SRC_FILES at CMakeLists.txt:8 (file)
file(GLOB NEW_GLOB LIST_DIRECTORIES true "/home/kimgwanwoo/avr-vscode/atmega128a/*.cpp")
set(OLD_GLOB
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/kimgwanwoo/avr-vscode/atmega128a/build/CMakeFiles/cmake.verify_globs")
endif()

# SRC_FILES_RECURSE at CMakeLists.txt:14 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/home/kimgwanwoo/avr-vscode/atmega128a/src/*.c")
set(OLD_GLOB
  "/home/kimgwanwoo/avr-vscode/atmega128a/src/ap.c"
  "/home/kimgwanwoo/avr-vscode/atmega128a/src/driver/NFC_rf522.c"
  "/home/kimgwanwoo/avr-vscode/atmega128a/src/driver/NFC_spi.c"
  "/home/kimgwanwoo/avr-vscode/atmega128a/src/driver/button.c"
  "/home/kimgwanwoo/avr-vscode/atmega128a/src/driver/buzzer.c"
  "/home/kimgwanwoo/avr-vscode/atmega128a/src/driver/fnd_4ea.c"
  "/home/kimgwanwoo/avr-vscode/atmega128a/src/driver/i2c.c"
  "/home/kimgwanwoo/avr-vscode/atmega128a/src/driver/i2c_lcd.c"
  "/home/kimgwanwoo/avr-vscode/atmega128a/src/driver/led.c"
  "/home/kimgwanwoo/avr-vscode/atmega128a/src/driver/pwm16.c"
  "/home/kimgwanwoo/avr-vscode/atmega128a/src/driver/pwm8.c"
  "/home/kimgwanwoo/avr-vscode/atmega128a/src/driver/rgb_led.c"
  "/home/kimgwanwoo/avr-vscode/atmega128a/src/driver/uart0.c"
  "/home/kimgwanwoo/avr-vscode/atmega128a/src/driver/uart1.c"
  "/home/kimgwanwoo/avr-vscode/atmega128a/src/driver/ultrasonic.c"
  "/home/kimgwanwoo/avr-vscode/atmega128a/src/driver/ultrasonic_cap.c"
  "/home/kimgwanwoo/avr-vscode/atmega128a/src/driver/ultrasonic_int.c"
  "/home/kimgwanwoo/avr-vscode/atmega128a/src/project_main.c"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/kimgwanwoo/avr-vscode/atmega128a/build/CMakeFiles/cmake.verify_globs")
endif()

# SRC_FILES_RECURSE at CMakeLists.txt:14 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/home/kimgwanwoo/avr-vscode/atmega128a/src/*.cpp")
set(OLD_GLOB
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/kimgwanwoo/avr-vscode/atmega128a/build/CMakeFiles/cmake.verify_globs")
endif()
