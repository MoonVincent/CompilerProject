#include "semantic.hpp"
#include "syntaxNode.hpp"
#include "type.hpp"
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <algorithm>

void semantic(tree syntaxTree){
   ExtDefList(syntaxTree->children[0]); 
}

void ExtDefList(tree root){
    if (root == nullptr) return ;
    ExtDef(root->children[0]);
    ExtDefList(root->children[1]);
}

void ExtDef(tree root){
    Type type = Specifier(root->children[0]);
    if (root->children[1]->key == "ExtDecList") {
        std::list<std::string> record;
        ExtDecList(type, root->children[1], record);
    } else if (root->children[1]->key == "FunDec") {
        std::list<std::string> record;
        FunDec(type, root->children[1], record);
        CompSt(root->children[2], record);
    }
}

void ExtDecList(Type type, tree root, std::list<std::string>& record) {
    VarDec(type, root->children[0], record);
    if (root->children[1]) {
        ExtDecList(type, root->children[2], record);
    }
}

Type Specifier(tree root){
    Type type;
    if (root->children[0]->key == "TYPE") {
        if (root->children[0]->value == "int") {
            type = newBasic(INT);
        } else {
            type = newBasic(FLOAT);
        }
    } else {
        type = StructSpecifier(root->children[0]);
    }
    return type;
}

Type StructSpecifier(tree root) {
    Type type;
    if (root->children[1]->key == "OptTag") {
        std::string optag = OptTag(root->children[1]);
        //TODO:

    } else if (root->children[1]->key == "Tag") {
        std::string tag = Tag(root->children[1]);
        Type tagType = getType(tag);
        if (tagType == nullptr) {
            std::cout << "Undefined reference to " << tag << "in line" << std::to_string(root->children[1]->lineNo) << "\n";
            exit(1);
        }
    } else {

    }
}

std::string OptTag(tree root) {
    return root->children[0]->value;
}

std::string Tag(tree root) {
    return root->children[0]->value;
}

void VarDec(Type type, tree root, std::list<std::string>& record) {

    if (root->children[0]->key == "ID") {
        //检查当前域内是否已经对该变量有过定义
        auto iter = std::find(record.begin(), record.end(), root->children[0]->value);
        if (iter != record.end()) {
            std::cout << "Multiple definition" << "\n";
            exit(1);
        }
        //TODO:也许可以简化
        if (!insertType(root->children[0]->value, type)) {
            std::cout << "Multiple definition of " << root->children[0]->value << "in line" << std::to_string(root->children[0]->lineNo) << "\n";
            exit(1);
        }
        //记录当前域内已定义变量的名字
        record.push_back(root->children[0]->value);
    } else {    //数组定义
        int elemSize = atoi(root->children[2]->value.c_str());
        Type innerType= newArray(type, elemSize);
        //递归直至遇到函数名
        VarDec(innerType, root->children[0], record);
    }
}

void FunDec(Type rv_type, tree root, std::list<std::string>& record) {

    std::string func_name = root->children[0]->value;
    std::vector<Type> paramList;
    if (root->children[2]->key == "VarList") {
        VarList(paramList,root->children[2], record);
    }
    Type type = newFunc(rv_type, paramList);
    if (!insertType(func_name, type)) {
        std::cout << "Multiple definition of" << "\n";
    }
}


void VarList(std::vector<Type>& paramList, tree root, std::list<std::string>& record) {

    ParamDec(paramList, root->children[0], record);

    if (root->children[1]) {
        VarList(paramList, root->children[2], record);
    }
}

void ParamDec(std::vector<Type>& paramList, tree root, std::list<std::string>& record) {

    Type type = Specifier(root->children[0]);
    VarDec(type, root->children[1], record);
    //从record中取避免传数组出错，但似乎并无必要
    //paramList.push_back(getType(record.back()));
    paramList.push_back(type);

}

void CompSt(tree root, std::list<std::string>& record) {
    DefList(root->children[1], record);
    StmtList(root->children[2]);
    while (!record.empty()) {
        deleteType(record.back());
        record.pop_back();
    }

}

void StmtList(tree root) {
    if (root == nullptr) return ;
    Stmt(root->children[0]);
    StmtList(root->children[1]);
}

void Stmt(tree root) {
    if (root->children[0]->key == "Exp") {
        Exp(root->children[0]);
    } else if (root->children[0]->key == "CompSt") {
        std::list<std::string> record;
        CompSt(root->children[0], record);
    } else if (root->children[0]->key == "RETURN") {
        Exp(root->children[1]);
    } else if (root->children[0]->key == "WHILE") {
        Exp(root->children[2]);
    } else {
        Exp(root->children[2]);
        if (root->children[5]) {
            Stmt(root->children[6]);
        }
    }
}

void DefList(tree root, std::list<std::string>& record) {
    if(root == nullptr) return ;
    Def(root->children[0], record);
    DefList(root->children[1], record);
}

void Def(tree root, std::list<std::string>& record) {
    Type type = Specifier(root->children[0]);
    DecList(type, root->children[1]);
}

void DecList(Type type, tree root, std::list<std::string>& record) {
    Dec(type, root->children[0], record);
    if (root->children[2]){
        DecList(type, root->children[0], record);
    }
}

void Dec(Type type, tree root, std::list<std::string>& record) {
    
    
    if (root->children[2]) {    //存在ASSIGNOP
        
    } else {
        VarDec(type, root->children[0], record);
    }
}

Type Exp(tree root) {
    if (root->childCnt == 1) {
        if (root->children[0]->key == "ID") {
            return getType(root->children[0]->value);
        } else if (root->children[0]->key == "INT") {
            return newBasic(INT);
        } else {
            return newBasic(FLOAT);
        }
    } else if (root->childCnt == 3) {
        if (root->children[0]->key == "Exp") {
            if (root->children[1]->key == "ASSIGNOP") { //Exp ASSIGNOP Exp

            } else if (root->children[1]->key == "DOT") {   //Exp DOT ID

            } else {

            }
            
        } else if (root->children[0]->key == "LP"){    //LP Exp RP
            return Exp(root->children[1]);
        } else {    //ID LP RP

        }
    } else if (root->childCnt == 2) {   //MINUS Exp /  NOT Exp

    } else if (root->childCnt == 4) {
        if (root->children[0]->key == "ID") {   // ID LP Args RP

        } else {    //Exp LB Exp RB

        }
    } else {    //ID / INT / FLOAT

    }
}

void Args(){

}



