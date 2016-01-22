CXXFLAGS += $(MYCXXFLAGS) $(CFLAGS) 
MYCXXFLAGS = -fno-exceptions -fno-rtti -ffreestanding -nostdlib -nodefaultlibs -std=c++11

CFLAGS=-g
INC=-Istm32f407
P103_PATH=/home/descent/git/jserv-course/stm32_p103_demos/
MYCFLAGS=-fno-common -O0 -g -mcpu=cortex-m3 -mthumb -I$(P103_PATH)/libraries/CMSIS/CM3/CoreSupport -I$(P103_PATH)/libraries/STM32F10x_StdPeriph_Driver/inc -I$(P103_PATH)/demos/common -mfloat-abi=soft -DP103 -I$(P103_PATH)/demos/uart_echo/ $(INC) -I.

SRC=core_cm3.c  stm32f10x_exti.c  stm32f10x_rcc.c    stm32_p103.c misc.c      stm32f10x_gpio.c  stm32f10x_usart.c  system_stm32f10x.c
OBJS=

all: $(OBJS)

#stm32f407_io.o: stm32f407_io.cpp stm32f407_io.h
#	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) $(CFLAGS) -c $<

%.o: %.c
	$(CXX) $(MYCFLAGS) $(MYCXXFLAGS) $(CFLAGS) -c $<

clean:
	rm -rf *.o 
distclean:
	find . -type l -exec rm -f {} \; 
