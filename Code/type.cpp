#include "type.hpp"
#include "global.hpp"
#include <iostream>
#include <unordered_map>
#include <vector>
/**
 * @brief 新建INT/FLOAT类型
 * 
 * @param kind:标明是INT还是FLOAT
 * @return Type 指向该INT/FLOAT类型的指针
 */
Type newBasic(Kind kind) {
    Type type = new Type_();
    type->kind = kind;
    return type;
}
/**
 * @brief 新建一个数组类型
 * 
 * @param elemType 数组中元素的类型
 * @param elemSize 数组元素个数
 * @return Type 指向该数组类型的指针
 */
Type newArray(Type elemType, int elemSize){
    Type type = new Type_();
    type->kind = ARRAY;
    type->u.array.elemType = elemType;
    type->u.array.elemSize = elemSize;
    return type;
}
/**
 * @brief 新建一个结构体类型
 * 
 * @param members 一个域名和域类型的对应表
 * @return Type 指向该结构体类型的指针
 */
Type newStructure(std::unordered_map<std::string, Type> members){
    Type type = new Type_();
    type->kind = STRUCTURE;
    
    FieldList dummyNode = new FieldList_();
    dummyNode->tail = nullptr;
    FieldList cur = dummyNode;
    for (auto member : members) {
        cur->tail = newFieldList(member.first, member.second);
        cur = cur->tail;
    }
    type->u.structure = dummyNode->tail;
    return type;
}

Type newFunc(Type rv, std::vector<Type>& paramTypes){
    Type type = new Type_();
    type->kind = FUNC;
    type->u.func.rv = rv;
    type->u.func.paraNum = paramTypes.size();
    type->u.func.paramList = new Type[paramTypes.size()];
    for(int i = 0; i < paramTypes.size(); ++i) {
        type->u.func.paramList[i] = paramTypes[i];
    }
    return type;
}

Type copyType(Type src){
    Type type = new Type_();
    type->kind = src->kind;
    switch(src->kind) {
        case INT:case FLOAT:break;
        case ARRAY:{
            type->u.array.elemType = copyType(src->u.array.elemType);
            type->u.array.elemSize = src->u.array.elemSize;
            break;
        }
        case FUNC:{
            type->u.func.rv = copyType(src->u.func.rv);
            type->u.func.paraNum = src->u.func.paraNum;
            type->u.func.paramList = new Type[type->u.func.paraNum];
            for (int i = 0; i < type->u.func.paraNum; ++i) {
                type->u.func.paramList[i] = copyType(src->u.func.paramList[i]);
            }
            break;
        }
        case STRUCTURE:{
            type->u.structure = copyFieldList(src->u.structure);
            break;
        }
    }
    return type;
}

FieldList newFieldList(std::string name, Type type){
    FieldList fieldList = new FieldList_();
    fieldList->name = name;
    fieldList->type = type;
    fieldList->tail = nullptr;
    return fieldList;
}

void deleteFieldList(FieldList fieldList){
    FieldList cur = fieldList;
    while (cur) {
        FieldList next = cur->tail;
        delete cur;
        cur = next;
    }
}

FieldList copyFieldList(FieldList fieldList){

    if (fieldList == nullptr) return nullptr;
    FieldList newList = new FieldList_();
    newList->name = fieldList->name;
    newList->type = fieldList->type;
    newList->tail = copyFieldList(fieldList->tail);
}

Type getType(std::string key) {
    auto target = symTable.find(key);
    if (target == symTable.end()) {
        return nullptr;
    } else {
        if (target->second.size() == 0) {
            return nullptr;
        } else {
            return target->second.top();
        }
    }
}

bool insertType(std::string key, Type type) {
    auto target = symTable.find(key);
    if (target == symTable.end()) {
        std::stack<Type> tmp;
        tmp.push(type);
        symTable.insert({key, tmp}); 
    } else {
        if (target->second.top()->kind == FUNC) {
            return false;
        } else {
            target->second.push(type);
        }
    }

    return true;
}

void deleteType(std::string key) {
    auto target = symTable.find(key);
    if (target == symTable.end()) {
        std::cout << "Error in deleteType" << std::endl;
    } else {
        if (target->second.size() == 0) {
            std::cout << "Error in deleteType" << std::endl;
        } else {
            target->second.pop();
        }
    }
}

bool isEquivalent(Type type1, Type type2) {
    if (type1->kind == type2->kind) {
        switch(type1->kind) {
            case INT:case FLOAT:return true;
            case ARRAY:{
                if (type1->u.array.elemSize != type2->u.array.elemSize) {
                    return false;
                }
                return isEquivalent(type1->u.array.elemType, type2->u.array.elemType);
            }
            case FUNC:{
                if (type1->u.func.rv != type2->u.func.rv || type1->u.func.paraNum != type2->u.func.paraNum) {
                    return false;
                }
                for (int i = 0; i < type1->u.func.paraNum; ++i) {
                    if (!isEquivalent(type1->u.func.paramList[i], type2->u.func.paramList[i])){
                        return false;
                    }
                }
                return true;
            }
            case STRUCTURE:{
                FieldList f1 = type1->u.structure;
                FieldList f2 = type2->u.structure;
                while(f1 && f2) {
                    if (!isEquivalent(f1->type, f2->type)) {
                        return false;
                    }
                    f1 = f1->tail;
                    f2 = f2->tail;
                }
                if (f1 || f2) {
                    return false;
                }
                return true;
            }
        }
    } else {
        return false;
    }
}