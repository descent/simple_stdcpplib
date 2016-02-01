#ifndef CRTBEGIN_H
#define CRTBEGIN_H

#include "x86_16.h"
#include "type.h"

extern void *__dso_handle;

struct DObjs
{
  void (*dtor_) (void *);
  void *arg_;
  void *dso_handle_;
};

void exit(int status);
void g_dtor();
void mymain();

extern "C"
{
  void ResetISR();
  int __cxa_guard_acquire(u32 *myself);
  void __cxa_guard_release(u32 *myself);
  int  __cxa_atexit(void (*)(void*), void*, void* );
  int __aeabi_atexit (void *arg, void (*func) (void *), void *d);
  void enter_main();
}


#endif
