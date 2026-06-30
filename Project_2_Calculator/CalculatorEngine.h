// This header file defines the CalculatorEngine class, which contains a method to perform basic arithmetic operations
// based on user input. The calculate method takes an integer representing the user's choice of operation,
// two double values for the operands, and a reference to a boolean to indicate success or failure of the calculation.

#pragma once
#include <windows.h>

//  Forward declaration of CalculatorEngine class
class CalculatorEngine {

private:
    double memory = 0.0;

public:
    double calculate(int choice, double num1, double num2, bool& success);

public:
    double getMemory() const { return memory; }
    void addToMemory(double value) { memory += value; }
    void subtractFromMemory(double value) { memory -= value; }
    void clearMemory() { memory = 0.0; }
};