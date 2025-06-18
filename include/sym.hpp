#pragma once

#include<string>
#include<variant>
#include<stdexcept>
#include<vector>
#include<utility>

using ValueVariant = std::variant<bool,char,short,int,long long,float,double,void*>;

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
    constant_f64
};

enum dataType{
    data_undefined,
    void_,
    i1,
    i8,
    i16,
    i32,
    i64,
    f32,
    f64,
    pointer
};

class Data {
private:
    dataType type;
    
public:
    virtual dataType getType() const =0;
    virtual ValueVariant getValue() const =0;
    virtual void setValue(ValueVariant value) =0;
};

class Data_i1:public Data {
private:
    bool value;
public:
    dataType getType() const override {
        return dataType::i1;
    }
    
    ValueVariant getValue() const override {
        return value;
    }
    
    void setValue(ValueVariant value) override {
        if (std::holds_alternative<bool>(value)) {
            this->value = std::get<bool>(value);
        } else {
            throw std::invalid_argument("ValueVariant is not bool type");
        }
    }
};

class Data_i8:public Data {
private:
    char value;
public:    
    dataType getType() const override {
        return dataType::i8;
    }
    
    ValueVariant getValue() const override {
        return value;
    }
    
    void setValue(ValueVariant value) override {
        if (std::holds_alternative<char>(value)) {
            this->value = std::get<char>(value);
        } else {
            throw std::invalid_argument("ValueVariant is not char type");
        }
    }
};

class Data_i16:public Data {
private:
    short value;
public:    
    dataType getType() const override {
        return dataType::i16;
    }
    
    ValueVariant getValue() const override {
        return value;
    }
    
    void setValue(ValueVariant value) override {
        if (std::holds_alternative<short>(value)) {
            this->value = std::get<short>(value);
        } else {
            throw std::invalid_argument("ValueVariant is not short type");
        }
    }
};

class Data_i32:public Data {
private:
    int value;
public:    
    dataType getType() const override {
        return dataType::i32;
    }
    
    ValueVariant getValue() const override {
        return value;
    }
    
    void setValue(ValueVariant value) override {
        if (std::holds_alternative<int>(value)) {
            this->value = std::get<int>(value);
        } else {
            throw std::invalid_argument("ValueVariant is not int type");
        }
    }
};

class Data_i64:public Data {
private:
    long long value;
public:    
    dataType getType() const override {
        return dataType::i64;
    }
    
    ValueVariant getValue() const override {
        return value;
    }
    
    void setValue(ValueVariant value) override {
        if (std::holds_alternative<long long>(value)) {
            this->value = std::get<long long>(value);
        } else {
            throw std::invalid_argument("ValueVariant is not long long type");
        }
    }
};

class Data_f32:public Data {
private:
    float value;
public:    
    dataType getType() const override {
        return dataType::f32;
    }
    
    ValueVariant getValue() const override {
        return value;
    }
    
    void setValue(ValueVariant value) override {
        if (std::holds_alternative<float>(value)) {
            this->value = std::get<float>(value);
        } else {
            throw std::invalid_argument("ValueVariant is not float type");
        }
    }
};

class Data_f64:public Data {
private:
    double value;
public:    
    dataType getType() const override {
        return dataType::f64;
    }
    
    ValueVariant getValue() const override {
        return value;
    }
    
    void setValue(ValueVariant value) override {
        if (std::holds_alternative<double>(value)) {
            this->value = std::get<double>(value);
        } else {
            throw std::invalid_argument("ValueVariant is not double type");
        }
    }
};

class Data_pointer:public Data {
private:
    void* value;
public:
    dataType getType() const override {
        return dataType::pointer;
    }
    
    ValueVariant getValue() const override {
        return value;
    }
    
    void setValue(ValueVariant value) override {
        if (std::holds_alternative<void*>(value)) {
            this->value = std::get<void*>(value);
        } else {
            throw std::invalid_argument("ValueVariant is not pointer type");
        }
    }
};

class Symbol {
private:
    //只考虑了指针，数组，基本数据类型，此处未考虑指针的指针，函数指针，指针数组的情况，若需要该功能，此处需要修改
    dataType elementType;//当前指针指向的元素类型
    std::vector<int> dimensions; //数组的维度信息 
    Symbol* pointedElement;//指向的符号

public:
    std::string name;
    symType type;
    Data* data;
    int offset;
    int scope;
    Symbol* next;
    bool isArray;//是否是数组

    Symbol(const std::string& name,symType type,Data* data)
        : name(name), type(type), data(data), offset(0), scope(0), next(nullptr) {}
    
    Symbol(const std::string& name)
        : name(name), type(symType::sym_undefined) , data(nullptr), offset(0), scope(0), next(nullptr) {}

    Symbol(const std::string& name,symType type)
        : name(name), type(symType::sym_undefined) , data(nullptr), offset(0), scope(0), next(nullptr) {}

    Symbol(const std::string& name,Data*data)
        : name(name), type(symType::sym_undefined) , data(data), offset(0), scope(0), next(nullptr){}


    //yacc文件中不需要调用以下方法
    //----------------------------------------------------------------
    //在allocaLLVM类中调用，yacc文件中调用allocaLLVM中的方法，不调用这个方法
    template<typename... Args>
    void allocateMemory(dataType elementType,Args... dims){
        this->elementType = elementType;
        Data_pointer* data_pointer = new Data_pointer();
        data_pointer->setValue(nullptr);
        this->data=data_pointer;
        this->addDimensions(dims...);
    }

    template<typename... Args>
        void addDimensions(Args... dims){ 
        (this->dimensions.push_back(static_cast<size_t>(dims)), ...);
    }

    void setPointedElement(Symbol* element){this->pointedElement=element;}

    void addDimensions(){}
    
    void allocateRegister();

    //从内存中加在数据到寄存器中
    Symbol* loadFromMemory();

    dataType getElementType() const {
        return elementType;
    }

    const std::vector<int>& getDimensions() const {
        return dimensions;
    }

};
