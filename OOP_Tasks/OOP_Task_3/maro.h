//#########################
//
// Various useful methods
// 
//#########################

#ifndef MARO_H
#define MARO_H

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::cerr;
using std::cin;

/// <summary> Generates a random Integer number between min and max inclusive. </summary>
int random(const int min, const int max)
{
    return rand() % (max - min + 1) + min;
}

/// <summary> Prints err_msg to the console and terminates the programme with code 1 </summary>
void exit_with_message(const char* err_msg)
{
    cerr << err_msg;
    exit(1);
}

/// <summary>
/// Outputs welcome_msg to the console, handles user input. 
/// If the input type does not satisfy T, outputs err_msg and repeats the input.
/// </summary>
template <typename T>
T SafeConsoleInput(const char* welcome_msg = "", const char* err_msg = "", bool(*expression)(T&) = [] {})
{
    T res;
    bool inputIsNotCorrect = false;
    cout << welcome_msg;
    do {
        if (inputIsNotCorrect) //If the input is faulty
        {
            cout << err_msg;
            cin.clear(); //Switching to the "normal" state
            cin.ignore(32767, '\n'); //Clearing the data in the input
            inputIsNotCorrect = false;
        }
        cin >> res;
        inputIsNotCorrect = !cin || (cin && cin.peek() != '\n') || !expression(res);
    } while (inputIsNotCorrect);

    return res;
}

#endif