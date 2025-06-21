#pragma once

#include"../include/GlobalArrayInitial.hpp"

long long HierarchicalBitmap::PosToIdx(std::vector<int>position){
    long long idx=1LL;
    long long tmp=1LL;
    for(int i=this->dims.size()-1;i>=position.size();i--){
        tmp=tmp*this->dims[i];
    }
    for(int i=position.size()-1;i>=0;i--){
        idx=idx+tmp*position[i];
    }
    return idx;
}

std::vector<int> HierarchicalBitmap::IdxToPos(long long idx){
    std::vector<int>pos;
    for(int i=1;i<this->dims.size()-1;i++){
        pos.push_back(idx/this->dims[i]);
        idx=idx%this->dims[i];
        i++;
    }
    return pos;
}

HierarchicalBitmap::HierarchicalBitmap(std::vector<int>&dims){
    this->dims=dims;
    int sz=1;
    for(int i=0;i<dims.size();i++){
        bitMap.push_back(std::vector<bool>(sz,false));
        sz=sz*dims[i];
    }
    bitMap.push_back(std::vector<bool>(sz,false));
}

void HierarchicalBitmap::Initialize(std::vector<int>position,Data* data){
    long long idx=this->PosToIdx(position);
    initializedData[idx]=data;
    bitMap[position.size()][idx]=true;
}

std::vector<std::pair<std::vector<int>,Data*>> HierarchicalBitmap::getInitializedData(){
    long long idx;
    Data* data;
    std::vector<std::pair<std::vector<int>,Data*>> res;
    for(const auto & idxAndData:this->initializedData){
        idx=idxAndData.first;
        data=idxAndData.second;
        res.push_back({IdxToPos(idx),data});
    }
    return res;
}