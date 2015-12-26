LD_FLAGS=-Wl,-T./stm32.ld -nostartfiles
MYCXXFLAGS = -fno-exceptions -fno-rtti -ffreestanding -nostdlib -nodefaultlibs -std=c++11
CFLAGS=-g

STM32F407=1
ifdef STM32F407
STM32F407_FLAG=-Istm32f407 -DSTM32F407
MYCFLAGS=-fno-common -O0 -g -mcpu=cortex-m3 -mthumb -I. -mfloat-abi=soft $(STM32F407_FLAG)
OTHER_OBJS=
endif

#for p103
ifdef P103
INC=-Ip103
P103_PATH=/home/descent/git/jserv-course/stm32_p103_demos/
MYCFLAGS=-fno-common -O0 -g -mcpu=cortex-m3 -mthumb -I/home/descent/git/jserv-course/stm32_p103_demos/libraries/CMSIS/CM3/CoreSupport -I/home/descent/git/jserv-course/stm32_p103_demos/libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x -I/home/descent/git/jserv-course/stm32_p103_demos//libraries/STM32F10x_StdPeriph_Driver/inc -I../../../demos/common -mfloat-abi=soft -DP103 -I$(P103_PATH)/demos/uart_echo/

OTHER_OBJS = $(P103_PATH)/libraries/CMSIS/CM3/CoreSupport/core_cm3.c $(P103_PATH)/libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c $(P103_PATH)/libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/gcc_ride7/startup_stm32f10x_md.s $(P103_PATH)/demos/common/stm32_p103.c $(P103_PATH)/libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c $(P103_PATH)/libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c $(P103_PATH)/libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_usart.c $(P103_PATH)/libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_exti.c $(P103_PATH)/libraries/STM32F10x_StdPeriph_Driver/src/misc.c
endif

CXXFLAGS += $(MYCXXFLAGS) $(CFLAGS) 
CXX=arm-none-eabi-g++

#LINK_FILES=bst.h bst.cpp k_stdio.cpp k_stdio.h mem.h mem.cpp

all: mymain.bin

libmystdcpp.a: myiostream.o  mylist.o  mymap.o  my_setjmp.o  mystring.o  myvec.o bst.o  gdeque.o  k_stdio.o mem.o eh.o crtbegin.o stm32f407/stm32f407_io.o
	arm-none-eabi-ar rcs $@ $^

mymain.elf: mymain.o libmystdcpp.a
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -Wl,-Tstm32.ld -nostartfiles $(CFLAGS) -o $@ $(OTHER_OBJS) $< -L. -lmystdcpp -lgcc
	#arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -Wl,-Tmain.ld -nostartfiles $(CFLAGS) -o $@ $(OTHER_OBJS) $< -L. -lmystdcpp -lgcc

mymain.o: mymain.cpp
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -nostartfiles $(CFLAGS) -c $<

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

mymap.o: mymap.cpp mymap.h type.h bst.h myiostream.h k_stdio.h gdeque.h my_setjmp.h myvec.h mem.h
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -Wl,-Tmain.ld -nostartfiles $(CFLAGS) -I../../demos/uart_echo/ -c $<

mylist.o: mylist.cpp mylist.h
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -Wl,-Tmain.ld -nostartfiles $(CFLAGS) -I../../demos/uart_echo/ -c $<


k_stdio.o: k_stdio.cpp k_stdio.h
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -Wl,-Tmain.ld -nostartfiles $(CFLAGS) -I../../demos/uart_echo/ -c $<

bst.o: bst.cpp bst.h
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -Wl,-Tmain.ld -nostartfiles $(CFLAGS) -I../../demos/uart_echo/ -c $<

eh.o: eh.cpp stm32.h
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -Wl,-Tmain.ld -nostartfiles $(CFLAGS) -c $<


crtbegin.o: crtbegin.cpp stm32.h crtbegin.h
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -Wl,-Tmain.ld -nostartfiles $(CFLAGS) -c $<

mem.o: mem.cpp mem.h
	arm-none-eabi-g++ -DSTM32 $(MYCFLAGS) $(MYCXXFLAGS) -Wl,-Tmain.ld -nostartfiles $(CFLAGS) -I../../demos/uart_echo/ -c $<


my_setjmp.o: my_setjmp.S my_setjmp.h
	arm-none-eabi-g++ -DSTM32 $(MYCFLAGS) $(MYCXXFLAGS) -Wl,-Tmain.ld -nostartfiles $(CFLAGS) -I../../demos/uart_echo/ -c $<

mymain.bin: mymain.elf
	arm-none-eabi-objcopy -Obinary $< $@

#arm-none-eabi-objdump -S demos/uart_echo/main.elf > demos/uart_echo/main.list

clean:
	rm -rf *.o *.elf *.bin *.dpp *.dpp.*
distclean:
	find . -type l -exec rm -f {} \; 
	rm -f $(LINK_FILES) libmystdcpp.a
