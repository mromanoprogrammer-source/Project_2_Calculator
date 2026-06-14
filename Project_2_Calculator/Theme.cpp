// This file defines the theme presets for the calculator application, specifying color attributes for various
// UI elements such as menu, input, error messages, results, and title.
// It also initializes the current theme to the classic preset by default.

#include "Theme.h"

// Define the theme presets with specific color attributes for menu, input, error messages, results, and title
Theme classic = { 11, 14, 12, 10, 11 };
Theme matrix = { 10, 14, 12, 11, 10 };
Theme sunset = { 6, 14, 12, 13, 6 };
Theme cyberBlue = { 9, 14, 12, 11, 9 };

// Initialize the current theme to the classic preset by default
Theme currentTheme = classic;