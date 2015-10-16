.code32
.data # Initialised data
	NEWLINE: .asciz "\n"
	MINUS: .asciz "-"
.bss #uninitialised data
	.lcomm COUNTER, 4
	.lcomm TEMP1, 4
	.lcomm a,4
	.lcomm b,4
	.lcomm c,4
	.lcomm d,4
	.lcomm e,4
	.lcomm f,4
	.lcomm g,4
	.lcomm h,4
	.lcomm i,4
	.lcomm j,4
	.lcomm k,4
	.lcomm l,4
	.lcomm m,4
	.lcomm n,4
	.lcomm o,4
	.lcomm p,4
	.lcomm q,4
	.lcomm r,4
	.lcomm s,4
	.lcomm t,4
	.lcomm u,4
	.lcomm v,4
	.lcomm w,4
	.lcomm x,4
	.lcomm y,4
	.lcomm z,4
.text
.globl _start # _start on linux
	.type print, @function
	.type printNumber, @function
	printNumber:
		movl $0, COUNTER
		cmpl $0, %eax #is it negative number
		jge loop #if eax is greater or equal zero then go to loop
		neg %eax #change last bit to 0
		push %eax #save eax
		push $1
		push $MINUS
		call print
		addl $8, %esp #restore stack pointer for 2 arguments
		pop %eax #get back value
		loop:
			movl $0, %edx #MSByte
			movl $10, %ebx
			idiv %ebx #eax=edx:eax/ebx; # edx=edx:eax MOD ebx 13/10=1, 13 mod 10 = 3 => push 3 on stack, 1 is in eax
			addl $48, %edx #add 48, check ASCII, zero is 48
			pushl %edx
			incl COUNTER #increment by one
			cmpl $0, %eax
			jz   printN #if zero then we have to print otherwise loop
			jmp loop

		printN:
			cmpl $0, COUNTER
			jz   return
			decl COUNTER
			movl $4, %eax
			movl $1, %ebx
			movl $1, %edx #how many bytes
			movl %esp, %ecx #ecx should contain pointer to ascii
			int  $0x80
			addl $4, %esp #decrease stack size, get next number on stack
			jmp  printN
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
	push	$732
	pop	a
	push	$2684
	pop	b
L000:
	push	a
	push	b
	pop TEMP1
	pop %eax
	cmp TEMP1,%eax
	je	L001
	push	a
	push	b
	pop TEMP1
	pop %eax
	cmp TEMP1,%eax
	jle	L002
	push	a
	push	b
	pop TEMP1
	pop %eax
	sub TEMP1, %eax
	push %eax

	pop	a
	jmp	L003
L002:
	push	b
	push	a
	pop TEMP1
	pop %eax
	sub TEMP1, %eax
	push %eax

	pop	b
L003:
	jmp	L000
L001:
	push	a
	pop %eax
	call printNumber
	push $1
	push $NEWLINE
	call print
	addl $8, %esp
	push	a
	push	b
	call gcd
	push %eax
	pop %eax
	call printNumber
	push $1
	push $NEWLINE
	call print
	addl $8, %esp
exit:
	movl $0,%ebx # first argument: exit code
	movl $1,%eax # system call number (sys_exit)
	int $0x80 # call kernel

