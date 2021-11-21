//#########################
//
// ��������� �������� ������
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

/// <summary> ��������� ���������� ������ ����� � ��������� �� min �� max ������������. </summary>
int random(const int min, const int max)
{
    return rand() % (max - min + 1) + min;
}

/// <summary> �������� � ������� err_msg � ��������� ��������� � ����� 1 </summary>
void exit_with_message(string err_msg)
{
    cerr << err_msg;
    exit(1);
}

/// <summary>
/// ������� �� ������� welcome_msg, ������������ ���� ������������. 
/// ���� ��� ����� �� ������������� T, �� ������� err_msg � ��������� ����.
/// </summary>
template <typename T>
T SafeConsoleInput(string welcome_msg = "", string err_msg = "")
{
    T res;
    bool inputIsNotCorrect = false;
    cout << welcome_msg;
    do {
        if (inputIsNotCorrect) //���� ���� �������� � �������
        {
            cout << err_msg;
            cin.clear(); //��������� � "�������" ���������
            cin.ignore(32767, '\n'); //������� ������ � �����
            inputIsNotCorrect = false;
        }
        cin >> res;
        inputIsNotCorrect = !cin || (cin && cin.peek() != '\n');
    } while (inputIsNotCorrect);

    return res;
}

#endif