//#########################
//
// Различные полезные методы
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

/// <summary> Генерация случайного ЦЕЛОГО числа в диапазоне от min до max включительно. </summary>
int random(const int min, const int max)
{
    return rand() % (max - min + 1) + min;
}

/// <summary> Печатает в консоль err_msg и завершает программу с кодом 1 </summary>
void exit_with_message(string err_msg)
{
    cerr << err_msg;
    exit(1);
}

/// <summary>
/// Выводит на консоль welcome_msg, обрабатывает ввод пользователя. 
/// Если тип ввода не удовлетворяет T, то выводит err_msg и повторяет ввод.
/// </summary>
template <typename T>
T SafeConsoleInput(string welcome_msg = "", string err_msg = "")
{
    T res;
    bool inputIsNotCorrect = false;
    cout << welcome_msg;
    do {
        if (inputIsNotCorrect) //Если ввод оказался с ошибкой
        {
            cout << err_msg;
            cin.clear(); //Переводим в "обычное" состояние
            cin.ignore(32767, '\n'); //Очищаем данные в вводе
            inputIsNotCorrect = false;
        }
        cin >> res;
        inputIsNotCorrect = !cin || (cin && cin.peek() != '\n');
    } while (inputIsNotCorrect);

    return res;
}

#endif