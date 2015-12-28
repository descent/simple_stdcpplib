#!/bin/sh

P103_PREFIX=~/git/jserv-course/stm32_p103_demos
ln -sf  $P103_PREFIX/demos/common/stm32_p103.c .
ln -sf  $P103_PREFIX/libraries/CMSIS/CM3/CoreSupport/core_cm3.c .
ln -sf  $P103_PREFIX/libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c .
ln -sf  $P103_PREFIX/libraries/STM32F10x_StdPeriph_Driver/src/misc.c .
ln -sf  $P103_PREFIX/libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_exti.c .
ln -sf  $P103_PREFIX/libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c .
ln -sf  $P103_PREFIX/libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c .
ln -sf  $P103_PREFIX/libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_usart.c .
