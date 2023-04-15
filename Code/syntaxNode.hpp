#include <stdarg.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#define NO_VALUE ""
typedef struct treeNode* tree;
/**
 * @功能:抽象语法树的结点定义
 * @param:
 * lineNo:当前语法单元所处行号
 * childCnt:节点的子节点数量
 * children:存储指向子节点的指针
 * isToken:当前节点存储的是否为一个token/terminals
 * key:当前节点对应的名称，如INT、Program...
 * value:节点内存储的值，只有isToken为true时，才会存储value
 */
struct treeNode{
    int lineNo;
    int childCnt;
    std::string key;
    std::string value;
    bool isToken;
    struct treeNode** children;
    treeNode() {
        lineNo = 0;
        childCnt = 0;
        children = nullptr;
        isToken = false;
    }
};

/**
 * @brief 新建一个子树
 * 
 * @param childCnt 根节点的子节点数量
 * @param lineNo token所处的行号，如果要返回的根节点不存储token，则赋值为-1
 * @param isToken 根节点存储的是否是token
 * @param key 根节点名称，如INT、Program...
 * @param value 对应的值，只有存储token时才会有值
 * @param ... 指向子节点的指针，根据情况不同有任意个
 * @return tree 返回新子树的根节点
 */

tree buildTree(int childCnt, int lineNo, bool isToken, std::string key, std::string value, ...){

    tree newTree = new treeNode();
    newTree->lineNo = lineNo;
    newTree->isToken = isToken;
    newTree->key = key;
    newTree->value = value;
    
    va_list children;
    va_start(children, childCnt);
    newTree->childCnt = childCnt;
    newTree->children = (tree*)malloc(sizeof(tree) * childCnt);
    for(int i = 0; i < childCnt; ++i) {
        newTree->children[i] = va_arg(children, tree);
    }
    va_end(children);
    return newTree;
}

/**
 * @brief 深度优先，输出每个子节点到tree.txt中
 * 
 * @param root 当前要输出的子树根节点
 * @param out tree.txt的输出流
 */

void printDFS(tree root, std::ofstream &out) {
    if (root == nullptr) {
        return;
    }

    if (root->isToken) {
        out << "[^" << root->key << " Value:" << root->value << " line:" << root->lineNo << "]";
        return; 
    }

    out << "[" << root->key;
    for (int i = 0; i < root->childCnt; ++i) {
        printDFS(root->children[i], out);
    }
    out << "]";
    return;
}

/**
 * @brief 将给定的树按一定格式输出至tree.txt,用于树的可视化
 * 
 * @param root:指定树的根节点
 */

void printTree(tree root) {
    std::ofstream out("tree.txt");
    printDFS(root,out);
}






