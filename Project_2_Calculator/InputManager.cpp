// This file implements the InputManager class, which provides methods to get valid numerical input and menu choices from the user.
// It uses Windows API functions to set console text attributes for better user experience and interacts with the SoundManager
// to provide audio feedback for invalid inputs and successful actions. The InputManager also relies on the current theme
// settings to determine the colors used for prompts and error messages.

#include <iostream>
#include <cmath>
#include <limits>
#include <istream>
#define NOMINMAX
#include <windows.h>
#include <vector>
#include <string>
#include "InputManager.h"
#include "Theme.h"
#include "CalculatorUI.h"
#include "SoundManager.h"


// External functions and variables used by InputManager
extern Theme currentTheme;

using namespace std;

// InputManager implementation
double InputManager::getValidNumber(HANDLE h, const char* prompt, SoundManager& sound) {
    
    double value;

    SetConsoleTextAttribute(h, currentTheme.inputColor);
    cout << prompt;
    SetConsoleTextAttribute(h, 7);

    cin >> value;

    while (cin.fail()) {
        sound.playErrorSound();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        SetConsoleTextAttribute(h, currentTheme.errorColor);
        cout << "Invalid input. Please enter a number: ";
        SetConsoleTextAttribute(h, 7);

        cin >> value;
    }

    return value;
}

// Function to get a valid menu choice from the user, ensuring the input is a number between 1 and 10
int InputManager::getMenuChoice(HANDLE h, SoundManager& sound) {
    
	CalculatorUI ui; // Create an instance of CalculatorUI to use printWide function
    
    int choice;

    ui.printWide(L"Choose an operation (1-10): ");
    cin >> choice;

    while (cin.fail() || choice < 1 || choice > 10) {
        sound.playErrorSound();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        SetConsoleTextAttribute(h, currentTheme.errorColor);
        cout << "Invalid choice. Please enter a number between 1 and 10: ";
        SetConsoleTextAttribute(h, 7);

        cin >> choice;
    }

    sound.playBeep(750, 80);
    return choice;
}