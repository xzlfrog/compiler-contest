#pragma once

#include<iostream>
#include"../include/GlobalArrayInitial.hpp"

void ArrayInitial::initialize(std::vector<int>position,Data* data){
    initializedData.push_back({position,createData(data)});
}

const std::vector<std::pair<std::vector<int>,Data*>>& ArrayInitial::getInitializedData(){
    return this->initializedData;
}

void ArrayInitial::initialize(Data* data){
    this->initializedData.push_back({std::vector<int>(0),data});
}

ArrayInitial* dataToArrayInitial(Data* data){
    ArrayInitial* arrayInitial = new ArrayInitial();
    arrayInitial->initialize(data);
    return arrayInitial;
}

Data* arrayInitialToData(ArrayInitial* arrayInitial){
    return arrayInitial->getInitializedData()[0].second;
}

void ArrayInitial::merge(ArrayInitial* x){
    for(auto &a : x->getInitializedData()){
        this->initializedData.push_back(a);
    }
}

void ArrayInitial::reverse(){
    for(auto &a : this->initializedData){
        std::vector<int>v;
        for(int i=a.first.size()-1;i>=0;i--){
            v.push_back(a.first[i]);
        }
        a.first=v;
    }
}