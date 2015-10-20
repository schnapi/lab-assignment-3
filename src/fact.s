.text
    .globl fact
    .type fact, @function
    fact:
        movl   4(%esp), %ecx     # get first parameter
        movl   $1, %eax          # eax <- 1
    l1: mull   %ecx              # %eax <- %eax * %ecx
        loop   l1                # %ecx--, jump to l1 if %ecx != 0
        ret

