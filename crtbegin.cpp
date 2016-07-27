#include "crtbegin.h"
#include "myvec.h"
#include "myiostream.h"
#include "eh.h"

#ifdef P103
#include "stm32f10x.h"
#include "stm32_p103.h"
#endif

#ifdef STM32F407
#include "stm32f407_io.h"
#endif

#ifdef RPI2
#include "rpi2_io.h"
#endif

#ifdef X86_16
#include "bios_call.h"
#endif

using namespace DS;

// #define DOS

#if 0

void init_command()
{
   int i=0;
   for(i=0;i<MAX_COMMAND_LEN;i++)
      command_buff[i]='\0';
}
#endif

#ifndef X86
#define STACK_SIZE 0xfff0
#else
#define STACK_SIZE 1
#endif
extern unsigned long _etext;
extern unsigned long _sidata;
extern unsigned long _data;
extern unsigned long _edata;
extern unsigned long _bss;
extern unsigned long _ebss;


#ifdef SUPPORT_PURE_VIRTUAL_FUNCTION
// ref: http://wiki.osdev.org/C%2B%2B#Pure_virtual_functions
extern "C" void __cxa_pure_virtual()
{
    // Do nothing or print an error message.
}
#endif


void *__dso_handle;

static int obj_count=0;

static const int DOBJS_SIZE = 10;
//DS::vector<DObjs> dobjs_vec;
DObjs dobjs_vec[DOBJS_SIZE];

void g_dtor()
{
#if 0
  for (int i=obj_count-1 ; i >= 0 ; --i)
    dobjs[i].dtor_(dobjs[i].arg_);
#endif

  //for (int i=0 ; i < dobjs_vec.length() ; ++i)
  //for (int i=0 ; i < DOBJS_SIZE ; ++i)
  for (int i=obj_count-1 ; i >= 0 ; --i)
  {
    dobjs_vec[i].dtor_(dobjs_vec[i].arg_);
  }
}

  int __cxa_atexit(void (*destructor) (void *), void *arg, void *__dso_handle)
  {
    DObjs dobj;

    dobj.dtor_ = destructor;
    dobj.arg_ = arg;
    dobj.dso_handle_ = __dso_handle;

    if (obj_count >= DOBJS_SIZE)
    {
#ifdef UEFI
      printf("too many global objects: %d\n", obj_count);
#else
      DS::printf("too many global objects\n");
#endif
      return -1;
    }
    dobjs_vec[obj_count] = dobj;
    ++obj_count;

    //dobjs_vec.push_back(dobj);
    // print_memarea();

#ifdef UEFI
    //printf("too many global objects\r\n");
    printf("fill ctor data: obj_count: %d, arg: %x\r\n", obj_count, arg);
#else
    DS::printf("fill ctor data: obj_count: %d, arg: %x\r\n", obj_count, arg);
#endif
    return 0;
  }

  // ref: http://git.opencores.org/?a=viewblob&p=uClibc&h=ebb233b4fce33b04953f1d9158a0479487bb50db&f=libc/sysdeps/linux/arm/aeabi_atexit.c
  /* Register a function to be called by exit or when a shared library
     is unloaded.  This routine is like __cxa_atexit, but uses the
     calling sequence required by the ARM EABI.  */
  int __aeabi_atexit (void *arg, void (*func) (void *), void *d)
  {
    return __cxa_atexit (func, arg, d);
  }


int __cxa_guard_acquire(u32 *myself)
{
  return !(*((char*)myself));
}

void __cxa_guard_release(u32 *myself)
{
  *((char*)myself) = 1;
}

typedef void (*Fp)();

void exit(int status)
{
#ifdef DOS
  back_to_dos();
#else
  while(1);
#endif
}


  char str012[]="xyz\r\n";

#ifndef UEFI
void enter_main()
{
  // init usart for showing error message
 
  // stm32f407
#ifdef STM32F407
  init_usart(9600);
#endif

  // p103
#ifdef P103
  init_rs232();
  USART_Cmd(USART2, ENABLE);
#endif

#ifdef RPI2
    uart_init();
#endif

  //putchar('A');
#if 1
  myprint("xx abc\r\n");
  myprint(str012);
#endif


  // ur_puts(USART2, "Init complete! Hello World!\r\n");

  TRY
  {

    extern u32 __start_global_ctor__;
    extern u32 __end_global_ctor__;
    u32 *start = &__start_global_ctor__;
    u32 *end = &__end_global_ctor__;

    //myprint((u32)(*start), 16);
    //while(1);
    // run global object ctor
    #if 1
    //for (unsigned int *i = start; i != end; ++i)
    for (u32 *i = start; i != end; ++i)
    {
      Fp fp = (Fp)(*i);
      //myprint((u32)(*i), 16);
      (*fp)();
      //myprint((int)start, 16);
      //myprint("\r\n");
    }
    #endif
    #if 0
    for (unsigned int i = 0 ; i < 2; ++i)
    {
      myprint((int)start, 16);
      myprint("\r\n");
      myprint((int)end, 16);
      myprint("\r\n");
    }
    #endif
    //while(1);

    mymain();
  }
  #if 1
  CATCH(NOFREE_MEM)
  {
    cout << "no mem" << endl;
  }
  ETRY
  // run global object dtor
  g_dtor();
  #endif
  exit(0);
}

void ResetISR()
{
  unsigned long *pulSrc, *pulDest;

#if defined(P103) || defined(STM32F407)
  pulSrc = &_sidata;
  for (pulDest = &_data; pulDest < &_edata;)
    *pulDest++ = *pulSrc++;
#endif

#if 1
  for (pulDest = &_bss; pulDest < &_ebss;)
    *pulDest++ = 0;
#endif

  enter_main();
}

void pendsv_isr(void)
{
  int i=5;

  ++i;
}

void svc_isr(void)
{
  // pendsv set:
  //ref: @ Cortex™-M3 Technical Reference Manual (file name: DDI0337E_cortex_m3_r1p1_trm.pdf) p8-19
  *( unsigned long *) 0xE000ED04 |= 0x10000000;
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
#endif // #ifndef EFUI
