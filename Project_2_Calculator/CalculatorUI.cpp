// This file implements the CalculatorUI class, which provides methods to manage the user interface of a console-based calculator
// application. It includes functions to display the footer, transition between screens, show calculation results, render
// the main menu, and handle console effects such as fade-in and fade-out animations. The UI is designed to be visually
// appealing and user-friendly, with support for themes and color customization.

#include <iostream>
#include <cmath>
#include <limits>
#include <istream>
#define NOMINMAX
#include <windows.h>
#include <vector>
#include <string>

#include "CalculatorUI.h"
#include "ConsoleEffects.h"
#include "Theme.h"

extern Theme currentTheme;

using namespace std;

void CalculatorUI::renderCenteredMenu(HANDLE h) {
    ConsoleEffects effects(h);

    vector<wstring> menuLines = {
        L"┌──────────────────────────────────────┐",
        L"│        PLEASE MAKE A SELECTION       │",
        L"├──────────────────────────────────────┤",
        L"│ 1. Addition (+)                      │",
        L"│ 2. Subtraction (-)                   │",
        L"│ 3. Multiplication (*)                │",
        L"│ 4. Division (/)                      │",
        L"│ 5. Power (^)                         │",
        L"│ 6. Modulus (%)                       │",
        L"│ 7. Square Root (s)                   │",
        L"│ 8. Exit                              │",
        L"│ 9. View History                      │",
        L"│ 10. Change Theme                     │",
        L"│ 11. Memory Add (M+)                  │",
        L"│ 12. Memory Subtract (M-)             │",
        L"│ 13. Memory Recall (MR)               │",
        L"│ 14. Memory Clear (MC)                │",
        L"└──────────────────────────────────────┘"
    };

    SetConsoleTextAttribute(h, currentTheme.menuColor);

    // Fade-in effect, but centered
    for (const auto& line : menuLines) {
        printCentered(line);
        Sleep(40);
    }

    SetConsoleTextAttribute(h, 7);

    showFooter(h);
}

// Function to highlight the selected menu option by changing the console text color and displaying a message indicating the
// selection is being processed, then resetting the text color back to default after a brief pause and
// providing visual feedback to the user.
void CalculatorUI::highlightOption(HANDLE h, int option) {
    SetConsoleTextAttribute(h, currentTheme.inputColor);

    wstring msg = L"> Option ";
    msg += to_wstring(option);
    msg += L" selected...\n";

    printWide(msg.c_str());

    SetConsoleTextAttribute(h, 7);
    Sleep(150);
}

// Function to display a footer with a message and decorative lines, using the current theme's title color for the text
// to enhance the visual appeal of the console application and provide a consistent look and feel across different screens.
void CalculatorUI::showFooter(HANDLE h) {
    SetConsoleTextAttribute(h, currentTheme.titleColor);

    printCentered(L"");  // spacing
    printCentered(L"──────────────────────────────────────────────");
    printCentered(L"Made with ❤️  by Mark | C++ Calculator App");
    printCentered(L"──────────────────────────────────────────────");

    SetConsoleTextAttribute(h, 7);
}

// Function to handle the transition between screens by fading out the current screen, clearing it, and then fading in the next screen
// to create a smooth visual effect for the user, enhancing the overall user experience of the console application.
void CalculatorUI::transition(HANDLE h) {
    ConsoleEffects effects(h);

    // Fade out the current screen
    effects.fadeOut(5, 60);

    // Clear the screen
    clearScreen(h);

    // Fade in the next screen
    effects.fadeIn(5, 60);
}

// Function to pause the program and wait for the user to press ENTER, allowing them to read messages or results before
// continuing to the next operation, enhancing the user experience by giving them control over the flow of the application.
void CalculatorUI::pause() {
    cout << "\nPress ENTER to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Function to display the result of a calculation in a visually appealing box format, using the current theme's result color
// and ensuring that the result is properly formatted without trailing zeros, enhancing the user experience by providing
// clear and concise feedback.
void CalculatorUI::showResult(HANDLE h, double result) {
    SetConsoleTextAttribute(h, currentTheme.resultColor);

    const int boxWidth = 38;  // width inside the borders
    std::wstring label = L"│   Result: ";
    std::wstring value = std::to_wstring(result);

    // Remove trailing zeros from to_wstring
    value.erase(value.find_last_not_of(L'0') + 1, std::wstring::npos);
    if (value.back() == L'.') value.pop_back();

    std::wstring line = label + value;

    // Calculate padding
    int padding = boxWidth - static_cast<int>(line.length());
    if (padding < 0) padding = 0; // safety

    line.append(padding, L' ');
    line += L" │\n";

    // Print box
    printWide(L"\n┌──────────────────────────────────────┐\n");
    printWide(line.c_str());
    printWide(L"└──────────────────────────────────────┘\n");

    SetConsoleTextAttribute(h, 7);
}

// Function to get the current width of the console window by retrieving the console screen buffer information
// and calculating the width based on the window's left and right coordinates to ensure that text can be centered
// properly within the available space.
int CalculatorUI::getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

// Function to print a given wide string centered in the console, calculating the necessary padding based on the console width 
// to ensure that text is visually centered and aligned properly within the available space.
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

// CalculatorUI implementation to print wide characters to the console, ensuring proper handling of
// Unicode text and enhancing the visual presentation of the application.
void CalculatorUI::printWide(const wchar_t* text) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written;
    WriteConsoleW(hConsole, text, wcslen(text), &written, NULL);
}

// Function to clear the console screen by filling it with spaces and resetting the cursor position to the top-left corner,
// ensuring a clean slate for the next output and improving the visual clarity of the console application.
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

// Function to display the title screen of the calculator application with a typewriter effect and wait for user input to
// continue the program, enhancing the user experience with a visually appealing introduction.
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

// Extra function just in case the given programmer wants to use a different menu rendering style,
// but currently not used in the main application flow to keep the menu consistent with the rest of the UI design.
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

    showFooter(h);
}