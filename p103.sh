#!/bin/sh
# ctrl-a x to exit nographic mode
#~/git/qemu_stm32/arm-softmmu/qemu-system-arm -M stm32-p103 -kernel mymain.bin -display sdl 
~/git/qemu_stm32/arm-softmmu/qemu-system-arm -M stm32-p103 -kernel mymain.bin -nographic
