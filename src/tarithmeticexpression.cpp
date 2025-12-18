#include "tarithmeticexpression.h"
#include <sstream>
#include <cmath>
#include <stdexcept>
#include <cctype>
#include <algorithm>
#include <iostream>

TArithmeticExpression::TArithmeticExpression(const std::string& expr)
    : infix(expr) {
    // Приоритеты операций
    priority["+"] = 1;
    priority["-"] = 1;
    priority["*"] = 2;
    priority["/"] = 2;
    priority["sin"] = 3;
    priority["cos"] = 3;

    // Регистрация функций
    functions["sin"] = [](double x) { return sin(x); };
    functions["cos"] = [](double x) { return cos(x); };

    toPostfix();
}

bool TArithmeticExpression::isOperator(char c) const {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool TArithmeticExpression::isDigit(char c) const {
    return std::isdigit(static_cast<unsigned char>(c)) || c == '.';
}

bool TArithmeticExpression::isLetter(char c) const {
    return std::isalpha(static_cast<unsigned char>(c));
}

bool TArithmeticExpression::isFunction(const std::string& token) const {
    return functions.find(token) != functions.end();
}

int TArithmeticExpression::getPriority(const std::string& op) const {
    auto it = priority.find(op);
    return (it != priority.end()) ? it->second : 0;
}

void TArithmeticExpression::toPostfix() {
    TStack<std::string> stack;
    postfix = "";
    operands.clear();

    size_t i = 0;
    while (i < infix.length()) {
        char c = infix[i];

        if (c == ' ') {
            i++;
            continue;
        }

        // Проверка на sin, cos
        if (isLetter(c)) {
            std::string token;
            while (i < infix.length() && isLetter(infix[i])) {
                token += infix[i];
                i++;
            }

            if (isFunction(token) && i < infix.length() && infix[i] == '(') {
                stack.push(token);
                continue; 
            }

            else if (token.length() == 1) {
                postfix += token + " ";
                if (std::find(operands.begin(), operands.end(), token[0]) == operands.end()) {
                    operands.push_back(token[0]);
                }
                continue;
            }
            else {
                throw std::invalid_argument("Unknown function or variable: " + token);
            }
        }

        // Если число
        if (isDigit(c)) {
            std::string num;
            while (i < infix.length() && (isDigit(infix[i]) || infix[i] == '.')) {
                num += infix[i];
                i++;
            }
            postfix += num + " ";
            continue;
        }

        if (c == '(') {
            stack.push("(");
            i++;
            continue;
        }

        if (c == ')') {
            while (!stack.isEmpty() && stack.peek() != "(") {
                postfix += stack.pop() + " ";
            }
            if (stack.isEmpty()) {
                throw std::invalid_argument("Mismatched parentheses");
            }
            stack.pop(); 

            if (!stack.isEmpty() && isFunction(stack.peek())) {
                postfix += stack.pop() + " ";
            }
            i++;
            continue;
        }

        // Если оператор
        if (isOperator(c)) {
            std::string op(1, c);
            while (!stack.isEmpty() && stack.peek() != "(" &&
                getPriority(stack.peek()) >= getPriority(op)) {
                postfix += stack.pop() + " ";
            }
            stack.push(op);
            i++;
            continue;
        }

        throw std::invalid_argument("Invalid character: " + std::string(1, c));
    }

    while (!stack.isEmpty()) {
        if (stack.peek() == "(") {
            throw std::invalid_argument("Mismatched parentheses");
        }
        postfix += stack.pop() + " ";
    }

    5
    if (!postfix.empty() && postfix.back() == ' ') {
        postfix.pop_back();
    }
}

double TArithmeticExpression::calculate(const std::map<char, double>& values) {
    TStack<double> stack;
    std::istringstream iss(postfix);
    std::string token;

    while (iss >> token) {
        // Если оператор
        if (token.length() == 1 && isOperator(token[0])) {
            if (stack.getSize() < 2) {
                throw std::invalid_argument("Not enough operands for " + token);
            }

            double b = stack.pop();
            double a = stack.pop();
            double result = 0;

            switch (token[0]) {
            case '+': result = a + b; break;
            case '-': result = a - b; break;
            case '*': result = a * b; break;
            case '/':
                if (fabs(b) < 1e-12) {
                    throw std::runtime_error("Division by zero");
                }
                result = a / b;
                break;
            }
            stack.push(result);
        }
        // Если функция
        else if (isFunction(token)) {
            if (stack.isEmpty()) {
                throw std::invalid_argument("No argument for function " + token);
            }

            double arg = stack.pop();
            double result = functions[token](arg);
            stack.push(result);
        }
        // Если переменная
        else if (token.length() == 1 && isLetter(token[0])) {
            auto it = values.find(token[0]);
            if (it != values.end()) {
                stack.push(it->second);
            }
            else {
                throw std::invalid_argument("No value for variable: " + token);
            }
        }
        // Если число
        else {
            try {
                double num = std::stod(token);
                stack.push(num);
            }
            catch (...) {
                throw std::invalid_argument("Invalid number: " + token);
            }
        }
    }

    if (stack.getSize() != 1) {
        throw std::invalid_argument("Invalid expression format");
    }

    return stack.pop();
}