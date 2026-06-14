// This code defines the InputManager class, which provides methods for getting valid numbers and menu choices from the user.
// It includes necessary headers such as windows.h for handling Windows-specific functionality, string for string manipulation,
// and SoundManager.h for interacting with the SoundManager class to play sounds based on user input.
// The getValidNumber method prompts the user for a number and validates the input, while the getMenuChoice method allows
// the user to select an option from a menu.

#pragma once
#include <windows.h>
#include <string>
#include "SoundManager.h"

// Forward declaration of InputManager class
class InputManager {
	// Public interface for InputManager class, providing methods to get valid numbers and menu choices from the user
public:
    double getValidNumber(HANDLE h, const char* prompt, SoundManager& sound);
    int getMenuChoice(HANDLE h, SoundManager& sound);
};