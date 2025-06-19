#pragma once

#include<string>
#include<variant>
#include<stdexcept>
#include<vector>
#include<utility>

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

using ValueVariant = std::variant<bool,char,short,int,long long,float,double,Data*>;

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
    Data* value;
public:
    dataType getType() const override {
        return dataType::pointer;
    }
    
    ValueVariant getValue() const override {
        return value;
    }
    
    void setValue(ValueVariant value) override {
        if (std::holds_alternative<Data*>(value)) {
            this->value = std::get<Data*>(value);
        } else {
            throw std::invalid_argument("ValueVariant is not pointer type");
        }
    }
};

Data* createData(dataType type,ValueVariant v){
    Data* ret;
    switch (type)
    {
    case dataType::i1:
        ret=new Data_i1();
        ret->setValue(v);
        return ret;
    case dataType::i8:
        ret=new Data_i8();
        ret->setValue(v);
        return ret;
    case dataType::i16:
        ret=new Data_i16();
        ret->setValue(v);
        return ret;
    case dataType::i32:
        ret=new Data_i32();
        ret->setValue(v);
        return ret;
    case dataType::i64:
        ret=new Data_i64();
        ret->setValue(v);
        return ret;
    case dataType::f32:
        ret=new Data_f32();
        ret->setValue(v);
        return ret;
    case dataType::f64:
        ret=new Data_f64();
        ret->setValue(v);
        return ret;
    default:
        throw std::invalid_argument("invalid type in creating a new data");
    }
}
