// our buffer looks like: eax,ebx,ecx,edx,esi,edi,esp,ebp,pc


//#define UEFI
#ifdef X86_64
// x86_64: 
// newlib-2.1.0/newlib/libc/machine/x86_64/setjmp.S
// newlib-2.1.0/newlib/libc/machine/x86_64/x86_64mach.h
// newlib-2.1.0/newlib/libc/include/machine/setjmp.h

  .globl	my_setjmp
my_setjmp:
  movq    %rbx,  0 (%rdi)
  movq    %rbp,  8 (%rdi)
  movq    %r12, 16 (%rdi)
  movq    %r13, 24 (%rdi)
  movq    %r14, 32 (%rdi)
  movq    %r15, 40 (%rdi)
  leaq    8 (%rsp), %rax
  movq    %rax, 48 (%rdi)
  movq    (%rsp), %rax
  movq    %rax, 56 (%rdi)
  movq    $0, %rax
  ret


  .globl	my_longjmp
my_longjmp:
  movq    %rsi, %rax        /* Return value */
  movq     8 (%rdi), %rbp
  #__CLI
  movq    48 (%rdi), %rsp
  pushq   56 (%rdi)
  movq     0 (%rdi), %rbx
  movq    16 (%rdi), %r12
  movq    24 (%rdi), %r13
  movq    32 (%rdi), %r14
  movq    40 (%rdi), %r15
  #__STI
  ret


#else

#ifdef X86
#ifdef X86_16
.code16

#endif
	.globl	my_setjmp
my_setjmp:
	//pushl	%esp

#if 1
	pushl	%ebx
	movl	8(%esp), %ebx
	movl	%eax, (%ebx)
	popl	%eax


	pushl	%eax

	movl	%eax, 4(%ebx)
	movl	%ecx, 8(%ebx)
	movl	%edx, 12(%ebx)
	movl	%esi, 16(%ebx)
	movl	%edi, 20(%ebx)
	movl	%esp, 24(%ebx)
	movl	%ebp, 28(%ebx)


	movl	4(%esp), %eax
	movl	%eax, 32(%ebx)
#endif
        popl %ebx
	xorl	%eax, %eax
	//popl	%esp
	ret

	.globl	my_longjmp
my_longjmp:
	movl	4(%esp), %ebx	// address of buf
	movl	8(%esp), %eax	// store return value

	movl	24(%ebx), %esp	// restore stack
	movl	32(%ebx), %edi
// Next line sets up return address.
	movl	%edi, 0(%esp)	
	movl	8(%ebx), %ecx
	movl	12(%ebx), %edx
	movl	16(%ebx), %esi
	movl	20(%ebx), %edi
	movl	28(%ebx), %ebp
	movl	4(%ebx), %ebx
	testl	%eax,%eax
	jne	bye
	incl	%eax		// eax hold 0 if we are here
bye:
	ret

#else // #ifdef X86




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

#endif 
