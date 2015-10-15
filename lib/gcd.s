gcd:
	movl 8(%esp), %eax #get first parameter
	movl 4(%esp), %edx #get second parameter
	start:
		cmp %eax, %edx
		je	end
		cmp %edx, %eax
		jg	middle #if eax > edx then jmp
		sub %eax, %edx #assign edx
		jmp	start
	middle:
		sub %edx, %eax #assign eax
		jmp	start
	end:
		ret
