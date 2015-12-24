CXXFLAGS += $(MYCXXFLAGS) $(CFLAGS) 

CFLAGS=-g
MYCFLAGS=-fno-common -O0 -g -mcpu=cortex-m3 -mthumb -I../ -mfloat-abi=soft 

MYCXXFLAGS = -fno-exceptions -fno-rtti -ffreestanding -nostdlib -nodefaultlibs -std=c++11
LD_FLAGS=-Wl,-T./stm32.ld -nostartfiles

OTHER_OBJS = 

CXX=arm-none-eabi-g++

LINK_FILES=bst.h bst.cpp k_stdio.cpp k_stdio.h mem.h mem.cpp

all: libmystdcpp.a

libmystdcpp.a: myiostream.o  mylist.o  mymap.o  my_setjmp.o  mystring.o  myvec.o bst.o  gdeque.o  k_stdio.o mem.o eh.o crtbegin.o
	arm-none-eabi-ar rcs $@ $^

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
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -nostartfiles $(CFLAGS) -c $<

mem.h:
	ln -s /home/descent/git/progs/mem_alloc/$@ .
mem.cpp:
	ln -s /home/descent/git/progs/mem_alloc/$@ .


mystring.o: mystring.cpp mystring.h
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -nostartfiles $(CFLAGS) -c $<

myiostream.o: myiostream.cpp myiostream.h
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -nostartfiles $(CFLAGS) -c $<

myvec.o: myvec.cpp myvec.h
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -nostartfiles $(CFLAGS) -c $<

mymap.o: mymap.cpp mymap.h type.h bst.h myiostream.h k_stdio.h gdeque.h my_setjmp.h myvec.h mem.h
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -nostartfiles $(CFLAGS) -c $<

mylist.o: mylist.cpp mylist.h
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -nostartfiles $(CFLAGS) -c $<


k_stdio.o: k_stdio.cpp k_stdio.h
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -nostartfiles $(CFLAGS) -c $<

bst.o: bst.cpp bst.h
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -nostartfiles $(CFLAGS) -c $<

eh.o: eh.cpp stm32.h
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -nostartfiles $(CFLAGS) -c $<


crtbegin.o: crtbegin.cpp stm32.h crtbegin.h
	arm-none-eabi-g++ $(MYCFLAGS) $(MYCXXFLAGS) -nostartfiles $(CFLAGS) -c $<

mem.o: mem.cpp mem.h
	arm-none-eabi-g++ -DSTM32 $(MYCFLAGS) $(MYCXXFLAGS) -nostartfiles $(CFLAGS) -c $<

my_setjmp.h:
	ln -s /home/descent/git/jserv-course/stm32f4_prog/myjmp/$@ .
my_setjmp.S:
	ln -s /home/descent/git/jserv-course/stm32f4_prog/myjmp/$@ .

my_setjmp.o: my_setjmp.S my_setjmp.h
	arm-none-eabi-g++ -DSTM32 $(MYCFLAGS) $(MYCXXFLAGS) -nostartfiles $(CFLAGS) -c $<

mymain.bin: mymain.elf
	arm-none-eabi-objcopy -Obinary $< $@

#arm-none-eabi-objdump -S demos/uart_echo/main.elf > demos/uart_echo/main.list

clean:
	rm -rf *.o *.elf *.bin *.dpp *.dpp.*
distclean:
	find . -type l -exec rm -f {} \; 
	rm -f libmystdcpp.a
