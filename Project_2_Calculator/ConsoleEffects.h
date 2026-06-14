// This code defines a class called ConsoleEffects that provides various animation effects for the console.
// It includes methods for displaying text with a typewriter effect, showing a loading bar, fading out the console, and fading in a menu.
// The class uses a HANDLE to interact with the console for performing these effects.

#pragma once
#include <windows.h>
#include <string>
#include <vector>

// Forward declaration of ConsoleEffects class
class ConsoleEffects {
// Private member to hold the console handle for performing effects
private:
    HANDLE h;

// Public interface for ConsoleEffects class, providing various console animation effects
public:
    ConsoleEffects(HANDLE consoleHandle);

	// Function to display text with a typewriter effect, where characters appear one by one with a delay
    void typewriter(const std::string& text, int speed = 20);
    void loadingBar(int duration = 800);
    void fadeOut(int steps = 5, int delay = 40);
    void fadeInMenu(const std::vector<std::wstring>& lines, int delay = 60);
    void fadeIn(int steps, int delay);
};

