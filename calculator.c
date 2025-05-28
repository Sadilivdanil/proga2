#include "calculator.h"

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

int fact(int n) {
    if (n <= 0) return 1;

    return fact(n - 1) * n;
}

// Реализация деления с защитой от деления на 0
int divide(int a, int b) {
    if (b == 0) {
        return 0;  // Обработка особого случая
    }
    return a / b;  // Целочисленное деление
} 