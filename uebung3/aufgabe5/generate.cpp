#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <string.h>

struct IRNode {
    typedef enum {PLUS, MINUS, MULT, POW, MAX, NUMBER} nodetype;

    IRNode(nodetype t, IRNode *l, IRNode *r) : type(t), value(-1), left(l), right(r) { }
    IRNode(unsigned v) : type(NUMBER), value(v), left(0), right(0) { }

    unsigned eval() const {
        switch (type) {
            case NUMBER: return value;
            case PLUS: return left->eval() + right->eval();
            case MINUS: return left->eval() - right->eval();
            case MULT: return left->eval() * right->eval();
            case POW:
            {
                unsigned result = 1;
                unsigned base = left->eval();
                if(right->eval() > 0) {
                    unsigned exponent = right->eval();
                    for(unsigned i = 0; i < exponent; i++) {
                        result *= base;
                    }
                    return result;
                } else {
                    fprintf(stderr, "\nERROR: Exponent must be a positive number (greater than 0).\n");
                    return 0;   // if exponent smaller or equal to 0
                }
            }
            case MAX:
            {
                unsigned leftValue = left->eval();
                unsigned rightValue = right->eval();
                return rightValue >= leftValue ? rightValue : leftValue;
            }
            default: throw "eval failed";
        }
    }

    void generate_x86() const {
        switch (type) {
            case NUMBER:
                printf("\tmovl\t$%d, %%eax\n", value);
                break;
            case PLUS:
                left->generate_x86();
                printf("\tpushl\t%%eax\n");
                right->generate_x86();
                printf("\tpopl\t%%ebx\n");
                printf("\taddl\t%%ebx, %%eax\n");
                break;
            case MINUS:
                left->generate_x86();
                printf("\tpushl\t%%eax\n");
                right->generate_x86();
                printf("\tpopl\t%%ebx\n");
                printf("\tsubl\t%%eax, %%ebx\n");
                printf("\tmovl\t%%ebx, %%eax\n");
                break;
            case MULT:
                left->generate_x86();
                printf("\tpushl\t%%eax\n");
                right->generate_x86();
                printf("\tpopl\t%%ebx\n");
                printf("\tmull\t%%ebx\n");
                break;
            case POW:
                // move value/operand to eax
                right->generate_x86();
                
                // move 0 to ebx (base register)
                // printf("\tmovl\t$0, %%ebx\n");

                // compare value from eax with 0
                printf("\tcmp\t$0, %%eax\n");

                // if right (eax) not greater => return
                printf("\tja greater\n");

                printf("\tmovl\t$0, %%eax\n");                
                printf("\tretl\n");

                // else: move value from eax to ecx
                printf("\tgreater:");
                // move value from eax (right value/operand) to ecx (counter register)
                printf("\tmovl\t%%eax, %%ecx\n");
                
                // move value/operand to eax
                left->generate_x86();
                // move value from eax (left value/operand) to ebx (base register)
                printf("\tmovl\t%%eax, %%ebx\n");

                // move 1 to eax (accumulator register)
                printf("\tmovl\t$1, %%eax\n");

                // start code block "loop_start"
                printf("loop_start:");
                // multiply value of ebx with value of eax and safe it in ebx
                printf("\tmull\t%%ebx\n");
                // loop
                printf("\tloop loop_start\n");
                break;
            case MAX:
                // move value/operand to eax
                left->generate_x86();
                printf("\tmovl\t%%eax, %%edx\n");

                // move value/operand to eax
                right->generate_x86();
                // move value of eax (left value/operand) to edx
                
                // compare value from eax with value from edx
                printf("\tcmp\t%%eax, %%edx\n");

                // if left (eax) not greater or euqal => do nothing (return)
                printf("\tjae greater_equal\n");
                //printf("\tretl\n");

                // else: move value from edx to eax
                printf("\tgreater_equal:");
                printf("\tmovl\t%%edx, %%eax\n");
                break;
            default:
                throw "gen x86 failed";
        }
    }

    void generate_expr_x86() const {
        fprintf(stderr, "generating x86 code...\n\n");

        printf("\t.text\n");
        printf("\t.globl calc_expr\n");
        printf("calc_expr:\n");
        // most first variable from stack to edi
        printf("\tmovl\t4(%%esp), %%edi\n");

        generate_x86();

        printf("\tretl\n");
    }

    nodetype type;
    unsigned value;
    IRNode *left, *right;
};

int main(int argc, const char* argv[]) {
    // get terminal arguments (argv string) and convert to int
    int operatorChoice = atoi(argv[1]);

    IRNode *ir = NULL;

    switch(operatorChoice) {
        case 1:
            fprintf(stderr, "\n6 ^ 3:\n");
            ir = new IRNode(IRNode::POW, new IRNode(6), new IRNode(3));
            break;
        case 2:
            fprintf(stderr, "\n6 ^ 0:\n");
            ir = new IRNode(IRNode::POW, new IRNode(6), new IRNode(0));
            break;
        case 3:
            fprintf(stderr, "\nMaximum von 21 und 14\n");
            ir = new IRNode(IRNode::MAX, new IRNode(21), new IRNode(14));
            break;
        default:
            throw "main switch failed";
    }

    fprintf(stderr, "interpreted: %d\n", ir->eval());

    if (ir) {
        if (sizeof(void *) == 4)
            ir->generate_expr_x86();
        else
            throw "architecture not supported";
    }

    return EXIT_SUCCESS;
}