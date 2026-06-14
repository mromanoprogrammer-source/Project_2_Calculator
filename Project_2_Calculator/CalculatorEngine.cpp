// This file implements the CalculatorEngine class, which provides a method to perform various mathematical operations
// based on user input.The calculate method takes an integer choice representing the operation to perform,
// two double values as operands, and a reference to a boolean variable to indicate success or failure of the operation.
// The method uses a switch statement to determine which operation to execute and handles cases such as division by zero
// and invalid input for square root.

#include "CalculatorEngine.h"
#include <cmath>

// CalculatorEngine implementation
double CalculatorEngine::calculate(int choice, double num1, double num2, bool& success) {
    success = true;

    switch (choice) {
    case 1: // Addition
        return num1 + num2;

    case 2: // Subtraction
        return num1 - num2;

    case 3: // Multiplication
        return num1 * num2;

    case 4: // Division
        if (num2 == 0) {
            success = false;
            return 0;
        }
        return num1 / num2;

    case 5: // Power
        return pow(num1, num2);

    case 6: // Modulus
        if (num2 == 0) {
            success = false;
            return 0;
        }
        return fmod(num1, num2);

    case 7: // Square root
        if (num1 < 0) {
            success = false;
            return 0;
        }
        return sqrt(num1);

    default:
        success = false;
        return 0;
    }
}