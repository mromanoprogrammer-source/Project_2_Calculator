// This file implements the HistoryManager class, which manages the history of calculations performed in the calculator application.
// It allows adding new entries to the history, displaying the history to the user with animations, clearing the history,
// and checking if the history is empty. The implementation uses wide strings to store and display calculation entries,
// and it interacts with the ConsoleEffects and CalculatorUI classes for visual effects and user interface management.

#include <iostream>
#include <cmath>
#include <limits>
#include <istream>
#define NOMINMAX
#include <windows.h>
#include <vector>
#include <string>
#include "HistoryManager.h"
#include "Theme.h"          // for currentTheme
#include "ConsoleEffects.h" // for animations
#include "CalculatorUI.h"   // for printWide and clearScreen

extern Theme currentTheme;

using namespace std;

// HistoryManager implementation
void HistoryManager::add(double num1, double num2, double result, int choice) {
    wchar_t buffer[256];

	// Format the history entry based on the operation choice
    switch (choice) {
		// Note: For square root, num2 is not used, so we only display num1 and the result
    case 1: swprintf(buffer, 256, L"%.2f + %.2f = %.2f", num1, num2, result); break;
    case 2: swprintf(buffer, 256, L"%.2f - %.2f = %.2f", num1, num2, result); break;
    case 3: swprintf(buffer, 256, L"%.2f * %.2f = %.2f", num1, num2, result); break;
    case 4: swprintf(buffer, 256, L"%.2f / %.2f = %.2f", num1, num2, result); break;
    case 5: swprintf(buffer, 256, L"%.2f ^ %.2f = %.2f", num1, num2, result); break;
    case 6: swprintf(buffer, 256, L"%.2f %% %.2f = %.2f", num1, num2, result); break;
    case 7: swprintf(buffer, 256, L"√%.2f = %.2f", num1, result); break;
    }

	// Add the formatted entry to the history vector
    history.push_back(buffer);
}

// Function to display the calculation history to the user, with animations and formatted output
void HistoryManager::show(HANDLE h) {

	CalculatorUI ui; // Create an instance of CalculatorUI to use printWide and clearScreen functions

	// Create ConsoleEffects instance for animations
    ConsoleEffects effects(h);

    effects.fadeOut(5, 100);
    ui.clearScreen(h);
    effects.loadingBar(1000);

    SetConsoleTextAttribute(h, currentTheme.menuColor);
    ui.printWide(L"┌──────────────────────────────────────┐\n");
    ui.printWide(L"│            CALCULATION HISTORY       │\n");
    ui.printWide(L"└──────────────────────────────────────┘\n");
    SetConsoleTextAttribute(h, 7);

    if (history.empty()) {
        ui.printWide(L"No history available.\n");
    } else {
        for (const auto& entry : history) {
            ui.printWide(entry.c_str());
            ui.printWide(L"\n");
        }
    }

    cout << "\nPress ENTER to return to the menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Clear the history vector to remove all entries
void HistoryManager::clear() {
    history.clear();
}

// Check if the history vector is empty, indicating no history entries
bool HistoryManager::empty() const {
    return history.empty();
}