// This header file defines the Theme struct and declares global theme variables for a calculator application.
// The Theme struct contains color attributes for different UI elements such as menu, input, error messages, results, and titles.

#pragma once
#include <windows.h>

// Define the Theme struct to hold color attributes for different UI elements
struct Theme {
    int menuColor;
    int inputColor;
    int errorColor;
    int resultColor;
    int titleColor;
};

// Declare the global theme variable
extern Theme currentTheme;

// Declare the theme presets
extern Theme classic;
extern Theme matrix;
extern Theme sunset;
extern Theme cyberBlue;
