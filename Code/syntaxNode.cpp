#include "syntaxNode.hpp"
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
    
    if (childCnt > 0) {
        va_list children;
        va_start(children, childCnt);
        newTree->childCnt = childCnt;
        newTree->children = (tree*)malloc(sizeof(tree) * childCnt);
        for(int i = 0; i < childCnt; ++i) {
            newTree->children[i] = va_arg(children, tree);
        }
        va_end(children);
    }

    return newTree;
}

/**
 * @brief 深度优先，输出每个子节点到tree.txt中
 * 
 * @param root 当前要输出的子树根节点
 * @param out tree.txt的输出流
 */

/*void printDFS(tree root, std::ofstream &out) {
    if (root == nullptr) {
        return;
    }

    if (root->isToken && root->children == nullptr) {
        out << "[^" << root->key << " Value:" << root->value << " line:" << root->lineNo << "]";
        return; 
    }

    out << "[" << root->key;
    for (int i = 0; i < root->childCnt; ++i) {
        printDFS(root->children[i], out);
    }
    out << "]";
    return;
}*/
void printDFS(tree root, std::ofstream &out) {
    if (root == nullptr) {
        return;
    }

    if (root->isToken && root->children == nullptr) {
        out << "[#Key:" << root->key << "\\" << "\n";
        out << "Value:";
        for (auto ch : root->value) {
            if ((ch <'a' || ch >'z') && (ch <'A' || ch >'Z')){
                out << "\\";
            }
            if (ch == '[') out << "-";
            else if (ch == ']') out << "+"; 
            else out << ch;
        }
        out << "]";
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