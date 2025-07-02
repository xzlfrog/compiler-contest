#pragma once

//#include"sym.hpp"
#include<queue>
#include<unordered_map>
#include"data.hpp"

struct VectorIntHash{
private:
    const long long mod=131L;

public:
    std::size_t operator()(const std::vector<int>&v) const{
        size_t seed=v.size();
        for(auto i:v){
            seed ^= std::hash<int>{}(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

class ArrayInitial{
private:
    std::vector<std::pair<std::vector<int>,Data*>> initializedData;

public:
    void initialize(std::vector<int>position,Data* data);//将某一个初始化为非0的值的位置和值
    //传入该函数
    const std::vector<std::pair<std::vector<int>,Data*>>& getInitializedData();//得到被初始化的
    //那些值
};


/*若有对第"0"维初始化(给所有数组中所有元素初始化为0)直接结束初始化部分
接下来开始遍历第一维的每一个元素，比如对a[8][9][10](类型若是i32)进行操作，以下开始举例说明
对于a[0]，包含了9*10=90个元素，如果全部初始化为0，则直接为
[9*[10*i32]] zeroinitializer，进入a[1]的初始化部分
如果不是再进入下一个维度即考虑a[0][0]，同理。
对于此处，用树来存储是否是一个可行的方式？
其实本质就是，还是上面的例子，其实我们可以看作根节点root，表示所有的a的元素，
连下来是8颗子树，每一个分别表示a[0]-a[7]，然后再接着下来
我们其实就是如果根节点被初始化了，那么就不用继续搜索这颗子树了，
否则继续搜索
使用bfs算法即可*/
/*class GlobalArrayInitialTreeNode{
public:
    GlobalArrayInitialTreeNode* child=nullptr;
    GlobalArrayInitialTreeNode* brother=nullptr;
    Data* data=nullptr;
    int idx;
    
    GlobalArrayInitialTreeNode* Addchildren(int idx)
    {
        if(this->child==nullptr){
            this->child=new GlobalArrayInitialTreeNode();
            this->child->pos=this->pos;
            this->child->pos.push_back(idx);
            this->child->idx=idx;
            return this->child;
        }
        else{
            GlobalArrayInitialTreeNode* node=this->child;
            while(node->brother!=nullptr&&node->brother->idx<idx)
                node=node->brother;
            if(node->brother!=nullptr&&node->brother->idx==idx)
                return node->brother;
            GlobalArrayInitialTreeNode* old_brother=node->brother;
            node->brother=new GlobalArrayInitialTreeNode();
            node->brother->pos=node->pos;
            node->brother->pos.push_back(idx);
            node->brother->brother=old_brother;
            return node->brother;
        }
    }

    GlobalArrayInitialTreeNode* findNthChild(int n){
        GlobalArrayInitialTreeNode* node=this->child;
        while(node!=nullptr){
            if(node->idx==n)
                return node;
            node=node->brother;
        }
        throw std::invalid_argument("the element in the array is not initialized");
    }
};

class GlobalArrayInitialTree{
private:
    GlobalArrayInitialTreeNode* root;
    std::vector<int>dims;

public:
    //通过数组维度初始化树，不用传整个数组的那个0
    GlobalArrayInitialTree(std::vector<int>&dims){
        this->root = new GlobalArrayInitialTreeNode();
        this->dims=dims;
    }

    void addInitialedData(std::vector<int>position,Data* data){
        GlobalArrayInitialTreeNode* node=this->root;
        GlobalArrayInitialTreeNode* children;
        for(auto pos:position){
            node=node->Addchildren(pos);
        }
        node->data=data;
    }

    std::vector<std::pair<std::vector<int>,Data*>> bfs(){
        std::vector<std::pair<std::vector<int>,Data*>>initialed_positions;
        std::queue<GlobalArrayInitialTreeNode*>q_node;
        q_node.push(this->root);
        GlobalArrayInitialTreeNode* node=nullptr;
        GlobalArrayInitialTreeNode* child_node=nullptr;
        while(!q_node.empty()){
            node=q_node.front();
            q_node.pop();
            if(node->data&&node->data->getIsInitialized()){
                initialed_positions.push_back({node->pos,node->data});
                continue;
            }
            for(child_node=node->child;child_node!=nullptr;child_node=child_node->brother){
                q_node.push(child_node);
            }
        }
        return initialed_positions;
    }
    
};*/