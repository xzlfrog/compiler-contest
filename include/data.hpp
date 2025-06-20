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

enum initializer{
    zeroinitializer,
    undef
};

class Data {
private:
    dataType type;
    bool isInitialized;
    initializer initMode;
    
public:
    virtual dataType getType() const;
    virtual ValueVariant getValue() const;
    virtual void setValue(ValueVariant value);
    void setIsInitialize(bool flag);
    bool getIsInitialized();
    void setInitMode(initializer initMode);
    initializer getInitMode();
};

using ValueVariant = std::variant<bool,char,short,int,long long,float,double,Data*>;

class Data_i1:public Data {
private:
    bool value;
public:
    dataType getType() const override;
    ValueVariant getValue() const override;
    void setValue(ValueVariant value) override;
};

class Data_i8:public Data {
private:
    char value;
public:    
    dataType getType() const override;
    ValueVariant getValue() const override;
    void setValue(ValueVariant value) override;
};

class Data_i16:public Data {
private:
    short value;
public:    
    dataType getType() const override;
    ValueVariant getValue() const override;
    void setValue(ValueVariant value) override;
};

class Data_i32:public Data {
private:
    int value;
public:    
    dataType getType() const override;
    ValueVariant getValue() const override;
    void setValue(ValueVariant value) override;
};

class Data_i64:public Data {
private:
    long long value;
public:    
    dataType getType() const override;
    ValueVariant getValue() const override;
    void setValue(ValueVariant value) override;
};

class Data_f32:public Data {
private:
    float value;
public:    
    dataType getType() const override;
    ValueVariant getValue() const override;
    void setValue(ValueVariant value) override;
};

class Data_f64:public Data {
private:
    double value;
public:    
    dataType getType() const override;
    ValueVariant getValue() const override;
    void setValue(ValueVariant value) override;
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

Data* createData(dataType type,ValueVariant v);
Data* createData(dataType type);
