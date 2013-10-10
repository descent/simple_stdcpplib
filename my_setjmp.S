// our buffer looks like: eax,ebx,ecx,edx,esi,edi,esp,ebp,pc

.text
.code 16
.syntax unified

  .globl	my_setjmp
my_setjmp:
  mov             r12, sp
  stmea           r0!, { r4-r12, lr }
  mov             r0, #0
  bx lr



#if 0
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
#endif
