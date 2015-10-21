.text
	.globl lntwo
	.type lntwo, @function
		lntwo:
			movl	4(%esp), %ebx	# get the parameter
			cmp	$0, %ebx	# if parameter <= 0
			jle	lezero		# jump & return 0 
			bsr	%ebx, %eax	# BSF searches for the first set bit in %ebx (starting from the most significant bit), and stores it in %eax
			ret
    		lezero:				# returns 0
			movl $0, %eax
			ret
