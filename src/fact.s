.text
	.globl fact
	.type fact, @function
	fact:
		movl	4(%esp), %ecx	# get the parameter
		movl	$1, %eax	# eax = 1
	l1:
		mull	%ecx		# eax *= ecx
		loop 	l1		# Decrement ecx, go to l1 while ecx != 0
		ret

