#pragma once

#include <vector>
#include "frontendTool.hpp"
#include "../include/SymbolFactory.hpp"
#include "../include/LLVMFactory.hpp"
#include "../include/data.hpp"

std::vector<BasicSymbol*> params_table;
dataType stringToDatatyoe(std::string returnDataTypeString);

FuncDefination* create_func_def(std::string returnDataTypeString, std::string name, std::vector<Symbol*> params, LLVM* blocks);

std::vector<BasicSymbol*> addToParams(BasicSymbol* param);
VarSymbol* create_param_nonarray(std::string paraType, std::sting name);
ArraySymbol* create_param_array(std::string paraType, std::string name, std::vector<int> dimensions);