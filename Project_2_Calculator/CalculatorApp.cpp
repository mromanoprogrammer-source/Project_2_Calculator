// This file implements the CalculatorApp class, which serves as the main application class for the calculator application.
// It includes all necessary components such as the user interface, input management, calculation engine, history management,
// theme management, and sound management. It also handles the memory functions and special options like changing themes and
// exiting the application.

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

        ui.renderCenteredMenu(h);

        int choice = input.getMenuChoice(h, sound);
		ui.highlightOption(h, choice); // Highlight the selected option in the menu 

        // Memory functions
        if (choice == 11) {
            double value = input.getValidNumber(h, "Enter value to add to memory: ", sound);
            engine.addToMemory(value);
            sound.playSuccessSound();
            ui.printCentered(L"Value added to memory.");
            ui.pause();   // lets user press ENTER
            continue;
        }

        if (choice == 12) {
            double value = input.getValidNumber(h, "Enter value to subtract from memory: ", sound);
            engine.subtractFromMemory(value);
            sound.playSuccessSound();
            ui.printCentered(L"Value subtracted from memory.");
            ui.pause();   // lets user press ENTER
            continue;
        }

        if (choice == 13) {
            double mem = engine.getMemory();
            sound.playSuccessSound();
            ui.showResult(h, mem);
            ui.pause();   // lets user press ENTER
            continue;
        }

        if (choice == 14) {
            engine.clearMemory();
            sound.playSuccessSound();
            ui.printCentered(L"Memory cleared.");
            ui.pause();   // lets user press ENTER
            continue;
        }

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