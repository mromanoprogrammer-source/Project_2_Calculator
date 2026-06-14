// This file implements the ConsoleEffects class, which provides various visual effects for the console application.
// It includes functions for typewriter text display, loading bar animation, fade-out and fade-in effects,
// and a fade-in effect specifically for menu options. The class uses the Windows API to manipulate console output and timing,
// and it interacts with the Theme class to apply consistent styling across the application.

#include "ConsoleEffects.h"
#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include "Theme.h"
#include "CalculatorUI.h"

// Declare the global theme variable and clearScreen, printWide functions
extern Theme currentTheme; // allows access to your theme variable

// ConsoleEffects class implementation
ConsoleEffects::ConsoleEffects(HANDLE consoleHandle)
    : h(consoleHandle) {
}

// Function to display text with a typewriter effect
void ConsoleEffects::typewriter(const std::string& text, int speed) {
    for (char c : text) {
        std::cout << c;
        Sleep(speed);
    }
}

// Function to display a loading bar animation
void ConsoleEffects::loadingBar(int duration) {
    SetConsoleTextAttribute(h, currentTheme.menuColor);
    std::cout << "\nLoading ";
	// Display 20 blocks over the specified duration
    for (int i = 0; i < 20; i++) {
		// Use ASCII character 219 for a solid block
        std::cout << char(219);
        Sleep(duration / 20);
    }
    SetConsoleTextAttribute(h, 7);
    std::cout << "\n";
}

// Function to simulate a fade-out effect by clearing the screen multiple times
void ConsoleEffects::fadeOut(int steps, int delay) {
	CalculatorUI ui; // Create an instance of CalculatorUI to use clearScreen function
    for (int i = 0; i < steps; i++) {
        ui.clearScreen(h);
        Sleep(delay);
    }
}

// Function to simulate a fade-in effect by gradually clearing the screen and waiting
void ConsoleEffects::fadeIn(int steps, int delay) {
    CalculatorUI ui; // use clearScreen from UI

    // Start with a blank screen
    ui.clearScreen(h);

    // Gradually draw the screen brighter
    for (int i = 0; i < steps; i++) {
        // We simulate fade-in by clearing and waiting
        // (Console has no real alpha blending)
        Sleep(delay);
    }
}

// Function to display menu options with a fade-in effect
void ConsoleEffects::fadeInMenu(const std::vector<std::wstring>& lines, int delay) {
    SetConsoleTextAttribute(h, currentTheme.menuColor);
	CalculatorUI ui; // Create an instance of CalculatorUI to use printWide function
    for (const auto& line : lines) {
        ui.printWide(line.c_str());
        Sleep(delay);
    }
    SetConsoleTextAttribute(h, 7);
}