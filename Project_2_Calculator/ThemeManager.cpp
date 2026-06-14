// This file implements the ThemeManager class, which provides functionality for allowing users to choose different themes
// for the calculator application. It includes methods to display a theme selection menu, validate user input,
// and update the current theme based on the user's choice. The implementation also incorporates console effects for a
// smoother user experience and sound feedback for successful or erroneous actions.

#include <iostream>
#include <cmath>
#include <limits>
#include <istream>
#define NOMINMAX
#include <windows.h>
#include <vector>
#include <string>
#include "ThemeManager.h"
#include "CalculatorUI.h"
#include "SoundManager.h"

// Include Theme.h for theme definitions and currentTheme variable
extern Theme currentTheme;
extern Theme classic;
extern Theme matrix;
extern Theme sunset;
extern Theme cyberBlue;

CalculatorUI ui; // Create a global instance of CalculatorUI to use printWide and clearScreen functions
SoundManager sound; // Create a global instance of SoundManager to use playErrorSound and playSuccessSound functions

// ThemeManager implementation
using namespace std;

// Function to display theme selection menu and update current theme based on user choice
void ThemeManager::chooseTheme(HANDLE h, SoundManager& sound) {

	// Create ConsoleEffects instance for animations
    ConsoleEffects effects(h);

	// Fade out current menu, clear screen, and show loading bar before displaying theme options
    effects.fadeOut(5, 100);
    ui.clearScreen(h);
    effects.loadingBar(1000);

	// Set menu color for theme selection
    ui.printWide(L"┌──────────────────────────────────────┐\n");
    ui.printWide(L"│            CHOOSE A THEME            │\n");
    ui.printWide(L"├──────────────────────────────────────┤\n");
    ui.printWide(L"│ 1. Classic (Cyan menu, Yellow input) │\n");
    ui.printWide(L"│ 2. Matrix (Everything almost Green)  │\n");
    ui.printWide(L"│ 3. Sunset (Yellow menu, Pink result) │\n");
    ui.printWide(L"│ 4. Cyber Blue (Blue title, Cyan menu)│\n");
    ui.printWide(L"│ 5. Exit                              │\n");
    ui.printWide(L"└──────────────────────────────────────┘\n");

    // Enter theme choice
    int t;
    cin >> t;

	// Validate theme choice input
    while (cin.fail() || t < 1 || t > 5) {
        sound.playErrorSound();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        SetConsoleTextAttribute(h, currentTheme.errorColor);
        cout << "Invalid choice. Please enter a number between 1 and 5: ";
        SetConsoleTextAttribute(h, 7);
        cin >> t;
    }

	// Update current theme based on user choice
    switch (t) {
		// Note: The actual theme definitions (classic, matrix, sunset, cyberBlue) should be defined in Theme.cpp
        // and declared as extern in Theme.h
    case 1: currentTheme = classic; break;
    case 2: currentTheme = matrix; break;
    case 3: currentTheme = sunset; break;
    case 4: currentTheme = cyberBlue; break;
	case 5: // Exit option - return to menu without changing theme
		// Play success sound and show message before returning to menu
        sound.playSuccessSound();
        cout << "Returning to menu..." << endl;
        Sleep(1000);
        return;
    }

	// Play success sound and show confirmation message after changing theme
    sound.playSuccessSound();
    cout << "Theme changed successfully!" << endl;
    Sleep(1000);
}