#pragma once

#include"data.hpp"

#define GLOBAL_SCOPE 0
#define FUNCTION_SCOPE 1
#define BLOCK_SCOPE 2

enum symType{
    sym_undefined,
    function,
    label,
    variable,
    const_i1,
    constant_i8,
    constant_i16,
    constant_i32,
    constant_i64,
    constant_f32,
    constant_f64,
    array,
    pointer
};

class Symbol {
public:
    symType type;
    std::string name;
    Data* data;
    int offset;
    int scope;
    Symbol* next;
    bool isArray;//是否是数组

    virtual symType getType() const;
    
    Symbol(const std::string& name)
        : name(name), type(symType::sym_undefined) , data(nullptr), offset(0), scope(0), next(nullptr) {}

    Symbol(const std::string& name,symType type)
        : name(name), type(type) , data(nullptr), offset(0), scope(0), next(nullptr) {}

};

//只考虑了指针的情况，未考虑指针的指针的情况，如需使用需后续补充
class PointerSymbol:public Symbol{
private:
    dataType PointedType;//当前指针指向的元素类型

public:
    Data* & pointedData;//指向的数据

    using Symbol::Symbol;

    symType getType() const override{return symType::pointer;}

    dataType getPointedType() const {
        return this->PointedType;
    }

    void allocateMemory(dataType elementType,ValueVariant value=nullptr){
        this->PointedType = elementType;

        Data_pointer* data_pointer = new Data_pointer();
        Data* data=createData(elementType,value);
        this->data=new Data_pointer();
        this->data->setValue(data);

        this->pointedData=std::get<Data*>(this->data->getValue());
    }

};

//包含常数符号和放在寄存器里的符号
class BasicSymbol: public Symbol{
public:
    using Symbol::Symbol;

    symType getType() const override{return this->type;}

    dataType getDataType(){return this->data->getType();}

    void setData(dataType dtype,ValueVariant v=nullptr){this->data=createData(dtype,v);}

    void setType(symType type) {
        if(type<symType::variable||type>symType::constant_f64)
            throw std::invalid_argument("basic symbol type is wrong");
        this->type=type;
    }
};

//数组变量的符号,似乎存数组中的数据没有什么意义？除非在做优化的时候可以用到？
class ArraySymbol: public Symbol{
private:
    std::vector<int> dimensions; //数组的维度信息 
    dataType arrayType;
    std::vector<int> elementNums;//比如数组a[5][6][7],则该向量中包含5*6*7,6*7,7,1表示每一个维度的"1"有几个元素

    template<typename... Args>
        void addDimensions(Args... dims){ 
        (this->dimensions.push_back(static_cast<size_t>(dims)), ...);
    }

public:
    using Symbol::Symbol;

    symType getType() const override{return symType::array;}

    //如array.allocateMemory(dataType::i32,5,6,7)表示分配了一个i32 a[5][6][7]的数组
    template<typename... Args>
    void allocateMemory(dataType type,Args... dims){
        this->arrayType=type;
        this->addDimensions(dims...);
        int size=1;

        for(auto dim:this->dimensions)
            size=dim*size;
        
        this->elementNums.push_back(size);
        for(auto dim:this->dimensions)
            size=size/dim,this->elementNums.push_back(size);
    }

    std::vector<int>getDimensions(){return this->dimensions;}

    dataType getArrayType(){return this->arrayType;}
};


//标签对应的符号
class LabelSymbol:public Symbol{
public:
    using Symbol::Symbol;

    symType getType() const override{return symType::label;}
};

class FuncSymbol:public Symbol{
public:
    std::vector<dataType> argumentsType;

    using Symbol::Symbol;
    symType getType() const override{return symType::function;}
    void addArguments(std::vector<dataType> arguments);
    void addArgument(dataType argument);
    const std::vector<dataType> getArgumentsType()const{return this->argumentsType;}
};
