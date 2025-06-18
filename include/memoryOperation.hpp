#include"llvm.hpp"
#include"sym.hpp"

class MemoryOperationLLVM:public LLVM{};

class AllocaLLVM:public MemoryOperationLLVM{
    public:
        Symbol* variable;
        int elementNum; 


        AllocaLLVM(Symbol* variable) : variable(variable) {
            this->llvmType = LLVMtype::alloca;
            this->ty = variable->data->getType();
        }
};