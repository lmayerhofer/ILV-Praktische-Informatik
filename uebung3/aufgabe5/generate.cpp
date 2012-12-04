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
                unsigned exponent = right->eval();
                for(unsigned i = 0; i < exponent; i++) {
                    result *= base;
                }
                return result;
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

    void gen_x86_64() const {
        switch (type) {
            case NUMBER:
                printf("\tmovl\t$%d, %%eax\n", value);
                break;
            case PLUS:
                left->gen_x86_64();
                printf("\tpushq\t%%rax\n");
                right->gen_x86_64();
                printf("\tpopq\t%%rbx\n");
                printf("\taddl\t%%ebx, %%eax\n");
                break;
            case MINUS:
                left->gen_x86_64();
                printf("\tpushq\t%%rax\n");
                right->gen_x86_64();
                printf("\tpopq\t%%rbx\n");
                printf("\tsubl\t%%eax, %%ebx\n");
                printf("\tmovl\t%%ebx, %%eax\n");
                break;
            case MULT:
                left->gen_x86_64();
                printf("\tpushq\t%%rax\n");
                right->gen_x86_64();
                printf("\tpopq\t%%rbx\n");
                printf("\tmull\t%%ebx\n");
                break;
            default:
                throw "gen x86_64 failed";
        }
    }

    void gen_x86() const {
        switch (type) {
            case NUMBER:
                printf("\tmovl\t$%d, %%eax\n", value);
                break;
            case PLUS:
                left->gen_x86();
                printf("\tpushl\t%%eax\n");
                right->gen_x86();
                printf("\tpopl\t%%ebx\n");
                printf("\taddl\t%%ebx, %%eax\n");
                break;
            case MINUS:
                left->gen_x86();
                printf("\tpushl\t%%eax\n");
                right->gen_x86();
                printf("\tpopl\t%%ebx\n");
                printf("\tsubl\t%%eax, %%ebx\n");
                printf("\tmovl\t%%ebx, %%eax\n");
                break;
            case MULT:
                left->gen_x86();
                printf("\tpushl\t%%eax\n");
                right->gen_x86();
                printf("\tpopl\t%%ebx\n");
                printf("\tmull\t%%ebx\n");
                break;
            case POW:
                // move value/operand to eax
                left->gen_x86();
                // move value of eax (left value/operand) to ebx (base register)
                printf("\tmovl\t%%eax, %%ebx\n");
                
                // move value/operand to eax
                right->gen_x86();
                // move value of eax (right value/operand) to ecx (counter register)
                printf("\tmovl\t%%eax, %%ecx\n");
                
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
                left->gen_x86();
                
                // move value/operand to eax
                right->gen_x86();
                // move value of eax (left value/operand) to edx
                printf("\tmovl\t%%eax, %%edx\n");
                
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

    void gen_expr_x86_64() const {
        fprintf(stderr, "generating x86-64 code\n");

        printf("\t.text\n");
        printf("\t.globl calc_expr\n");
        printf("calc_expr:\n");

        gen_x86_64();

        printf("\tretq\n");
    }

    void gen_expr_x86() const {
        fprintf(stderr, "generating x86 code\n");

        printf("\t.text\n");
        printf("\t.globl calc_expr\n");
        printf("calc_expr:\n");
        // most first variable from stack to edi
        printf("\tmovl\t4(%%esp), %%edi\n");

        gen_x86();

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
            ir = new IRNode(IRNode::MINUS,
            new IRNode(IRNode::MULT, new IRNode(5), new IRNode(3)),
            new IRNode(4));
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            ir = new IRNode(IRNode::POW, new IRNode(3), new IRNode(4));
            break;
        case 5:
            ir = new IRNode(IRNode::MAX, new IRNode(2), new IRNode(10));
            break;
        default:
            throw "main switch failed";
    }

    fprintf(stderr, "eval(interpreted) = %d\n", ir->eval());

    if (ir) {
        if (sizeof(void *) == 8)
            ir->gen_expr_x86_64();
        else if (sizeof(void *) == 4)
            ir->gen_expr_x86();
        else
            throw "unknown architecture";
    }

    return EXIT_SUCCESS;
}