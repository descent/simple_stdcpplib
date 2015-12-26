CXXFLAGS += $(MYCXXFLAGS) $(CFLAGS) 
LD_FLAGS=-Wl,-T./stm32.ld -nostartfiles
MYCXXFLAGS = -fno-exceptions -fno-rtti -ffreestanding -nostdlib -nodefaultlibs -std=c++11

CFLAGS=-g
INC=-Istm32f407
MYCFLAGS=-I.. -fno-common -O0 -g -mcpu=cortex-m3 -mthumb -Istm32f407 -mfloat-abi=soft -DSTM32F407

stm32f407_io.o: stm32f407_io.cpp stm32f407_io.h
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) $(CFLAGS) -c $<
clean:
	rm -rf *.o 
