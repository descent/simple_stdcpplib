CXXFLAGS += $(MYCXXFLAGS) $(CFLAGS) 

CFLAGS=-g
MYCFLAGS=-fno-common -O0 -g -mcpu=cortex-m3 -mthumb -I../ -I./ -I../../../libraries/CMSIS/CM3/CoreSupport -I../../../libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x -I../../../libraries/STM32F10x_StdPeriph_Driver/inc -I../../../demos/common -mfloat-abi=soft -DP103
MYCXXFLAGS = -fno-exceptions -fno-rtti -ffreestanding -nostdlib -nodefaultlibs -std=c++11
LD_FLAGS=-Wl,-T./stm32.ld -nostartfiles

OTHER_OBJS = ../../../libraries/CMSIS/CM3/CoreSupport/core_cm3.c ../../../libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c ../../../libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/gcc_ride7/startup_stm32f10x_md.s ../../../demos/common/stm32_p103.c ../../../libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c ../../../libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c ../../../libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_usart.c ../../../libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_exti.c ../../../libraries/STM32F10x_StdPeriph_Driver/src/misc.c
MYCFLAGS=-fno-common -O0 -g -mcpu=cortex-m3 -mthumb -I../ -I./ -I../../../libraries/CMSIS/CM3/CoreSupport -I../../../libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x -I../../../libraries/STM32F10x_StdPeriph_Driver/inc -I../../../demos/common -mfloat-abi=soft 
MYCXXFLAGS = -fno-exceptions -fno-rtti -ffreestanding -nostdlib -nodefaultlibs -std=c++11
LD_FLAGS=-Wl,-T./stm32.ld -nostartfiles

OTHER_OBJS = 

CXX=arm-none-eabi-g++

LINK_FILES=bst.h bst.cpp k_stdio.cpp k_stdio.h mem.h mem.cpp

all: mymain.bin

<<<<<<< HEAD
libmystdcpp.a: myiostream.o  mylist.o  mymap.o  my_setjmp.o  mystring.o  myvec.o bst.o  gdeque.o  k_stdio.o mem.o 
	arm-none-eabi-ar rcs $@ $^

mymap: mymap.cpp mymap.h
	g++ -g -DTEST -DUSE_OS -std=c++11 -o $@ $<
mymain.elf: mymain.o libmystdcpp.a
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -Wl,-Tmain.ld -nostartfiles $(CFLAGS) -I../../demos/uart_echo/ -o $@ $(OTHER_OBJS) $< -L. -lmystdcpp -lgcc

mymain.o: mymain.cpp stm32f10x.h \
 ../../../libraries/CMSIS/CM3/CoreSupport/core_cm3.h \
  ../../../libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.h \
   type.h stm32f10x_conf.h \
    ../../../libraries/STM32F10x_StdPeriph_Driver/inc/stm32f10x_usart.h \
      bst.h myiostream.h k_stdio.h gdeque.h \
      my_setjmp.h mem.h mystring.h ../k_string.h ../type.h myvec.h mylist.h \
       mymap.h
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -Wl,-Tmain.ld -nostartfiles $(CFLAGS) -I../../demos/uart_echo/ -c $<
=======
libmystdcpp.a: myiostream.o  mylist.o  mymap.o  my_setjmp.o  mystring.o  myvec.o bst.o  gdeque.o  k_stdio.o mem.o eh.o crtbegin.o
	arm-none-eabi-ar rcs $@ $^

mymain.elf: mymain.o libmystdcpp.a
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -Wl,-Tstm32.ld -nostartfiles $(CFLAGS) -o $@ $(OTHER_OBJS) $< -L. -lmystdcpp -lgcc

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

<<<<<<< HEAD
mymap.o: mymap.cpp mymap.h type.h bst.h myiostream.h k_stdio.h \
 stm32f10x.h ../../../libraries/CMSIS/CM3/CoreSupport/core_cm3.h \
 ../../../libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.h \
 stm32f10x_conf.h \
 ../../../libraries/STM32F10x_StdPeriph_Driver/inc/stm32f10x_usart.h \
 ../stm32f10x.h gdeque.h my_setjmp.h myvec.h mem.h
=======
mymap.o: mymap.cpp mymap.h type.h bst.h myiostream.h k_stdio.h gdeque.h my_setjmp.h myvec.h mem.h
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -Wl,-Tmain.ld -nostartfiles $(CFLAGS) -I../../demos/uart_echo/ -c $<

mylist.o: mylist.cpp mylist.h
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -Wl,-Tmain.ld -nostartfiles $(CFLAGS) -I../../demos/uart_echo/ -c $<


k_stdio.o: k_stdio.cpp k_stdio.h
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -Wl,-Tmain.ld -nostartfiles $(CFLAGS) -I../../demos/uart_echo/ -c $<

bst.o: bst.cpp bst.h
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -Wl,-Tmain.ld -nostartfiles $(CFLAGS) -I../../demos/uart_echo/ -c $<

<<<<<<< HEAD
=======
eh.o: eh.cpp stm32.h
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -Wl,-Tmain.ld -nostartfiles $(CFLAGS) -c $<


crtbegin.o: crtbegin.cpp stm32.h crtbegin.h
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -Wl,-Tmain.ld -nostartfiles $(CFLAGS) -c $<

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
<<<<<<< HEAD
#CC=gcc
#CXX=g++
#CXXFLAGS=-Wall -DTEST_MAIN -DUSE_OS -std=c++11
#bst: bst.o
#	$(CXX) $(CXXFLAGS) -o $@ $< 
#bst.o: bst.cpp
#	$(CXX) $(CXXFLAGS) -c -g $<
#
#btree: btree.o
#	$(CXX) -o $@ $< 
#btree.o: btree.cpp
#	$(CXX) -c -g $<
#clean:
#	rm *.o
# make TEST=1 will make mem for testing

#CFLAGS += -g -std=c++11
#
#ifdef TEST
#CFLAGS += -DTEST
#mem: mem.o
#	g++ $(CFLAGS) -o $@ $<
#endif
#alloc: alloc.o mem.o
#	g++ $(CFLAGS) -o $@ $^
#alloc.o: alloc.cpp mem.h
#	g++ $(CFLAGS) -c $<
#mem.o: mem.cpp mem.h
#	g++ $(CFLAGS) -c $<
#clean:
#	rm -rf *.o alloc
CFLAGS=-g
MYCFLAGS=-fno-common -O0 -g -mcpu=cortex-m3 -mthumb
#-mcpu=cortex-m3 -mthumb 
MYCFLAGS_NO_LD=-nostartfiles -fno-common -O0 -g -mcpu=cortex-m3 -mthumb
LD_FLAGS=-Wl,-T./stm32.ld -nostartfiles -fno-common -mcpu=cortex-m3 -mthumb

all: t0.bin t1.bin

%.o:%.S
	arm-none-eabi-gcc $(MYCFLAGS) $(INC) -c $< 
	#arm-none-eabi-gcc $(MYCFLAGS_NO_LD) $(INC) -c $< 

%.o:%.c
	arm-none-eabi-gcc $(MYCFLAGS) $(INC) -c $< 

t0.elf: t0.o 
	arm-none-eabi-gcc $(LD_FLAGS) -o $@ $^
t1.elf: t1.o my_setjmp.o
	arm-none-eabi-gcc $(LD_FLAGS) -o $@ $^

pendsv_c.o: stm32.h lib_mygpio_led.h

pendsv_c.elf: pendsv_c.o lib_mygpio_led.o
	arm-none-eabi-gcc $(LD_FLAGS) -o $@ $^

%.bin:%.elf
	#arm-none-eabi-objcopy -R .data -O binary $< $@
	arm-none-eabi-objcopy -O binary $< $@

pendsv.elf: pendsv.o
	arm-none-eabi-ld -Ttext 0x0 -Tdata 0x20000000 -Tbss 0x20000100 -o $@ $^

process_1.bin: process_1.elf
	arm-none-eabi-objcopy -R .data -O binary $< $@
process_1.elf: process_1.o
	arm-none-eabi-ld -Ttext 0x0 -Tdata 0x20000000 -o $@ $<
process_1.o: process_1.S
	#arm-none-eabi-as -g -mcpu=cortex-m3 -mthumb -o $@ $<
	arm-none-eabi-gcc -nostartfiles -fno-common -O0 -g -mcpu=cortex-m3 -mthumb -c $< 

two_stack.bin: two_stack.elf
	arm-none-eabi-objcopy -R .data -O binary $< $@

two_stack.elf: two_stack.o
	arm-none-eabi-ld -Ttext 0x0 -Tdata 0x20000000 -Tbss 0x20000100 -o $@ $^
two_stack.o: two_stack.S
	arm-none-eabi-gcc $(MYCFLAGS) $(INC) -c $< 

myc.bin: myc.elf
	arm-none-eabi-objcopy -Obinary $< $@
myc.elf: myc.o
	arm-none-eabi-gcc $(LD_FLAGS) $(INC) -o $@ $< 

proc_periph.bin: proc_periph.elf
	arm-none-eabi-objcopy -R .data -O binary $< $@

proc_periph.elf: proc_periph.o gpio_led.o
	arm-none-eabi-ld -Ttext 0x0 -Tdata 0x20000000 -Tbss 0x20000100 -o $@ $^

proc_periph.o: proc_periph.S
	#arm-none-eabi-as -g -mcpu=cortex-m3 -mthumb -o $@ $<
	arm-none-eabi-gcc $(MYCFLAGS) $(INC) -c $< 

gpio_led.o: gpio_led.c gpio_led.h
	arm-none-eabi-gcc $(CFLAGS) -mcpu=cortex-m3 -mthumb -nostartfiles -c $<

myur_led.bin: myur_led.elf
	arm-none-eabi-objcopy -Obinary $< $@
myur_led.elf: myur_led.c
	arm-none-eabi-gcc $(MYCFLAGS) $(INC) -o $@ $< 

process.bin: process.elf
	arm-none-eabi-objcopy -R .data -O binary $< $@
process.elf: process.o
	arm-none-eabi-ld -Ttext 0x0 -Tdata 0x20000000 -o $@ $<
process.o: process.S
	arm-none-eabi-as -g -mcpu=cortex-m3 -mthumb -o $@ $<

myur.bin: myur.elf
	arm-none-eabi-objcopy -Obinary $< $@
myur.elf: myur.c
	arm-none-eabi-gcc $(MYCFLAGS) $(INC) -o $@ $< 

factorial.bin: factorial.elf
	arm-none-eabi-objcopy -O binary $< $@

factorial.elf: factorial.o
	arm-none-eabi-ld -Ttext 0x0 -o $@ $<
	
factorial.o: factorial.S
	arm-none-eabi-as -g -mcpu=cortex-m3 -mthumb -o $@ $<
	#arm-none-eabi-gcc $(CFLAGS) -mcpu=cortex-m3 -mthumb -nostartfiles -c hello.c

hello.bin: hello.elf
	arm-none-eabi-objcopy -O binary hello.elf hello.bin

hello.o: hello.c stm32.h
	arm-none-eabi-gcc $(CFLAGS) -mcpu=cortex-m3 -mthumb -nostartfiles -c hello.c

hello.elf: hello.o
	arm-none-eabi-ld -T stm32.ld -o hello.elf hello.o

mygpio_led.bin: mygpio_led.elf
	arm-none-eabi-objcopy -Obinary $< $@
mygpio_led.elf: mygpio_led.c
	arm-none-eabi-gcc $(LD_FLAGS) $(INC) -o $@ $< 
clean:
	rm -rf *.o *.bin *.elf
