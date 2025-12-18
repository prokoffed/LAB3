#include <iostream>
#include <map>
#include "../include/tarithmeticexpression.h"

using namespace std;

int main() {
    string exprStr;
    cout << "Enter expression: ";
    getline(cin, exprStr);
    
    TArithmeticExpression expr(exprStr);
    cout << "Infix: " << expr.getInfix() << endl;
    cout << "Postfix: " << expr.getPostfix() << endl;
    
    vector<char> operands = expr.getOperands();
    map<char, double> values;
    double val;
    for (char op : operands) {
        cout << "Enter value of " << op << ": ";
        cin >> val;
        values[op] = val;
    }
    
    try {
        double result = expr.calculate(values);
        cout << "Result: " << result << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    
    return 0;
}
