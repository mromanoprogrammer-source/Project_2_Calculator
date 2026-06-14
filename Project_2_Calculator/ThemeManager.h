// This header file defines the ThemeManager class, which is responsible for managing the themes of the calculator application.
// It includes necessary headers for handling Windows API, themes, console effects, and sound management.
// The class provides a public method chooseTheme that allows users to select a theme for the calculator,
// taking a HANDLE and a reference to a SoundManager object as parameters.

#pragma once
#include <windows.h>
#include "Theme.h"
#include "ConsoleEffects.h"
#include "SoundManager.h"

// Forward declaration of ThemeManager class
class ThemeManager {
	// Public interface for ThemeManager class, providing a method to allow users to choose a theme for the calculator application
public:
    void chooseTheme(HANDLE h, SoundManager& sound);
};
