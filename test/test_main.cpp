#include <iostream>
#include <map>
#include <cmath>
#include "tarithmeticexpression.h"

void testAll() {
    std::cout << "=== CALCULATOR WITH sin()/cos() ===\n\n";

    // Простые выражения
    std::cout << "1. Basic arithmetic:\n";
    TArithmeticExpression e1("2+3*4");
    std::cout << "   2+3*4 = " << e1.calculate() << " (expected: 14)\n";

    TArithmeticExpression e2("(2+3)*4");
    std::cout << "   (2+3)*4 = " << e2.calculate() << " (expected: 20)\n";

    // Функции
    std::cout << "\n2. Functions:\n";
    TArithmeticExpression e3("sin(0)");
    std::cout << "   sin(0) = " << e3.calculate() << " (expected: 0)\n";

    TArithmeticExpression e4("cos(0)");
    std::cout << "   cos(0) = " << e4.calculate() << " (expected: 1)\n";

    TArithmeticExpression e5("sin(1.5708)"); // π/2
    std::cout << "   sin(π/2) ≈ " << e5.calculate() << " (expected: ~1)\n";

    // Комбинированные
    std::cout << "\n3. Combined:\n";
    TArithmeticExpression e6("2*sin(1.5708) + cos(0)");
    std::cout << "   2*sin(π/2) + cos(0) ≈ " << e6.calculate() << " (expected: ~3)\n";

    TArithmeticExpression e7("sin(a)*cos(b)");
    std::map<char, double> vals = { {'a', 0}, {'b', 0} };
    std::cout << "   sin(0)*cos(0) = " << e7.calculate(vals) << " (expected: 0)\n";
}

int main() {
    try {
        testAll();

        std::cout << "\n=== Interactive mode ===\n";
        std::cout << "Examples: sin(1.57), cos(0), 2*sin(x), etc.\n";
        std::cout << "Type 'quit' to exit.\n\n";

        while (true) {
            std::string expr;
            std::cout << "Enter: ";
            std::getline(std::cin, expr);

            if (expr == "quit") break;
            if (expr.empty()) continue;

            try {
                TArithmeticExpression calc(expr);
                std::cout << "Postfix: " << calc.getPostfix() << "\n";

                auto vars = calc.getOperands();
                if (!vars.empty()) {
                    std::map<char, double> values;
                    for (char v : vars) {
                        double val;
                        std::cout << "Value for " << v << ": ";
                        std::cin >> val;
                        std::cin.ignore();
                        values[v] = val;
                    }
                    std::cout << "Result: " << calc.calculate(values) << "\n";
                }
                else {
                    std::cout << "Result: " << calc.calculate() << "\n";
                }
            }
            catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";
            }
            std::cout << "\n";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}