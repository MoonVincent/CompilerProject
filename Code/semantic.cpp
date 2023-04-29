#include "semantic.hpp"
#include "global.hpp"


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
            type = newBasic(INT_SEMA);
        } else {
            type = newBasic(FLOAT_SEMA);
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
        std::list<std::string> names; 
        std::unordered_map<std::string, Type> s_field;
        DefList(root->children[3], names);
        for (auto name : names) {
            Type cur_type = getItem(name);
            s_field.insert({name, cur_type});
            deleteItem(name);
        }
        type = newStructure(s_field);
    } else if (root->children[1]->key == "Tag") {
        std::string tag = Tag(root->children[1]);
        type = getItem(tag);
        if (type == nullptr) {
            std::cout << "[line " << root->children[1]->lineNo <<" semantic error] "
                      << "Undefined reference to the struct " << tag << std::endl;

        }
    }
    return type;
}

std::string OptTag(tree root) {
    return root->children[0]->value;
}

std::string Tag(tree root) {
    return root->children[0]->value;
}

int VarDec(Type type, tree root, std::list<std::string>& record) {

    if (root->children[0]->key == "ID") {
        //检查当前域内是否已经对该变量有过定义
        auto iter = std::find(record.begin(), record.end(), root->children[0]->value);
        if (iter != record.end()) {
            std::cout << "[line " << root->children[0]->lineNo <<" semantic error] "
                      << "Multiple definition of variable " << root->children[0]->value << std::endl;
        } else {
            insertItem(root->children[0]->value, type);
            //记录当前域内已定义变量的名字
            record.push_back(root->children[0]->value);
            return root->children[0]->lineNo;
        }
    } else {    //数组定义
        int elemSize = atoi(root->children[2]->value.c_str());
        Type innerType= newArray(type, elemSize);
        //递归直至遇到变量名
        return VarDec(innerType, root->children[0], record);
    }
}

void FunDec(Type rv_type, tree root, std::list<std::string>& record) {

    std::string func_name = root->children[0]->value;
    std::vector<Type> paramList;
    if (root->children[2]->key == "VarList") {
        VarList(paramList,root->children[2], record);
    }
    Type type = newFunc(rv_type, paramList);
    if (!insertFuncItem(func_name, type)) {
        std::cout << "[line " << root->children[0]->lineNo <<" semantic error] "
                  << "Multiple definition of function " << func_name << std::endl;
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
    VarDec(type, root->children[1], record);   //参数列表中的参数会出现在符号表中
    paramList.push_back(type);

}

/**
 * record:主要用于处理因定义函数而产生的域，因为参数列表里的参数在扫描时已经加入符号表
*/

void CompSt(tree root, std::list<std::string>& record) {
    DefList(root->children[1], record);
    StmtList(root->children[2]);
    //出花括号时，将域内定义过的变量进行删除item操作
    while (!record.empty()) {
        deleteItem(record.back());
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
        Stmt(root->children[4]);
        if (root->children[5]) {    //IF LP Exp RP Stmt ELSE Stmt
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
    DecList(type, root->children[1], record);
}

void DecList(Type type, tree root, std::list<std::string>& record) {
    Dec(type, root->children[0], record);
    if (root->children[2]){
        DecList(type, root->children[0], record);
    }
}

void Dec(Type type, tree root, std::list<std::string>& record) {
    
    int line = VarDec(type, root->children[0], record);
    if (root->children[2]) {    //存在ASSIGNOP, VarDec其后必为左值，因此此处的ASSIGNOP无需判断是否为左值
        Type right = Exp(root->children[2]).first;
        if (!isEquivalent(type, right)) {
            std::cout << "[line " << line <<" semantic error] "
                      << "This kind of value can't be assigned to " << record.back() << std::endl;
        }
    }
}

std::pair<Type, bool> Exp(tree root) {
    if (root->childCnt == 1) { //Exp->ID INT FLOAT
        if (root->children[0]->key == "ID") {
            Type type = getItem(root->children[0]->value);
            if (type == nullptr) {
                std::cout << "[line " << root->children[0]->lineNo <<" semantic error] "
                          << "Undefined reference to variable " << root->children[0]->key << std::endl;
                return {nullptr, false};
            } 
            return {type, true};
        } else if (root->children[0]->key == "INT") {
            return {newBasic(INT_SEMA), false};
        } else {
            return {newBasic(FLOAT_SEMA), false};
        }
    } else if (root->childCnt == 3) {   //
        if (root->children[0]->key == "Exp") {
            if (root->children[1]->key == "ASSIGNOP") { //Exp ASSIGNOP Exp
                std::pair<Type, bool> exp1 = Exp(root->children[0]);
                std::pair<Type, bool> exp2 = Exp(root->children[2]);
                //TODO:判断是否为左值
                if (!exp1.second) {
                    std::cout << "[line " << root->children[1]->lineNo <<" semantic error] "
                              << "Can't assign value to a non-left value. " << std::endl;
                }
                if (!isEquivalent(exp1.first, exp2.first)) {
                    std::cout << "[line " << root->children[1]->lineNo <<" semantic error] "
                              << "Type doesn't match" << std::endl;
                }
                return {exp2.first, false};

            } else if (root->children[1]->key == "DOT") {   //Exp DOT ID
                std::pair<Type, bool> typeExp = Exp(root->children[0]);
                if (typeExp.first && typeExp.first->kind != STRUCTURE_SEMA) {
                    std::cout << "[line " << root->children[1]->lineNo <<" semantic error] "
                              << "Can't access use ." << std::endl;
                    return {nullptr, false};
                }
                std::string id = root->children[2]->value;
                Type typeID = getFieldType(typeExp.first->u.structure, id);
                if (typeID == nullptr) {
                    std::cout << "[line " << root->children[1]->lineNo <<" semantic error] "
                              << "The structure doesn't has the member" << std::endl;
                    return {nullptr, false};
                }
                return {typeID, true};

            } else {    //Exp MUL Exp | Exp ADD Exp ......
                std::pair<Type, bool> exp1 = Exp(root->children[0]);
                std::pair<Type, bool> exp2 = Exp(root->children[2]);
                if (!isEquivalent(exp1.first, exp2.first)) {
                    std::cout << "[line " << root->children[1]->lineNo <<" semantic error] "
                              << "Type doesn't match" << std::endl;
                }
                return {nullptr, false};
            }
            
        } else if (root->children[0]->key == "LP"){    //LP Exp RP
            return Exp(root->children[1]);
        } else {    //ID LP RP
            std::string id = root->children[0]->value;
            Type type = getFuncItem(id);
            if (type == nullptr) {
                std::cout << "[line " << root->children[0]->lineNo <<" semantic error] "
                              << "Undefined reference to function " << id << std::endl;
                return {nullptr,false};
            }
            if (type->u.func.paraNum != 0) {
                std::cout << "[line " << root->children[0]->lineNo <<" semantic error] "
                              << "There are too many params" << std::endl;
                
            }
            return {type->u.func.rv, false};
        }
    } else if (root->childCnt == 2) {   //MINUS Exp /  NOT Exp
        std::pair<Type, bool> exp = Exp(root->children[1]);
        if (exp.first) {
            switch(exp.first->kind){
                case INT_SEMA:FLOAT_SEMA:{
                    if (root->children[0]->key == "MINUS") {
                        return {exp.first, false};
                    } else {
                        return {newBasic(INT_SEMA), false};
                    }
                    break;
                }
                case ARRAY_SEMA:{
                    Type elemType = getArrayElemType(exp.first);
                    if (root->children[0]->key == "MINUS") {
                        if (elemType->kind != STRUCTURE_SEMA) {
                            return {elemType,false};
                        }
                    } else {
                        if (elemType->kind != STRUCTURE_SEMA) {
                            return {newBasic(INT_SEMA), false};
                        }
                    }
                    break;
                }
                case FUNC_SEMA:{
                    Type rv_type = exp.first->u.func.rv;
                    if (root->children[0]->key == "MINUS") {
                        if (rv_type->kind != STRUCTURE_SEMA) {
                            return {rv_type, false};
                        }
                    } else {
                        if (rv_type->kind != STRUCTURE_SEMA) {
                            return {newBasic(INT_SEMA), false};
                        }
                    }
                    break;

                }
                case STRUCTURE_SEMA:{
                    break;
                }
            }
        }
        std::cout << "[line " << root->children[0]->lineNo <<" semantic error] "
                              << "Illegal usage of ! and -" << std::endl;
        return {nullptr, false};
    } else if (root->childCnt == 4) {
        if (root->children[0]->key == "ID") {   // ID LP Args RP
            std::string func_name = root->children[0]->value;
            Type func_type = getFuncItem(func_name);
            if (func_type == nullptr) {
                std::cout << "[line " << root->children[0]->lineNo <<" semantic error] "
                              << "Undefined reference to function " << func_name << std::endl;
                return {nullptr, false};
            }
            if (Args(root->children[2], func_type, 0)) {
                return {func_type->u.func.rv, false};
            }
            std::cout << "[line " << root->children[0]->lineNo <<" semantic error] "
                              << "The paramlist doesn't match" << std::endl;
            return {nullptr, false};
        } else {    //Exp LB Exp RB
            std::pair<Type, bool> exp1 = Exp(root->children[0]);
            std::pair<Type, bool> exp2 = Exp(root->children[2]);
            //TODO:
            if (exp1.first->kind != ARRAY_SEMA) {
                std::cout <<"in line" << root->children[0]->lineNo << " Can't access using index except array" << std::endl;
                return {nullptr, false};
            }

            if (exp2.first->kind != INT_SEMA) {
                std::cout <<"in line" << root->children[0]->lineNo << " The index of array only can be an integer" << std::endl;
                return {nullptr, false};
            }
            return {getArrayElemType(exp1.first), true};
        }
    } 
}

bool Args(tree root, Type func_type, int paramNo){

    if (paramNo == func_type->u.func.paraNum) return true;
    std::pair<Type, bool> exp = Exp(root->children[0]);
    if (!isEquivalent(exp.first, func_type->u.func.paramList[paramNo])) {
        return false;
    }
    if (root->children[2]) {
        return Args(root->children[2], func_type, paramNo + 1);
    }
    return false;

}



