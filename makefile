# make STM32F407=1
# make P103=1
#STM32F407=1
P103=1
#RPI2=1
#X86=1

OBJCOPY=arm-none-eabi-objcopy

CXX=arm-none-eabi-g++

MYCXXFLAGS = -fno-exceptions -fno-rtti -ffreestanding -nostdlib -nodefaultlibs -std=c++11
CFLAGS=-g

PLATFORM_OBJ=

TARGET=mymain.bin libmystdcpp.a
all: $(TARGET)

ifdef STM32F407
IODIR=stm32f407
PLATFORM_OBJ=stm32f407/stm32f407_io.o
stm32f407/stm32f407_io.o: stm32f407/stm32f407_io.cpp stm32f407/stm32f407_io.h
	(cd $(IODIR) ; ./ln.sh ; make)

LD_FLAGS=-Wl,-T./stm32.ld -nostartfiles
STM32F407_FLAG=-Istm32f407 -DSTM32F407
MYCFLAGS=-fno-common -O0 -g -mcpu=cortex-m3 -mthumb -I. -mfloat-abi=soft $(STM32F407_FLAG)
OTHER_OBJS=
endif

#for p103
ifdef P103
IODIR=p103
LD_FLAGS=-Wl,-T./p103.ld -nostartfiles
INC=-Ip103
P103_PATH=/home/descent/git/jserv-course/stm32_p103_demos/
MYCFLAGS=-fno-common -O0 -g -mcpu=cortex-m3 -mthumb -I$(P103_PATH)/libraries/CMSIS/CM3/CoreSupport -I$(P103_PATH)/libraries/STM32F10x_StdPeriph_Driver/inc -I$(P103_PATH)/demos/common -mfloat-abi=soft -DP103 -I$(P103_PATH)/demos/uart_echo/ $(INC) -I.

#OTHER_OBJS = $(P103_PATH)/libraries/CMSIS/CM3/CoreSupport/core_cm3.c $(P103_PATH)/libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c $(P103_PATH)/demos/common/stm32_p103.c $(P103_PATH)/libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c $(P103_PATH)/libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c $(P103_PATH)/libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_usart.c $(P103_PATH)/libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_exti.c $(P103_PATH)/libraries/STM32F10x_StdPeriph_Driver/src/misc.c

PLATFORM_OBJ=p103/core_cm3.o  p103/stm32f10x_exti.o  p103/stm32f10x_rcc.o    p103/stm32_p103.o p103/misc.o      p103/stm32f10x_gpio.o  p103/stm32f10x_usart.o  p103/system_stm32f10x.o
$(PLATFORM_OBJ):
	(cd $(IODIR) ; ./p103_io.sh ; make)


#$(P103_PATH)/libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/gcc_ride7/startup_stm32f10x_md.s 
endif

ifdef RPI2
IODIR=rpi2
CXX=arm-linux-gnueabihf-g++
MYCFLAGS=-fno-common -O0 -g -mcpu=cortex-a7 -I. -DRPI2 -Irpi2
#ref: -Wl,--build-id=none http://stackoverflow.com/questions/15316384/do-not-pass-build-id-to-linker-from-gcc
LD_FLAGS=-Wl,--build-id=none -Wl,-T./rpi2.ld -nostartfiles
PLATFORM_OBJ=rpi2/periph.o rpi2/start.o 

$(PLATFORM_OBJ):
	(cd rpi2 ; make)
endif

ifdef X86
OBJCOPY=objcopy
IODIR=x86
CXX=g++
MYCFLAGS=-m32 -fno-common -g -DX86 -I. -I$(IODIR)
#ref: -Wl,--build-id=none http://stackoverflow.com/questions/15316384/do-not-pass-build-id-to-linker-from-gcc
LD_FLAGS=-Wl,--build-id=none -Wl,-T./x86.ld -nostartfiles
PLATFORM_OBJ=$(IODIR)/start.o $(IODIR)/bios_call.o

$(PLATFORM_OBJ):
	(cd x86 ; make)
endif

CXXFLAGS += $(MYCXXFLAGS) $(CFLAGS) 

#LINK_FILES=bst.h bst.cpp k_stdio.cpp k_stdio.h mem.h mem.cpp


libmystdcpp.a: myiostream.o  mylist.o  mymap.o  my_setjmp.o  mystring.o  myvec.o bst.o  gdeque.o  k_stdio.o mem.o eh.o crtbegin.o $(PLATFORM_OBJ)
	arm-none-eabi-ar rcs $@ $^
p103_io: $(OTHER_OBJS)
	ls -l $^
mymain.elf: mymain.o libmystdcpp.a
	#arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) $(CFLAGS) $(LD_FLAGS) -o $@ $(OTHER_OBJS) $< -L. -lmystdcpp -lgcc
	$(CXX) $(MYCFLAGS) $(MYCXXFLAGS) $(CFLAGS) $(LD_FLAGS) -o $@ $< -L. -lmystdcpp -lgcc

mymain.o: mymain.cpp
	$(CXX) $(MYCFLAGS) $(MYCXXFLAGS) $(CFLAGS) -c $<

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
	$(CXX) $(MYCFLAGS) $(MYCXXFLAGS) $(CFLAGS) -I../../demos/uart_echo/ -c $<

mem.h:
	ln -s /home/descent/git/progs/mem_alloc/$@ .
mem.cpp:
	ln -s /home/descent/git/progs/mem_alloc/$@ .


mystring.o: mystring.cpp mystring.h
	$(CXX) $(MYCFLAGS) $(MYCXXFLAGS) $(CFLAGS) -I../../demos/uart_echo/ -c $<

myiostream.o: myiostream.cpp myiostream.h
	$(CXX) $(MYCFLAGS) $(MYCXXFLAGS) $(CFLAGS) -c $<

myvec.o: myvec.cpp myvec.h
	$(CXX) $(MYCFLAGS) $(MYCXXFLAGS) $(CFLAGS) -I../../demos/uart_echo/ -c $<

mymap.o: mymap.cpp mymap.h type.h bst.h myiostream.h k_stdio.h gdeque.h my_setjmp.h myvec.h mem.h
	$(CXX) $(MYCFLAGS) $(MYCXXFLAGS) $(CFLAGS) -I../../demos/uart_echo/ -c $<

mylist.o: mylist.cpp mylist.h
	$(CXX) $(MYCFLAGS) $(MYCXXFLAGS) $(CFLAGS) -I../../demos/uart_echo/ -c $<


k_stdio.o: k_stdio.cpp k_stdio.h
	$(CXX) $(MYCFLAGS) $(MYCXXFLAGS) $(CFLAGS) -I../../demos/uart_echo/ -c $<

bst.o: bst.cpp bst.h
	$(CXX) $(MYCFLAGS) $(MYCXXFLAGS) $(CFLAGS) -I../../demos/uart_echo/ -c $<

eh.o: eh.cpp 
	$(CXX) $(MYCFLAGS) $(MYCXXFLAGS) $(CFLAGS) -c $<


crtbegin.o: crtbegin.cpp crtbegin.h
	$(CXX) $(MYCFLAGS) $(MYCXXFLAGS) $(CFLAGS) -c $<

mem.o: mem.cpp mem.h
	$(CXX) -DSTM32 $(MYCFLAGS) $(MYCXXFLAGS) $(CFLAGS) -I../../demos/uart_echo/ -c $<

cstring.o: cstring.cpp  cstring.h    
	$(CXX) -DSTM32 $(MYCFLAGS) $(MYCXXFLAGS) $(CFLAGS) -c $<


my_setjmp.o: my_setjmp.S my_setjmp.h
	$(CXX) $(MYCFLAGS) $(MYCXXFLAGS)  $(CFLAGS) -I../../demos/uart_echo/ -c $<

mymap: mymap.cpp mymap.h
	g++ -g -DTEST -DUSE_OS -m32 -std=c++11 -o $@ $<

myvec: myvec.cpp myvec.h
	g++ -g -DTEST_MAIN -DUSE_OS -m32 -std=c++11 -o $@ $<

mylist: mylist.cpp mylist.h
	g++ -g -DTEST_MAIN -DUSE_OS -m32 -std=c++11 -o $@ $<

mystring: mystring.cpp mystring.h
	g++ -static -g -DTEST -m32 -std=c++11 -o $@ $<

myiostream: myiostream.cpp myiostream.h
	g++ -g -DTEST -m32 -std=c++11 -o $@ $<

bst: bst.cpp bst.h
	g++ -g -DTEST_MAIN -DUSE_OS -m32 -std=c++11 -o $@ $<

mymain.bin: mymain.elf
	$(OBJCOPY) -Obinary $< $@

#arm-none-eabi-objdump -S demos/uart_echo/main.elf > demos/uart_echo/main.list

clean:
	rm -rf *.o *.elf *.bin *.dpp *.dpp.* $(TARGET)
	(cd $(IODIR) ; make clean)
distclean:
	find . -type l -exec rm -f {} \; 
	rm -f $(LINK_FILES) libmystdcpp.a
