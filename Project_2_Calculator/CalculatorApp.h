// This header file defines the CalculatorApp class, which serves as the main application class for the calculator application.
// It includes all necessary components such as the user interface, input management, calculation engine, history management,
// theme management, and sound management.

#pragma once
#include <windows.h>
#include "CalculatorUI.h"
#include "InputManager.h"
#include "CalculatorEngine.h"
#include "HistoryManager.h"
#include "ThemeManager.h"
#include "SoundManager.h"

// Forward declaration of currentTheme variable for theme management
class CalculatorApp {
private:
    HANDLE h;
    CalculatorUI ui;
    InputManager input;
    CalculatorEngine engine;
    HistoryManager history;
    ThemeManager themeManager;
    SoundManager sound;

// Public interface for the CalculatorApp class
public:
    CalculatorApp();
    void run();
};