# STM32F2 template using CMake

This template includes the basics to get a project up and running with CMake!

## Building

You need to start with the toolchain (arm-none-eabi-gcc et al):
https://launchpad.net/gcc-arm-embedded, as well as CMake and either GNU Make or Ninja.

### Using Ninja (which is way faster!)

    mkdir build && cd build
    cmake -DCMAKE_BUILD_TYPE=Debug -GNinja ..
    ninja

### Using GNU Make

    mkdir build && cd build
    cmake -DCMAKE_BUILD_TYPE=Debug ..
    make

## Logging configuration

We use a cmake file, logging_config.cmake, to set the default log level, and add
overides for specific files. Here's a simple example:

    logging_set_default_level(${EXECUTABLE} ERROR)
    
    logging_set_level(DEBUG src/main.c)

The file-specific config will override the default. If no configuration is
specified, the default level with be `LOG_LEVEL_NONE`.
