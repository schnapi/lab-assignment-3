#include <stdio.h>
#include "calc3.h"
#include "y.tab.h"

static int lbl;
static int i=0;

// here we need replace push, pop,... with i386 assembler instructions
//You will need to allocate space for the symbol table and emit some
/*header for the assembly then the instructions that make up the code and then*/
/*a few lines to clean up, s*/
int ex(nodeType *p) {
    int lbl1, lbl2;
    //print assembly header
    if(i++==0) {
    	char *initialisedData = ".data # Initialised data\n\tNEWLINE: .asciz \"\\n\"";
    	printf(".code32\n%s\n.bss #uninitialised data\n",initialisedData);
    	puts("\t.lcomm TEMP1, 4");
    	//print variables
    	char c;
		  for(c='a'; c<='z'; ++c)
		     printf("\t.lcomm %c,1\n",c);
			printf(".text\n.globl _start # _start on linux\n");	
			char *types="\t.type print, @function\n\t.type printNumber, @function";
			char* printNumber="\n\tprintNumber:\n\t\tloop:\n\t\t\tmovl $0, %edx\n\t\t\tmovl $10, %ebx\n\t\t\tdivl %ebx\n\t\t\taddl $48, %edx\n\t\t\tpushl %edx\n\t\t\tincl %esi\n\t\t\tcmpl $0, %eax\n\t\t\tjz   next\n\t\t\tjmp loop\n\n\t\tnext:\n\t\t\tcmpl $0, %esi\n\t\t\tjz   return\n\t\t\tdecl %esi\n\t\t\tmovl $4, %eax\n\t\t\tmovl %esp, %ecx\n\t\t\tmovl $1, %ebx\n\t\t\tmovl $1, %edx\n\t\t\tint  $0x80\n\t\t\taddl $4, %esp\n\t\t\tjmp  next \n\t\treturn:\n\t\t\tret";
			char* print="\n\tprint:\n\t\tmovl $4, %eax\n\t\tmovl $1, %ebx\n\t\tmovl 4(%esp), %ecx #point to first argument which is on the stack\n\t\tmovl 8(%esp), %edx #point to first argument which is on the stack\n\t\tint $0x80 # call kernel\n\t\tret #change eip to start next instruction";
			printf("%s%s%s\n",types,printNumber, print);
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
            printf("\tjz\tL%03d\n", lbl2 = lbl++);
            ex(p->opr.op[1]);
            printf("\tjmp\tL%03d\n", lbl1);
            printf("L%03d:\n", lbl2);
            break;
        case IF:
            ex(p->opr.op[0]);
            if (p->opr.nops > 2) {
                /* if else */
                printf("\tjz\tL%03d\n", lbl1 = lbl++);
                ex(p->opr.op[1]);
                printf("\tjmp\tL%03d\n", lbl2 = lbl++);
                printf("L%03d:\n", lbl1);
                ex(p->opr.op[2]);
                printf("L%03d:\n", lbl2);
            } else {
                /* if */
                printf("\tjz\tL%03d\n", lbl1 = lbl++);
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
            printf("\tneg\n");
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
	    case GCD:   printf("\tgcd\n"); break;
	    			//get from the stack and save into TEMP1 then into eax and add TEMP1 to eax, push on the stack
            case '+':   puts("\tpop TEMP1\n\tpop %eax\n\tadd TEMP1, %eax\n\tpush %eax\n"); break;
            case '-':   printf("\tsub\n"); break; 
            case '*':   printf("\tmul\n"); break;
            case '/':   printf("\tdiv\n"); break;
            case '<':   printf("\tcompLT\n"); break;
            case '>':   printf("\tcompGT\n"); break;
            case GE:    printf("\tcompGE\n"); break;
            case LE:    printf("\tcompLE\n"); break;
            case NE:    printf("\tcompNE\n"); break;
            case EQ:    printf("\tcompEQ\n"); break;
            }
        }
    }
    return 0;
}
