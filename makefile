include rule.mk

CFLAGS += $(MYCFLAGS)
CXXFLAGS += $(MYCXXFLAGS) $(CFLAGS)

sources = cell.cpp  k_stdio.cpp  mydeque.cpp  myur.cpp  s_eval.cpp  token_container.cpp

include $(sources:.cpp=.dpp)

# useless MYCFLAGS_NO_LD=-nostartfiles -fno-common -O0 -g -mcpu=cortex-m3 -mthumb


#%.o:%.S
#	arm-none-eabi-gcc $(MYCFLAGS) $(INC) -c $< 

#%.o:%.c
#	arm-none-eabi-gcc $(MYCFLAGS) $(INC) -c $< 


myur.bin: myur.elf
	arm-none-eabi-objcopy -Obinary $< $@
myur.o: myur.cpp stm32.h ../inc/lib_mygpio_led.h ../inc/stm32f4xx_gpio.h \
 ../inc/stm32f4xx.h ../inc/core_cm4.h ../inc/core_cmInstr.h \
  ../inc/core_cmFunc.h ../inc/core_cm4_simd.h ../inc/type.h \
   ../inc/stm32f4xx_conf.h ../inc/stm32f4xx_gpio.h ../inc/stm32f4xx.h \
    ../inc/stm32f4xx_rcc.h ../inc/stm32f4xx_usart.h
	$(CXX) $(MYCXXFLAGS) $(MYCFLAGS) $(INC) -c $< 

myur.elf: myur.o cell.o  s_eval.o  token_container.o k_stdio.o
	$(CXX) $(LD_FLAGS) -o $@ $^



token_container.h:
	ln -s ~/git/simple_scheme/token_container.h .
token_container.cpp:
	ln -s ~/git/simple_scheme/token_container.cpp .
s_eval.h:
	ln -s ~/git/simple_scheme/s_eval.h .
s_eval.cpp:
	ln -s ~/git/simple_scheme/s_eval.cpp  .
cell.h:
	ln -s ~/git/simple_scheme/cell.h .
cell.cpp:
	ln -s ~/git/simple_scheme/cell.cpp .
	
clean:
	rm -rf *.o *.elf *.bin *.dpp
distclean:
	find . -type l -exec rm -f {} \;
