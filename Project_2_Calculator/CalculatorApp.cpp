// This file implements the main application logic for the calculator, including the main loop, user input handling,
// and interaction with the UI and sound manager.

#include <iostream>
#include <cmath>
#include <limits>
#include <istream>
#define NOMINMAX
#include <windows.h>
#include <vector>
#include <string>

#include "CalculatorApp.h"
#include "CalculatorUI.h"
#include "SoundManager.h"

extern Theme currentTheme;

using namespace std;

CalculatorApp::CalculatorApp() {
    h = GetStdHandle(STD_OUTPUT_HANDLE);
}

void CalculatorApp::run() {
    
	CalculatorUI ui; // Create an instance of CalculatorUI to use printWide, clearScreen, showTitleScreen, and renderMenu functions
	SoundManager sound; // Create an instance of SoundManager to use playBeep, playErrorSound, and playSuccessSound functions

    ui.showTitleScreen(h);
    ConsoleEffects effects(h);

    //ui.transition(h);

    effects.fadeOut(5, 100);
    ui.clearScreen(h);
    effects.loadingBar(1000);

    char again = 'y';

    while (again == 'y' || again == 'Y') {

        ui.transition(h);

        /*effects.fadeOut(5, 100);
        ui.clearScreen(h);
        effects.loadingBar(1000);*/

        ui.renderMenu(h);

        int choice = input.getMenuChoice(h, sound);

        // Handle special options
        if (choice == 10) {
            themeManager.chooseTheme(h, sound);
            continue;
        }

        if (choice == 8) {
            sound.playSuccessSound();
            cout << "Thank you for using the calculator. Goodbye!\n";
            return;
        }

        if (choice == 9) {
            history.show(h);
            continue;
        }

        // Get numbers
        double num1 = 0, num2 = 0;

        if (choice == 7) {
            num1 = input.getValidNumber(h, "Enter number to find square root of: ", sound);
            num2 = 0;
        }
        else {
            num1 = input.getValidNumber(h, "Enter first number: ", sound);
            num2 = input.getValidNumber(h, "Enter second number: ", sound);
        }

        // Perform calculation
        bool success;
        double result = engine.calculate(choice, num1, num2, success);

        if (!success) {
            SetConsoleTextAttribute(h, currentTheme.errorColor);
            cout << "Error: Invalid operation (divide by zero or negative sqrt)!\n";
            SetConsoleTextAttribute(h, 7);
            continue;
        }

        // Display result
        sound.playSuccessSound();
        ui.showResult(h, result);

        // Add to history
        if (choice == 7)
            history.add(num1, NAN, result, choice);
        else
            history.add(num1, num2, result, choice);

        // Continue?
        sound.playBeep(750, 80);
        cout << "Do you want to perform another calculation? (y/n): ";
        cin >> again;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        while (again != 'y' && again != 'Y' && again != 'n' && again != 'N') {
            sound.playErrorSound();
            SetConsoleTextAttribute(h, currentTheme.errorColor);
            cout << "Invalid choice. Please enter y or n: ";
            SetConsoleTextAttribute(h, 7);
            cin >> again;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    sound.playSuccessSound();
    cout << "Thank you for using the calculator. Goodbye!\n";
}