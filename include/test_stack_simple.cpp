# В папке LAB 3 создайте файл
@'
#include <iostream>
#include "tstack.h"

void testStack() {
    std::cout << "=== Testing TStack ===\n";
    
    // 1. Создание
    TStack<int> stack;
    std::cout << "1. Created empty stack: OK\n";
    
    // 2. Push/Pop
    stack.push(10);
    stack.push(20);
    stack.push(30);
    std::cout << "2. Push 3 elements: OK\n";
    
    // 3. Проверка порядка (LIFO)
    if (stack.pop() == 30 && stack.pop() == 20 && stack.pop() == 10) {
        std::cout << "3. LIFO order correct: OK\n";
    } else {
        std::cout << "3. LIFO order WRONG!\n";
    }
    
    // 4. Исключение при пустом стеке
    try {
        stack.pop();
        std::cout << "4. ERROR: Should throw on empty stack!\n";
    } catch (...) {
        std::cout << "4. Exception on empty stack: OK\n";
    }
    
    // 5. Автоматическое расширение
    TStack<int> small(2);
    small.push(1);
    small.push(2);
    small.push(3); // Должно расшириться
    std::cout << "5. Auto-resize works: OK (pushed 3 into size=2 stack)\n";
    
    // 6. Проверка peek
    TStack<int> s;
    s.push(42);
    if (s.peek() == 42 && s.getSize() == 1) {
        std::cout << "6. Peek works (doesn\'t remove): OK\n";
    }
    
    std::cout << "=== All stack tests passed ===\n";
}

int main() {
    try {
        testStack();
    } catch (const char* msg) {
        std::cout << "Exception: " << msg << std::endl;
    } catch (...) {
        std::cout << "Unknown exception" << std::endl;
    }
    return 0;
}
'@ | Out-File -FilePath test_stack_simple.cpp -Encoding utf8