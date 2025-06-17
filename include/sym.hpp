#include<string>
#include<variant>
#include<stdexcept>
#include<vector>

using ValueVariant = std::variant<bool,char,short,int,long long,float,double>;

enum symType{
    undefined,
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
};

enum dataType{
    undefined,
    i1,
    i8,
    i16,
    i32,
    i64,
    f32,
    f64
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


class Symbol {
private:
    unsigned pointerLevel;//当前的符号是几级指针
    int memorySize;//当前符号的内存大小，单位为字节
    int elementNum;//当前符号的元素个数，如果是数组类型，则为数组的长度，否则为1
    symType elementType;//指针最终指向的类型，比如i32******指向的为i32
    std::vector<int> dimensions;//如果是数组类型，则为数组的维度，按从外到内的顺序存储  

public:
    std::string name;
    symType type;
    Data* data;
    int offset;
    int scope;
    Symbol* next;

    Symbol(const std::string& name,symType type)
        : name(name), type(type), data(nullptr), offset(0), scope(0), next(nullptr) {}
    
    Symbol(const std::string& name)
        : name(name), type(symType::undefined) , data(nullptr), offset(0), scope(0), next(nullptr) {}

    Symbol(const std::string& name,Data*data)
        : name(name), type(symType::undefined) , data(data), offset(0), scope(0), next(nullptr) {}

    //这几个成员函数写yacc时不用考虑
    //分配内存空间，在写yacc文件时不用管这个函数，考虑到底分配内存空间还是分配寄存器空间交给后面的工作
    template<typename T,typename ...Args>
    void allocateMemory(int memorySize,symType elementType,unsigned pointerLevel,Args ...dimensions);

    //同上,只是这个是分配寄存器空间
    void allocateRegister();

    //从内存中加在数据到寄存器中
    Symbol* loadFromMemory();
};