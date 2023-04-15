#include "syntaxNode.hpp"
int main() {
    tree node1 = buildTree(0,1,true,"INT","1");
    tree node2 = buildTree(0,1,true,"FLOAT","1.2");
    tree node3 = buildTree(0,1,true,"ASSIGNOP","=");
    tree node4 = buildTree(0,1,true,"REOP",">");

    tree left = buildTree(2,1,false,"Specifier",NO_VALUE,node1,node2);
    tree right = buildTree(2,1,false,"ExtList",NO_VALUE,node3,node4);
    tree root = buildTree(2,1,false,"Program",NO_VALUE,left,right);
    printTree(root);
    return 0;
}