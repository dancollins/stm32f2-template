cmake_minimum_required(VERSION 3.16.3)

# We always want to cross-compile for ARM
set(CMAKE_TOOLCHAIN_FILE
  ${CMAKE_SOURCE_DIR}/cmake/toolchain.arm-none-eabi-gcc.cmake)

enable_language(C ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

project(stm32f2-template)

set(PROJECT_FILES
  src/main.c
  src/logging/logging.c)

set(STM32CUBEMX_GENERATED_FILES
  src/stm/startup_stm32f207xx.s

  src/stm/Src/stm32f2xx_hal_msp.c
  src/stm/Src/stm32f2xx_it.c
  src/stm/Src/system_stm32f2xx.c

  src/stm/Inc/main.h
  src/stm/Inc/stm32f2xx_hal_conf.h
  src/stm/Inc/stm32f2xx_it.h)

set(STM32CUBEF2_FILES
  STM32CubeF2/Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_tim.c
  STM32CubeF2/Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_tim_ex.c
  STM32CubeF2/Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_uart.c
  STM32CubeF2/Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal.c
  STM32CubeF2/Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rcc.c
  STM32CubeF2/Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rcc_ex.c
  STM32CubeF2/Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_cortex.c
  STM32CubeF2/Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_flash.c
  STM32CubeF2/Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_flash_ex.c
  STM32CubeF2/Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_pwr.c
  STM32CubeF2/Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_pwr_ex.c
  STM32CubeF2/Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_gpio.c
  STM32CubeF2/Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_dma.c
  STM32CubeF2/Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_dma_ex.c)

set_source_files_properties(${STM32CUBEF2_FILES}
  PROPERTIES
  COMPILE_FLAGS -Wno-unused-parameter)

set(EXECUTABLE ${PROJECT_NAME}.elf)
add_executable(${EXECUTABLE} ${PROJECT_FILES}
  ${STM32CUBEMX_GENERATED_FILES}
  ${STM32CUBEF2_FILES})


include(${CMAKE_SOURCE_DIR}/cmake/logging.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/logging_config.cmake OPTIONAL)
logging_set_filename(${EXECUTABLE})


target_compile_definitions(${EXECUTABLE} PRIVATE
  -DUSE_HAL_DRIVER
  -DSTM32F207xx)

target_include_directories(${EXECUTABLE} PRIVATE
  src
  src/stm/Inc

  STM32CubeF2/Drivers/STM32F2xx_HAL_Driver/Inc
  STM32CubeF2/Drivers/STM32F2xx_HAL_Driver/Inc/Legacy
  STM32CubeF2/Drivers/CMSIS/Device/ST/STM32F2xx/Include
  STM32CubeF2/Drivers/CMSIS/Include)

target_compile_options(${EXECUTABLE} PRIVATE
  -mcpu=cortex-m3
  -mthumb
  -mfloat-abi=soft
  -fdata-sections
  -ffunction-sections

  -Wall
  -Werror

  $<$<CONFIG:Debug>:-Og>)

target_link_options(${EXECUTABLE} PRIVATE
  -T${CMAKE_SOURCE_DIR}/src/stm/STM32F207ZGTx_FLASH.ld

  -mcpu=cortex-m3
  -mthumb
  -mfloat-abi=soft

  -specs=nano.specs
  -specs=nosys.specs
  -lc
  -lm
  -Wl,-Map=${PROJECT_NAME}.map,--cref
  -Wl,--gc-sections
  -Wl,--print-memory-usage)


add_custom_command(TARGET ${EXECUTABLE}
  POST_BUILD
  COMMAND arm-none-eabi-size ${EXECUTABLE})

add_custom_command(TARGET ${EXECUTABLE}
  POST_BUILD
  COMMAND arm-none-eabi-objcopy -O ihex ${EXECUTABLE} ${PROJECT_NAME}.hex
  COMMAND arm-none-eabi-objcopy -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin)


set_target_properties(${EXECUTABLE} PROPERTIES ADDITIONAL_CLEAN_FILES
  "${PROJECT_NAME}.bin;${PROJECT_NAME}.hex;${PROJECT_NAME}.map")
