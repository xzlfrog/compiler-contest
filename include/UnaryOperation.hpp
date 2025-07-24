#include"llvm.hpp"
#include"sym.hpp"

class UnaryOperationLLVM : public LLVM{
public:
    BasicSymbol* dest_sym;
    BasicSymbol* src_sym;

    dataType getType();
    std::string out_str() const override;
    void out_arm_str() override;
    ~UnaryOperationLLVM()=default;
};