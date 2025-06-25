#pragma once

#include"../include/GlobalArrayInitial.hpp"

void ArrayInitial::initialize(std::vector<int>position,Data* data){
    initializedData[position]=createData(data);
}

std::vector<std::pair<std::vector<int>,Data*>> ArrayInitial::getInitializedData(){
    std::vector<int> idx;
    Data* data;
    std::vector<std::pair<std::vector<int>,Data*>> res;
    for(const auto & idxAndData:this->initializedData){
        idx=idxAndData.first;
        data=idxAndData.second;
        res.push_back({idx,data});
    }
    return res;
}