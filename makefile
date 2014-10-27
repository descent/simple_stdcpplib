CFLAGS=-g
MYCFLAGS=-fno-common -O0 -g -mcpu=cortex-m3 -mthumb -I../inc
MYCXXFLAGS = -fno-exceptions -fno-rtti
LD_FLAGS=-Wl,-T./stm32.ld -nostartfiles
CXX=arm-none-eabi-g++

# useless MYCFLAGS_NO_LD=-nostartfiles -fno-common -O0 -g -mcpu=cortex-m3 -mthumb


#%.o:%.S
#	arm-none-eabi-gcc $(MYCFLAGS) $(INC) -c $< 

#%.o:%.c
#	arm-none-eabi-gcc $(MYCFLAGS) $(INC) -c $< 


myur.o: myur.cpp
	$(CXX) $(MYCXXFLAGS) $(MYCFLAGS) $(INC) -c $< 

myur.bin: myur.elf
	arm-none-eabi-objcopy -Obinary $< $@
myur.elf: myur.o
	arm-none-eabi-gcc $(LD_FLAGS) -o $@ $^

	
clean:
	rm -rf *.o *.bin *.elf
