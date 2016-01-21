// our buffer looks like: eax,ebx,ecx,edx,esi,edi,esp,ebp,pc

#ifdef X86
  .globl	my_setjmp
my_setjmp:
  ret

.globl	my_longjmp
my_longjmp:
  ret


#else

.text
#ifdef RPI2
.code 32
#else
.code 16
#endif
.syntax unified

  .globl	my_setjmp
my_setjmp:
  mov             r12, sp
  stmea           r0!, { r4-r12, lr }
  mov             r0, #0
  bx lr



.globl	my_longjmp
my_longjmp:
  ldmfd           a1!, { v1-v7, fp, ip, lr }
  mov             sp, ip

  movs            a1, a2
  it              eq
  moveq           a1, #1
  bx lr

#if 0
@ x86 implementaion
	testl	%eax,%eax
	jne	bye
	incl	%eax		// eax hold 0 if we are here
bye:
	ret
#endif

#endif // end #ifdef X86
