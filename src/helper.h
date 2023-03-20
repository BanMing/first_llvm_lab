#ifndef _HELPER_H_
#define _HELPER_H_
#include <iostream>
#include "exprast.h"

std::unique_ptr<ExprAST> LogError(const char *str)
{
    fprintf(stderr, "Error: %s\n", str);
    return nullptr;
}

std::unique_ptr<PrototypeAST> LogErrorP(const char *str)
{
    LogError(str);
    return nullptr;
}

#endif //_HELPER_H_
