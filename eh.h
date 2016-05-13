#ifndef EH_H
#define EH_H
#include "x86_16.h"
#include "my_setjmp.h"

#define setjmp my_setjmp
#define longjmp my_longjmp

extern  int ex_code;
extern jmp_buf ex_buf__;

#define TRY do { switch((ex_code = setjmp(ex_buf__))) { case 0:
#define CATCH(x) break; case x : 
#define ETRY break; } } while(0);
#define THROW(x) longjmp(ex_buf__, x)

#define NOFREE_MEM 5



#endif
