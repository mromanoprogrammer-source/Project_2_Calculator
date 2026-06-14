// The code defines a class named CalculatorUI that provides various methods for managing the user interface of a calculator application.
// The class includes methods for transitioning between screens, displaying results, getting console width,
// printing centered text, printing wide characters, clearing the screen, showing a title screen, and rendering a menu.
// The class uses the Windows API for handling console output and input.

#pragma once
#include <windows.h>
#include <vector>
#include <string>

// Forward declaration of CalculatorUI class
class CalculatorUI {
public:
    void transition(HANDLE h);
    void showResult(HANDLE h, double result);
    int getConsoleWidth();
    void printCentered(const std::wstring& text);
    void printWide(const wchar_t* text);
    void clearScreen(HANDLE h);
    void showTitleScreen(HANDLE h);
    void renderMenu(HANDLE h);
};