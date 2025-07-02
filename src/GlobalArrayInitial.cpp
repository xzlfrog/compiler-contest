#pragma once

#include<iostream>
#include"../include/GlobalArrayInitial.hpp"

void ArrayInitial::initialize(std::vector<int>position,Data* data){
    initializedData.push_back({position,createData(data)});
}

const std::vector<std::pair<std::vector<int>,Data*>>& ArrayInitial::getInitializedData(){
    return this->initializedData;
}