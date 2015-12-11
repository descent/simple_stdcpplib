CXXFLAGS += $(MYCXXFLAGS) $(CFLAGS) 

CFLAGS=-g
MYCFLAGS=-fno-common -O0 -g -mcpu=cortex-m3 -mthumb -I../ -I./ -I../../../libraries/CMSIS/CM3/CoreSupport -I../../../libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x -I../../../libraries/STM32F10x_StdPeriph_Driver/inc -I../../../demos/common -mfloat-abi=soft -DP103
MYCXXFLAGS = -fno-exceptions -fno-rtti -ffreestanding -nostdlib -nodefaultlibs -std=c++11
LD_FLAGS=-Wl,-T./stm32.ld -nostartfiles

OTHER_OBJS = ../../../libraries/CMSIS/CM3/CoreSupport/core_cm3.c ../../../libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c ../../../libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/gcc_ride7/startup_stm32f10x_md.s ../../../demos/common/stm32_p103.c ../../../libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c ../../../libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c ../../../libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_usart.c ../../../libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_exti.c ../../../libraries/STM32F10x_StdPeriph_Driver/src/misc.c

CXX=arm-none-eabi-g++

LINK_FILES=bst.h bst.cpp k_stdio.cpp k_stdio.h mem.h mem.cpp

all: mymain.bin

mymain.elf: mymain.o bst.o k_stdio.o mem.o myiostream.o mystring.o gdeque.o my_setjmp.o myvec.o mylist.o mymap.o
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -Wl,-Tmain.ld -nostartfiles $(CFLAGS) -I../../demos/uart_echo/ -o $@ $(OTHER_OBJS) $^ -lgcc

mymain.o: mymain.cpp bst.h
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -Wl,-Tmain.ld -nostartfiles $(CFLAGS) -I../../demos/uart_echo/ -c $<

bst.h:
	ln -s /home/descent/git/progs/tree/$@ .

bst.cpp:
	ln -s /home/descent/git/progs/tree/$@ .

k_stdio.cpp:
	ln -s /home/descent/git/jserv-course/stm32f4_prog/stm32f4_simple_scheme/$@ .
k_stdio.h:
	ln -s /home/descent/git/jserv-course/stm32f4_prog/stm32f4_simple_scheme/$@ .

k_string.h:
	ln -s /home/descent/git/jserv-course/stm32f4_prog/stm32f4_simple_scheme/$@ .

gdeque.h:
	ln -s /home/descent/git/progs/queue/$@ .
gdeque.cpp:
	ln -s /home/descent/git/progs/queue/$@ .

gdeque.o: gdeque.cpp gdeque.h
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -Wl,-Tmain.ld -nostartfiles $(CFLAGS) -I../../demos/uart_echo/ -c $<

mem.h:
	ln -s /home/descent/git/progs/mem_alloc/$@ .
mem.cpp:
	ln -s /home/descent/git/progs/mem_alloc/$@ .


mystring.o: mystring.cpp mystring.h
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -Wl,-Tmain.ld -nostartfiles $(CFLAGS) -I../../demos/uart_echo/ -c $<

myiostream.o: myiostream.cpp myiostream.h
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -Wl,-Tmain.ld -nostartfiles $(CFLAGS) -I../../demos/uart_echo/ -c $<

myvec.o: myvec.cpp myvec.h
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -Wl,-Tmain.ld -nostartfiles $(CFLAGS) -I../../demos/uart_echo/ -c $<

mymap.o: mymap.cpp mymap.h
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -Wl,-Tmain.ld -nostartfiles $(CFLAGS) -I../../demos/uart_echo/ -c $<

mylist.o: mylist.cpp mylist.h
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -Wl,-Tmain.ld -nostartfiles $(CFLAGS) -I../../demos/uart_echo/ -c $<


k_stdio.o: k_stdio.cpp k_stdio.h
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -Wl,-Tmain.ld -nostartfiles $(CFLAGS) -I../../demos/uart_echo/ -c $<

bst.o: bst.cpp bst.h
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -Wl,-Tmain.ld -nostartfiles $(CFLAGS) -I../../demos/uart_echo/ -c $<

mem.o: mem.cpp mem.h
	arm-none-eabi-g++ -DSTM32 $(MYCFLAGS) $(MYCXXFLAGS) -Wl,-Tmain.ld -nostartfiles $(CFLAGS) -I../../demos/uart_echo/ -c $<

my_setjmp.h:
	ln -s /home/descent/git/jserv-course/stm32f4_prog/myjmp/$@ .
my_setjmp.S:
	ln -s /home/descent/git/jserv-course/stm32f4_prog/myjmp/$@ .

my_setjmp.o: my_setjmp.S my_setjmp.h
	arm-none-eabi-g++ -DSTM32 $(MYCFLAGS) $(MYCXXFLAGS) -Wl,-Tmain.ld -nostartfiles $(CFLAGS) -I../../demos/uart_echo/ -c $<

mymain.bin: mymain.elf
	arm-none-eabi-objcopy -Obinary $< $@

#arm-none-eabi-objdump -S demos/uart_echo/main.elf > demos/uart_echo/main.list

clean:
	rm -rf *.o *.elf *.bin *.dpp *.dpp.*
distclean:
	find . -type l -exec rm -f {} \; 
	rm -f $(LINK_FILES)
