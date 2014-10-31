#ifndef STM32_H
#define STM32_H

#include "lib_mygpio_led.h"

#define STACK_SIZE 0xffff
extern unsigned long _etext;
extern unsigned long _data;
extern unsigned long _edata;
extern unsigned long _bss;
extern unsigned long _ebss;

extern "C"
{
  int mymain();
}

void ResetISR(void)
{
  unsigned long *pulSrc, *pulDest;

  pulSrc = &_etext;
  for (pulDest = &_data; pulDest < &_edata;)
    *pulDest++ = *pulSrc++;
  for (pulDest = &_bss; pulDest < &_ebss;)
    *pulDest++ = 0;

  mymain();
}

void pendsv_isr(void)
{
  int i=5;

  ++i;
#if 1
  //void test_led();
  //test_led();
  /* PD12 to be toggled */
  GPIO_SetBits(GPIOD, GPIO_Pin_12); 
  /* Insert delay */
  Delay(0x3FFFFF);

#endif
}

void svc_isr(void)
{
  // pendsv set:
  //ref: @ Cortex™-M3 Technical Reference Manual (file name: DDI0337E_cortex_m3_r1p1_trm.pdf) p8-19
  *( unsigned long *) 0xE000ED04 |= 0x10000000;
  GPIO_SetBits(GPIOD, GPIO_Pin_13); 
  /* Insert delay */
  Delay(0x3FFFFF);
}

void systick_isr(void)
{
}

void int_isr(void)
{
}

#ifdef EXT_INT

void wwdg_isr(void)
{
  int b=33;
}
void pvd_isr(void)
{
}
void tamp_stamp_isr(void)
{
}

void rtc_wkup_isr(void)
{
}
void flash_isr(void)
{
}
void rcc_isr(void)
{
}

void exti0_isr(void);
#endif

typedef void (*pfnISR)(void);

static unsigned long pulStack[10] __attribute__((section(".stackares")));
 __attribute__((section(".ccm")))
static u8 stack[STACK_SIZE];


__attribute__((section(".isr_vector")))
pfnISR VectorTable[]=
{
  (pfnISR)((unsigned long)stack + STACK_SIZE),
  ResetISR, // 1
  int_isr,
  int_isr,
  int_isr,
  int_isr,
  int_isr,
  int_isr,
  int_isr,
  int_isr,
  int_isr,
  svc_isr,    // 11
  int_isr,
  int_isr,
  pendsv_isr, // 14
  systick_isr, // 15

#ifdef EXT_INT
  // External Interrupts
  wwdg_isr,                   // Window WatchDog
  pvd_isr,                   // PVD through EXTI Line detection                      
  tamp_stamp_isr,            // Tamper and TimeStamps through the EXTI line
  rtc_wkup_isr,              // RTC Wakeup through the EXTI line                     
  flash_isr,                 // FLASH                                           
  rcc_isr,                   // RCC                                             
  exti0_isr                  // EXTI Line0 
#endif
};

#endif
