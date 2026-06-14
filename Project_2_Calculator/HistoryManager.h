// This code defines a class called HistoryManager that manages the history of calculations in a calculator application. 
// It provides methods to add new entries, display the history, clear the history, and check if the history is empty.
// The class uses a vector of wide strings to store the history entries, which are formatted based on the type of calculation performed.

#pragma once
#include <vector>
#include <string>
#include <windows.h>

// Forward declaration of HistoryManager class
class HistoryManager {
// Private member to hold the history of calculations as a vector of wide strings
private:
    std::vector<std::wstring> history;

// Public interface for HistoryManager class, providing methods to add entries, show history, clear history,
// and check if history is empty
public:
    void add(double num1, double num2, double result, int choice);
    void show(HANDLE h);
    void clear();
    bool empty() const;
};