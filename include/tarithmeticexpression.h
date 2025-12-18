#ifndef TARITHMETICEXPRESSION_H
#define TARITHMETICEXPRESSION_H

#include <string>
#include <vector>
#include <map>
#include <functional>
#include "tstack.h"

class TArithmeticExpression {
private:
    std::string infix;
    std::string postfix;
    std::vector<char> operands;
    std::map<std::string, int> priority;
    std::map<std::string, std::function<double(double)>> functions;

    void toPostfix();
    bool isOperator(char c) const;
    bool isDigit(char c) const;
    bool isLetter(char c) const;
    bool isFunction(const std::string& token) const;
    int getPriority(const std::string& op) const;

public:
    TArithmeticExpression(const std::string& expr = "");

    std::string getInfix() const { return infix; }
    std::string getPostfix() const { return postfix; }
    std::vector<char> getOperands() const { return operands; }

    double calculate(const std::map<char, double>& values = {});
};

#endif