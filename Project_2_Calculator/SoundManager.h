// This header file defines the SoundManager class, which provides methods to play different types of sounds using the Windows API.
// The class includes methods for playing a beep sound with specified frequency and duration, as well as methods
// for playing error and success sounds. The implementation of these methods would be provided in a corresponding .cpp file,
// where the Windows API functions would be utilized to produce the desired sounds.

#pragma once
#include <windows.h>

// Forward declaration of SoundManager class
class SoundManager {
	// Public interface for SoundManager class, providing methods to play different types of sounds
public:
    void playBeep(int frequency, int duration);
    void playErrorSound();
    void playSuccessSound();
};