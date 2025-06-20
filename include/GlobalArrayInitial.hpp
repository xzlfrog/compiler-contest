#pragma once

#include"data.hpp"
#include<stack>
#include<queue>

class GlobalArrayInitialTreeNode{
public:
    GlobalArrayInitialTreeNode* child=nullptr;
    GlobalArrayInitialTreeNode* brother=nullptr;
    GlobalArrayInitialTreeNode* lastBrother=nullptr;
    Data* data=nullptr;
    std::vector<int>pos={0};//表示是数组中的位置,比如a[8][9][10]，如果是a[2][3]，那么返回0,2,3,如果是根节点则只返回0

    GlobalArrayInitialTreeNode* Addchildren()
    {
        if(this->child==nullptr){
            this->child=new GlobalArrayInitialTreeNode();
            return this->child;
        }
        else if(this->child->brother==nullptr){
            this->child->brother=new GlobalArrayInitialTreeNode();
            this->child->lastBrother=this->child->brother;
            return this->child->lastBrother;
        }
        else{
            this->child->lastBrother->brother=new GlobalArrayInitialTreeNode();
            this->child->lastBrother=this->child->lastBrother->brother;
            return this->child->lastBrother;
        }
    }

    GlobalArrayInitialTreeNode* findNthChild(int n){
        if(n<0)
            throw std::invalid_argument("the index exceeds the size of the array");
        else if(n==0)
            return this->child;
        else{
            n-=1;
            GlobalArrayInitialTreeNode* node=this->child;
            for(int i=0;i<=n;i++){
                if(node->brother!=nullptr)
                    node=node->brother;
                else
                    throw std::invalid_argument("the index exceeds the size of the array");
                return node;
            }
        return nullptr;
        }
    }
};

class GlobalArrayInitialTree{
private:
    GlobalArrayInitialTreeNode* root;

public:
    GlobalArrayInitialTree(std::vector<int>&dims){
        std::queue<GlobalArrayInitialTreeNode*>q_node;
        GlobalArrayInitialTreeNode* node;
        q_node.push(root);
        int sz=1;
        for(auto dim : dims){
            for(int i=0;i<sz;i++){
                node=q_node.front();
                q_node.pop();
                for(int j=0;j<dim;j++){
                    q_node.push(node->Addchildren());
                }
            }
            sz=sz*dim;
        }
    }
    
};
