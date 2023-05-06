#include"intercode.hpp"
int main(int argc, char **argv)
{
    std::ofstream out("tree.txt");
    std::string s1 = "abc";
    std::string s2 = "bda";
    Operand x1 = newOperand(OP_READ_ADDRESS,s1);
    Operand x2 = newOperand(OP_VARIABLE,s2);
    InterCode x = newAssign(IC_ASSIGN, x1,x2);
    InterCodeList l1 = newICList();
    add_ICList(l1,x);
    printInterCodes(out,l1);
    return 0;
}