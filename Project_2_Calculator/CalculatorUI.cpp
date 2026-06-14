// This file implements the CalculatorUI class, which provides various methods for managing the user interface
// of the calculator application. It includes methods for transitioning between screens, displaying results, getting console width,
// printing centered text, printing wide characters, clearing the screen, showing a title screen, and rendering a menu.
// The implementation uses the Windows API for handling console output and input, as well as animations and effects to enhance the
// user experience. The class interacts with other components such as ConsoleEffects for animations and Theme for managing
// the color scheme of the UI.

#include "CalculatorUI.h"
#include "ConsoleEffects.h"
#include "Theme.h"
#include <iostream>

extern Theme currentTheme;

using namespace std;

void CalculatorUI::transition(HANDLE h) {
    ConsoleEffects effects(h);

    // Fade out the current screen
    effects.fadeOut(5, 60);

    // Clear the screen
    clearScreen(h);

    // Fade in the next screen
    effects.fadeIn(5, 60);
}

// Function to display the result of a calculation in a formatted box with the appropriate color based on the current theme
void CalculatorUI::showResult(HANDLE h, double result) {
    SetConsoleTextAttribute(h, currentTheme.resultColor);

    printWide(L"\n┌──────────────────────────────────────┐\n");

    // Build the result line dynamically
    std::wstring resultText = L"│   Result: ";
    resultText += std::to_wstring(result);
    resultText += L"                      │\n";

    printWide(resultText.c_str());
    printWide(L"└──────────────────────────────────────┘\n");

    SetConsoleTextAttribute(h, 7);
}

// Function to get the current width of the console window by retrieving the console screen buffer information
int CalculatorUI::getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

// Function to print a given wide string centered in the console, calculating the necessary padding based on the console width
void CalculatorUI::printCentered(const std::wstring& text) {
    int width = getConsoleWidth();
    int padding = (width - static_cast<int>(text.length())) / 2;

    std::wstring padded;
    padded.append(padding, L' ');
    padded += text;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written;
    WriteConsoleW(hConsole, padded.c_str(), padded.length(), &written, NULL);
    WriteConsoleW(hConsole, L"\n", 1, &written, NULL);
}

// CalculatorUI implementation
void CalculatorUI::printWide(const wchar_t* text) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written;
    WriteConsoleW(hConsole, text, wcslen(text), &written, NULL);
}

// Function to clear the console screen by filling it with spaces and resetting the cursor position
void CalculatorUI::clearScreen(HANDLE h) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cellCount;

    if (!GetConsoleScreenBufferInfo(h, &csbi)) return;

    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    FillConsoleOutputCharacter(h, (TCHAR)' ', cellCount, { 0, 0 }, &count);
    FillConsoleOutputAttribute(h, csbi.wAttributes, cellCount, { 0, 0 }, &count);
    SetConsoleCursorPosition(h, { 0, 0 });
}

// Function to display the title screen of the calculator application with a typewriter effect and wait for user input to continue
void CalculatorUI::showTitleScreen(HANDLE h) {
    ConsoleEffects effects(h);
    effects.fadeIn(5, 80);   // Smooth fade-in before showing title

    SetConsoleTextAttribute(h, currentTheme.titleColor);

    
	// Ignoring the original box design to ensure it fits within typical console widths and looks good with the fade-in effect
    //printCentered(L"┌──────────────────────────────────────┐\n");
    //printCentered(L"│                                      │\n");
    //printCentered(L"│              CALCULATOR              │\n");
    //printCentered(L"│                                      │\n");
    //printCentered(L"└──────────────────────────────────────┘\n");

	// A more compact title design that fits well with the fade-in effect and looks good on various console widths
    printCentered(L"┌──────────────────────────────┐");
    printCentered(L"│                              │");
    printCentered(L"│         CALCULATOR           │");
    printCentered(L"│                              │");
    printCentered(L"└──────────────────────────────┘");

    SetConsoleTextAttribute(h, 7);

    printCentered(L"Welcome to the C++ Calculator!");
    Sleep(300);

    cout << "Press ENTER to continue...";
    cin.get();
}

// Function to render the main menu of the calculator application with a fade-in effect,
// displaying various operation options for the user to choose from
void CalculatorUI::renderMenu(HANDLE h) {
    ConsoleEffects effects(h);

    vector<wstring> menuLines = {
        L"\n┌──────────────────────────────────────┐\n",
        L"│        PLEASE MAKE A SELECTION       │\n",
        L"├──────────────────────────────────────┤\n",
        L"│ 1. Addition (+)                      │\n",
        L"│ 2. Subtraction (-)                   │\n",
        L"│ 3. Multiplication (*)                │\n",
        L"│ 4. Division (/)                      │\n",
        L"│ 5. Power (^)                         │\n",
        L"│ 6. Modulus (%)                       │\n",
        L"│ 7. Square Root (s)                   │\n",
        L"│ 8. Exit                              │\n",
        L"│ 9. View History                      │\n",
        L"│ 10. Change Theme                     │\n",
        L"└──────────────────────────────────────┘\n"
    };

    SetConsoleTextAttribute(h, currentTheme.menuColor);
    effects.fadeInMenu(menuLines, 40);
    SetConsoleTextAttribute(h, 7);
}