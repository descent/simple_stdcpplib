#!/bin/sh
STM32f4_DIR=stm32f4_prog
if [ ! -d "$STM32f4_DIR" ]; then
  git clone https://github.com/descent/stm32f4_prog.git 
fi
#rm -rf stm32f4_prog
PREFIX_DIR=stm32f4_prog/inc
ln -sf $PREFIX_DIR/stm32f4xx_rcc.h .
ln -sf $PREFIX_DIR/core_cmInstr.h .
ln -sf $PREFIX_DIR/core_cm4.h .
ln -sf $PREFIX_DIR/core_cm4_simd.h .
ln -sf $PREFIX_DIR/stm32f4xx_usart.h .
ln -sf $PREFIX_DIR/stm32f4xx.h .
ln -sf $PREFIX_DIR/stm32f4xx_gpio.h .
ln -sf $PREFIX_DIR/core_cmFunc.h .
#ln -sf $PREFIX_DIR/stm32.h .
#ln -sf $PREFIX_DIR/stm32f10x_conf.h .
#ln -sf $PREFIX_DIR/stm32f10x.h .
