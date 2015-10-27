#include <stdio.h>
#include "calc3.h"
#include "y.tab.h"

static int lbl;

int ex(nodeType *p) {
    if (!p) return 0;
    switch (p->type) {
        case typeCon:
            printf("push(%d);\n", p->con.value);
            break;
        case typeId:
            printf("push(%c);\n", p->id.i + 'a');
            break;
        case typeOpr:
            switch (p->opr.oper) {
                case WHILE:
                    ex(p->opr.op[0]);
                    printf("while(pop()){\n");
                    ex(p->opr.op[1]);
                    ex(p->opr.op[0]);
                    printf("}\n");
                    break;
                case IF:
                    ex(p->opr.op[0]);
                    if (p->opr.nops > 2) {
                        /* if else */
                        printf("if(pop()){\n");
                        ex(p->opr.op[1]);
                        printf("}else{\n");
                        ex(p->opr.op[2]);
                        printf("}\n");
                    } else {
                        /* if */
                        printf("if(pop()){\n");
                        ex(p->opr.op[1]);
                        printf("}\n");
                    }
                    break;
                case PRINT:
                    ex(p->opr.op[0]);
                    printf("print();\n");
                    break;
                case '=':
                    ex(p->opr.op[1]);
                    printf("%c = pop();\n", p->opr.op[0]->id.i + 'a');
                    break;
                case UMINUS:
                    ex(p->opr.op[0]);
                    printf("neg();\n");
                    break;
                case FACT:
                    ex(p->opr.op[0]);
                    printf("fact();\n");
                    break;
                case LNTWO:
                    ex(p->opr.op[0]);
                    printf("lntwo();\n");
                    break;
                default:
                    ex(p->opr.op[0]);
                    ex(p->opr.op[1]);
                    switch (p->opr.oper) {
                        case GCD: printf("gcd();\n");
                            break;
                        case '+': printf("add();\n");
                            break;
                        case '-': printf("sub();\n");
                            break;
                        case '*': printf("mul();\n");
                            break;
                        case '/': printf("divide();\n");
                            break;
                        case '<': printf("compLT();\n");
                            break;
                        case '>': printf("compGT();\n");
                            break;
                        case GE: printf("compGE();\n");
                            break;
                        case LE: printf("compLE();\n");
                            break;
                        case NE: printf("compNE();\n");
                            break;
                        case EQ: printf("compEQ();\n");
                            break;
                    }
            }
    }
    return 0;
}
