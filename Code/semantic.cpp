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
        if (root->children[0]->value == "INT_SEMA") {
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
            std::cout << "Undefined reference to " << tag << "in line" << std::to_string(root->children[1]->lineNo) << "\n";
            exit(1);
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

void VarDec(Type type, tree root, std::list<std::string>& record) {

    if (root->children[0]->key == "ID") {
        //检查当前域内是否已经对该变量有过定义
        auto iter = std::find(record.begin(), record.end(), root->children[0]->value);
        if (iter != record.end()) {
            std::cout << "Multiple definition of variable" << root->children[0]->value << "in line" << root->children[0]->lineNo << std::endl;
        } else {
            insertItem(root->children[0]->value, type);
            //记录当前域内已定义变量的名字
            record.push_back(root->children[0]->value);
        }
    } else {    //数组定义
        int elemSize = atoi(root->children[2]->value.c_str());
        Type innerType= newArray(type, elemSize);
        //递归直至遇到变量名
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
    if (!insertFuncItem(func_name, type)) {
        std::cout << "Multiple definition of function" << func_name << "() in line" << root->children[0]->lineNo << std::endl;
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
    //从record中取避免传数组出错，但似乎并无必要(不支持参数中传数组)
    //paramList.push_back(getType(record.back()));
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
    
    VarDec(type, root->children[0], record);
    if (root->children[2]) {    //存在ASSIGNOP
        Type right = Exp(root->children[2]);
        if (!isEquivalent(type, right)) {
            std::cout <<"line:" << root->children[0]->lineNo << " The variable can't be assigned with this kind of value" << std::endl;
        }
    }
}

Type Exp(tree root) {
    if (root->childCnt == 1) { //Exp->ID INT FLOAT
        if (root->children[0]->key == "ID") {
            Type type = getItem(root->children[0]->value);
            if (type == nullptr) {
                std::cout << "in line:" << root->children[0]->lineNo << " Undefined reference to " << root->children[0]->value << std::endl;
            }
            return type;
        } else if (root->children[0]->key == "INT") {
            return newBasic(INT_SEMA);
        } else {
            return newBasic(FLOAT_SEMA);
        }
    } else if (root->childCnt == 3) {   //
        if (root->children[0]->key == "Exp") {
            if (root->children[1]->key == "ASSIGNOP") { //Exp ASSIGNOP Exp
                Type type1 = Exp(root->children[0]);
                Type type2 = Exp(root->children[2]);

                if (!isLeftValue(type1)) {
                    std::cout << "in line:" << root->children[1]->lineNo << " Can't assign to a non-left value" << std::endl;
                }
                if (!isEquivalent(type1, type2)) {
                    std::cout << "in line:" << root->children[1]->lineNo << "The type doesn't match" << std::endl;
                }
                return type2;

            } else if (root->children[1]->key == "DOT") {   //Exp DOT ID
                Type typeExp = Exp(root->children[0]);
                if (typeExp && typeExp->kind != STRUCTURE_SEMA) {
                    std::cout << "in line:"<< root->children[0]->lineNo <<  "Error, can't access the value using ." << std::endl;
                    return nullptr;
                }
                std::string id = root->children[2]->value;
                Type typeID = getFieldType(typeExp->u.structure, id);
                if (typeID == nullptr) {
                    std::cout << "in line" << root->children[2]->lineNo << "Has no such member." << std::endl;
                }
                return typeID;

            } else {    //Exp MUL Exp | Exp ADD Exp ......
                Type type1 = Exp(root->children[0]);
                Type type2 = Exp(root->children[2]);
                if (!isEquivalent(type1, type2)) {
                    std::cout << "in line " << root->children[0]->lineNo <<  " The type of two operands doesn't match" << std::endl;
                }
                return type1;
            }
            
        } else if (root->children[0]->key == "LP"){    //LP Exp RP
            return Exp(root->children[1]);
        } else {    //ID LP RP
            std::string id = root->children[0]->value;
            Type type = getFuncItem(id);
            if (type == nullptr) {
                std::cout <<"in line" << root->children[0]->lineNo << " Undefined reference to function " << id << std::endl;
                return nullptr;
            }
            if (type->u.func.paraNum != 0) {
                std::cout <<"in line" << root->children[0]->lineNo<< "Too much params for function" << id << std::endl;
            }
            return type->u.func.rv;
        }
    } else if (root->childCnt == 2) {   //MINUS Exp /  NOT Exp
        Type type = Exp(root->children[1]);
        if (type) {
            switch(type->kind){
                case INT_SEMA:FLOAT:{
                    if (root->children[0]->key == "MINUS") {
                        return type;
                    } else {
                        return newBasic(INT_SEMA);
                    }
                    break;
                }
                case ARRAY_SEMA:{
                    Type elemType = getArrayElemType(type);
                    if (root->children[0]->key == "MINUS") {
                        if (elemType->kind != FUNC_SEMA || elemType->kind != STRUCTURE_SEMA) {
                            return elemType;
                        }
                    } else {
                        if (elemType->kind != FUNC_SEMA || elemType->kind != STRUCTURE_SEMA) {
                            return newBasic(INT_SEMA);
                        }
                    }
                    break;
                }
                case FUNC_SEMA:{
                    Type rv_type = type->u.func.rv;
                    if (root->children[0]->key == "MINUS") {
                        if (rv_type->kind != STRUCTURE_SEMA) {
                            return type;
                        }
                    } else {
                        if (rv_type->kind != STRUCTURE_SEMA) {
                            return newBasic(INT_SEMA);
                        }
                    }
                    break;

                }
                case STRUCTURE_SEMA:{
                    break;
                }
            }
        }
        std::cout << "in line" << root->children[0]->lineNo << "The operation is illegal" << std::endl;
        return nullptr;
    } else if (root->childCnt == 4) {
        if (root->children[0]->key == "ID") {   // ID LP Args RP
            std::string func_name = root->children[0]->value;
            Type func_type = getFuncItem(func_name);
            if (func_type == nullptr) {
                std::cout << "in line" << root->children[0]->lineNo << " Undefined reference to the function " << func_name << std::endl;
                return nullptr;
            }
            if (Args(root->children[2], func_type, 0)) {
                return func_type->u.func.rv;
            }
            std::cout <<"in line "<< root->children[2]->lineNo << " The paramList is unmatched." << std::endl;
            return nullptr;
        } else {    //Exp LB Exp RB
            Type type1 = Exp(root->children[0]);
            Type type2 = Exp(root->children[2]);
            //TODO:
            if (type1->kind != ARRAY_SEMA) {
                std::cout <<"in line" << root->children[0]->lineNo << " Can't access using index except array" << std::endl;
                return nullptr;
            }

            if (type2->kind != INT_SEMA) {
                std::cout <<"in line" << root->children[0]->lineNo << " The index of array only can be an integer" << std::endl;
                return nullptr;
            }
            return getArrayElemType(type1);
        }
    } 
}

bool Args(tree root, Type func_type, int paramNo){

    if (paramNo == func_type->u.func.paraNum) return true;
    Type type1 = Exp(root->children[0]);
    if (!isEquivalent(type1, func_type->u.func.paramList[paramNo])) {
        return false;
    }
    if (root->children[2]) {
        return Args(root->children[2], func_type, paramNo + 1);
    }
    return false;

}



