.code32
.data # Initialised data
	NEWLINE: .asciz "\n"
.bss #uninitialised data
	.lcomm TEMP1, 4
	.lcomm a,1
	.lcomm b,1
	.lcomm c,1
	.lcomm d,1
	.lcomm e,1
	.lcomm f,1
	.lcomm g,1
	.lcomm h,1
	.lcomm i,1
	.lcomm j,1
	.lcomm k,1
	.lcomm l,1
	.lcomm m,1
	.lcomm n,1
	.lcomm o,1
	.lcomm p,1
	.lcomm q,1
	.lcomm r,1
	.lcomm s,1
	.lcomm t,1
	.lcomm u,1
	.lcomm v,1
	.lcomm w,1
	.lcomm x,1
	.lcomm y,1
	.lcomm z,1
.text
.globl _start # _start on linux
	.type print, @function
	.type printNumber, @function
	printNumber:
		loop:
			movl $0, %edx
			movl $10, %ebx
			divl %ebx
			addl $48, %edx
			pushl %edx
			incl %esi
			cmpl $0, %eax
			jz   next
			jmp loop

		next:
			cmpl $0, %esi
			jz   return
			decl %esi
			movl $4, %eax
			movl %esp, %ecx
			movl $1, %ebx
			movl $1, %edx
			int  $0x80
			addl $4, %esp
			jmp  next 
		return:
			ret
	print:
		movl $4, %eax
		movl $1, %ebx
		movl 4(%esp), %ecx #point to first argument which is on the stack
		movl 8(%esp), %edx #point to first argument which is on the stack
		int $0x80 # call kernel
		ret #change eip to start next instruction
_start:
	push	$5
	push	$4
	pop TEMP1
	pop %eax
	add TEMP1, %eax
	push %eax

	pop	a
	push	a
	pop %eax
	call printNumber
	push $1
	push $NEWLINE
	call print
exit:
	movl $0,%ebx # first argument: exit code
	movl $1,%eax # system call number (sys_exit)
	int $0x80 # call kernel

