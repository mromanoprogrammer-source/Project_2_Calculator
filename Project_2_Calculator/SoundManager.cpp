// This file implements the SoundManager class, which provides methods to play different types of sounds using the Windows API.
// The class includes methods to play a beep sound with specified frequency and duration,
// as well as methods to play predefined error and success sounds. The implementation uses the Beep and MessageBeep functions
// from the Windows API to produce the desired sounds, and includes a short sleep after each sound to ensure they are heard
// clearly without overlapping with subsequent sounds. The SoundManager class can be used throughout the calculator
// application to provide audio feedback for user actions and events.

#include "SoundManager.h"
#include <windows.h>

// SoundManager implementation
void SoundManager::playBeep(int frequency, int duration) {
    Beep(frequency, duration);
    Sleep(80);
}

// Plays a standard error sound using the Windows API
void SoundManager::playErrorSound() {
    MessageBeep(MB_ICONHAND);
    Sleep(80);
}

// Plays a simple success sound using the Windows API
void SoundManager::playSuccessSound() {
    Beep(1000, 120);
    Sleep(80);
}