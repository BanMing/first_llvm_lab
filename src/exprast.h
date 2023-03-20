#ifndef _EXPRAST_H_
#define _EXPRAST_H_
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// EXprAST - Base class for all expression nodes. Abstract Syntanx Tree(AST)
class ExprAST
{
public:
    virtual ~ExprAST() = default;
};

// NumberExprAST - EXpression class for numeric literals like "1.0"
class NumberExprAST : public ExprAST
{
private:
    double Val;

public:
    NumberExprAST(double val) : Val(val) {}
};

// VariableExprAST - Expression class for referencing a variable like "a".
class VariableExprAST : public ExprAST
{
private:
    std::string Name;

public:
    VariableExprAST(const std::string &name) : Name(name) {}
};

// BinaryExprAST - Expression class for a binary operator.
class BinaryExprAST : public ExprAST
{
private:
    char Op;
    std::unique_ptr<ExprAST> LHS, RHS;

public:
    BinaryExprAST(char op, std::unique_ptr<ExprAST> lhs, std::unique_ptr<ExprAST> rhs) : Op(op), LHS(std::move(lhs)), RHS(std::move(rhs)) {}
};

// CallExprAST - EXpression class for function calls
class CallExprAST : public ExprAST
{
private:
    std::string Callee;
    std::vector<std::unique_ptr<ExprAST>> Args;

public:
    CallExprAST(const std::string &callee, std::vector<std::unique_ptr<ExprAST>> args) : Callee(callee), Args(std::move(args)) {}
};

// PrototypeAST - This class represents the "prototype" for a function,
// which captures its name, and its argument names (thus implicitly the number
// of arguments the function takes).
class PrototypeAST
{
private:
    std::string Name;
    std::vector<std::string> Args;

public:
    PrototypeAST(const std::string &name, std::vector<std::string> args) : Name(name), Args(std::move(args)) {}
    const std::string &getName() const { return Name; }
};

// FunctionAST - This class represents a function definition itself.
class FunctionAST
{
private:
    std::unique_ptr<PrototypeAST> Proto;
    std::unique_ptr<ExprAST> Body;

public:
    FunctionAST(std::unique_ptr<PrototypeAST> proto, std::unique_ptr<ExprAST> body) : Proto(std::move(proto)), Body(std::move(body)) {}
};
#endif //_EXPRAST_H_