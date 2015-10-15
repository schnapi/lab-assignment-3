#include <stdio.h>
#include <string.h>
#include "calc3.h"
#include "y.tab.h"

static int lbl;
static int i=0;
char jmpType[4];

// here we need replace push, pop,... with i386 assembler instructions
//You will need to allocate space for the symbol table and emit some
/*header for the assembly then the instructions that make up the code and then*/
/*a few lines to clean up, s*/
int ex(nodeType *p) {
    int lbl1, lbl2;
    //print assembly header
    if(i++==0) {
    	char *initialisedData = ".data # Initialised data\n\tNEWLINE: .asciz \"\\n\"\n\tMINUS: .asciz \"-\"";
    	printf(".code32\n%s\n.bss #uninitialised data\n",initialisedData);
    	puts("\t.lcomm COUNTER, 4\n\t.lcomm TEMP1, 4");
    	//print variables
    	char c;
		  for(c='a'; c<='z'; ++c)
		     printf("\t.lcomm %c,4\n",c);
			printf(".text\n.globl _start # _start on linux\n");	
			char *types="\t.type print, @function\n\t.type printNumber, @function\n\t.type gcd, @function\n";
			char* printNumber="\tprintNumber:\n\t\tmovl $0, COUNTER\n\t\tcmpl $0, %eax #is it negative number\n\t\tjge loop #if eax is greater or equal zero then go to loop\n\t\tneg %eax #change last bit to 0\n\t\tpush %eax #save eax\n\t\tpush $1\n\t\tpush $MINUS\n\t\tcall print\n\t\taddl $8, %esp #restore stack pointer for 2 arguments\n\t\tpop %eax #get back value\n\t\tloop:\n\t\t\tmovl $0, %edx #MSByte\n\t\t\tmovl $10, %ebx\n\t\t\tidiv %ebx #eax=edx:eax/ebx; # edx=edx:eax MOD ebx 13/10=1, 13 mod 10 = 3 => push 3 on stack, 1 is in eax\n\t\t\taddl $48, %edx #add 48, check ASCII, zero is 48\n\t\t\tpushl %edx\n\t\t\tincl COUNTER #increment by one\n\t\t\tcmpl $0, %eax\n\t\t\tjz   printN #if zero then we have to print otherwise loop\n\t\t\tjmp loop\n\n\t\tprintN:\n\t\t\tcmpl $0, COUNTER\n\t\t\tjz   return\n\t\t\tdecl COUNTER\n\t\t\tmovl $4, %eax\n\t\t\tmovl $1, %ebx\n\t\t\tmovl $1, %edx #how many bytes\n\t\t\tmovl %esp, %ecx #ecx should contain pointer to ascii\n\t\t\tint  $0x80\n\t\t\taddl $4, %esp #decrease stack size, get next number on stack\n\t\t\tjmp  printN\n\t\treturn:\n\t\t\tret\n";
			char* print="\n\tprint:\n\t\tmovl $4, %eax\n\t\tmovl $1, %ebx\n\t\tmovl 4(%esp), %ecx #point to first argument which is on the stack\n\t\tmovl 8(%esp), %edx #point to first argument which is on the stack\n\t\tint $0x80 # call kernel\n\t\tret #change eip to start next instruction\n";
			char* gcd = "\tgcd:\n\t\tmovl 8(%esp), %eax #get first parameter\n\t\tmovl 4(%esp), %edx #get second parameter\n\t\tstart:\n\t\t\tcmp %eax, %edx\n\t\t\tje\tend\n\t\t\tcmp %edx, %eax\n\t\t\tjg\tmiddle #if eax > edx then jmp\n\t\t\tsub %eax, %edx #assign edx\n\t\t\tjmp\tstart\n\t\tmiddle:\n\t\t\tsub %edx, %eax #assign eax\n\t\t\tjmp\tstart\n\t\tend:\n\t\t\tret\n";
			printf("%s%s%s%s",types,printNumber, print,gcd);
			printf("_start:\n");
		}
    if (!p) return 0;
    switch(p->type) {
    case typeCon:       
        printf("\tpush\t$%d\n", p->con.value); 
        break;
    case typeId:
        printf("\tpush\t%c\n", p->id.i + 'a'); 
        break;
    case typeOpr:
        switch(p->opr.oper) {
        case WHILE:
            printf("L%03d:\n", lbl1 = lbl++);
            ex(p->opr.op[0]);
            printf("\t%s\tL%03d\n",jmpType, lbl2 = lbl++);
            ex(p->opr.op[1]);
            printf("\tjmp\tL%03d\n", lbl1);
            printf("L%03d:\n", lbl2);
            break;
        case IF:
            ex(p->opr.op[0]);
            if (p->opr.nops > 2) {
                /* if else */
                printf("\t%s\tL%03d\n",jmpType, lbl1 = lbl++);
                ex(p->opr.op[1]);
                printf("\tjmp\tL%03d\n", lbl2 = lbl++);
                printf("L%03d:\n", lbl1);
                ex(p->opr.op[2]);
                printf("L%03d:\n", lbl2);
            } else {
                /* if */
                printf("\t%s\tL%03d\n",jmpType, lbl1 = lbl++);
                ex(p->opr.op[1]);
                printf("L%03d:\n", lbl1);
            }
            break;
        case PRINT:     
            ex(p->opr.op[0]);
            puts("\tpop %eax");
            printf("\tcall printNumber\n");
            //print new line
            puts("\tpush $1\n\tpush $NEWLINE\n\tcall print");
            break;
        case '=':       
            ex(p->opr.op[1]);
            printf("\tpop\t%c\n", p->opr.op[0]->id.i + 'a');
            break;
        case UMINUS:    
            ex(p->opr.op[0]);
            puts("\tpop %eax\n\tneg %eax\n\tpush %eax");
            break;
	case FACT:
  	    ex(p->opr.op[0]);
	    printf("\tfact\n");
	    break;
	case LNTWO:
	    ex(p->opr.op[0]);
	    printf("\tlntwo\n");
	    break;
        default:
            ex(p->opr.op[0]);
            ex(p->opr.op[1]);
            switch(p->opr.oper) {
	    case GCD:   puts("\tcall gcd\n\tpush %eax"); break;
	    			//get from the stack and save into TEMP1 then into eax and add TEMP1 to eax, push on the stack
            case '+':   puts("\tpop TEMP1\n\tpop %eax\n\tadd TEMP1, %eax\n\tpush %eax\n"); break;
            case '-':   puts("\tpop TEMP1\n\tpop %eax\n\tsub TEMP1, %eax\n\tpush %eax\n"); break;
            case '*':   puts("\tpop TEMP1\n\tpop %eax\n\timul TEMP1, %eax\n\tpush %eax\n"); break;
            case '/':   puts("\tpop TEMP1\n\tpop %eax\n\tidiv TEMP1, %eax\n\tpush %eax\n"); break;
            case '<':   puts("\tpop TEMP1\n\tpop %eax\n\tcmp %eax, TEMP1"); strcpy (jmpType,"jl\0"); break;
            case '>':   puts("\tpop TEMP1\n\tpop %eax\n\tcmp %eax, TEMP1"); strcpy (jmpType,"jg\0"); break;
            case GE:    puts("\tpop TEMP1\n\tpop %eax\n\tcmp %eax, TEMP1"); strcpy (jmpType,"jge\0"); break;
            case LE:    puts("\tpop TEMP1\n\tpop %eax\n\tcmp %eax, TEMP1"); strcpy (jmpType,"jle\0"); break;
            case NE:    puts("\tpop TEMP1\n\tpop %eax\n\tcmp %eax, TEMP1"); strcpy (jmpType,"je\0"); break;
            case EQ:    puts("\tpop TEMP1\n\tpop %eax\n\tcmp %eax, TEMP1"); strcpy (jmpType,"jne\0"); break;
            }
        }
    }
    return 0;
}
