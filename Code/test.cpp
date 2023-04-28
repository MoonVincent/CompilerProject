#include"intercode.hpp"
int main(int argc, char **argv)
{
    std::ofstream out("tree.txt");
    InterCodeList head;
    std::string s1 = "abc";
    std::string s2 = "bda";
    Operand x1 = newOperand(VARIABLE_OP,s1);
    Operand x2 = newOperand(VARIABLE_OP,s2);
    InterCode x = newAssign(ASSIGN, x1,x2);
    add_ICList(head,x);
    printInterCodes(out,head);
    return 0;
}