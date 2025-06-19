#pragma once

#include"sym.hpp"

class SymbolFactory{
    BasicSymbol* createBasicSymbol();

    PointerSymbol* createPointerSymbol();

    ArraySymbol* createArraySymbol();

    LabelSymbol* createLabelSymbol();

    FuncSymbol* createFuncSymbol();
};
