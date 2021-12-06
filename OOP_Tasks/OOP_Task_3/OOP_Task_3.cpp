/*
VS STUDIO 2022 17.0.1

ВАРИАНТ 7
Б9120-09.03.04прогин, подгруппа 4
Рольщиков Максим Евгеньевич

Условия задачи:
1) Написать функцию, которая записывает в бинарный файл данные о сканере из приведенной структуры.
Структура файла: в первых 4 байтах размещается значение типа int,
определяющее количество сделанных в файл записей; далее без пропусков размещаются записи о сканерах.

РЕАЛИЗАЦИЯ В: write_scan_to_file


2) Написать функцию, которая вводит данные о сканере с клавиатуры в структуру типа scan_info,
и, если данные об этом сканере отсутствуют в файле, помещает содержимое структуры в конец файла;
в противном случае выдает соответствующее сообщение.

РЕАЛИЗАЦИЯ В: read_scan_from_user_and_write_to_file

!!!Остальные функции всмогательные!!!
*/

#include <iostream>
#include <fstream>
#include <string>
#include "maro.h"

using namespace std;

/// <summary> Структура информации о сканере </summary>
struct scan_info
{
    string model; //название модели
    int price; //цена модели
    double size_x; //ширина области сканирования
    double size_y; //высота области сканирования
    int optr; //оптическое разрешение
    int grey; //градации серого

    bool operator==(const scan_info &other) const
    {
        bool temp = model == other.model;
        temp = temp && price == other.price;
        temp = temp && size_x == other.size_x;
        temp = temp && size_y == other.size_y;
        temp = temp && optr == other.optr;
        temp = temp && grey == other.grey;
        return temp;
    }
};

/// <summary> Выводит информацию о сканере в консоль </summary>
void print_scan_to_console(const scan_info scan)
{
    cout << "\nНазвание модели: " << scan.model;
    cout << "\nЦена: " << scan.price;
    cout << "\nШирина обл. сканирования: " << scan.size_x;
    cout << "\nВысота обл. сканирования: " << scan.size_y;
    cout << "\nОптическое разрешение: " << scan.optr;
    cout << "\nГрадаций серого: " << scan.grey << "\n";
}

/// <summary> Вводит информацию о сканере с клавиатуры в консоли </summary>
scan_info read_scan_from_console()
{
    scan_info temp_scan;

    //Ввод названия сканера
    cout << "Название модели: ";
    getline(cin, temp_scan.model);

    temp_scan.price = SafeConsoleInput<int>("Цена: ", "Ввод с ошибкой! Повторите ввод: ", [](auto& t) { return t>0; });
    temp_scan.size_x = SafeConsoleInput<double>("Ширина обл. сканирования: ", "Ввод с ошибкой! Повторите ввод: ", [](auto& t) { return t > 0; });
    temp_scan.size_y = SafeConsoleInput<double>("Высота обл. сканирования: ", "Ввод с ошибкой! Повторите ввод: ", [](auto& t) { return t > 0; });
    temp_scan.optr = SafeConsoleInput<int>("Оптическое разрешение: ", "Ввод с ошибкой! Повторите ввод: ", [](auto& t) { return t > 0; });
    temp_scan.grey = SafeConsoleInput<int>("Градаций серого: ", "Ввод с ошибкой! Повторите ввод: ", [](auto& t) { return t > 0; });

    return temp_scan;
}

/// <summary> Просто считывает информацию о сканере с текущей позиции в файле и возвращает структуру типа scan_info </summary>
scan_info read_scan_from_cur_pos_in_file(fstream& file)
{
    if (!file.is_open()) exit_with_message("Error: file does not exist!");

    scan_info temp_scan;
    int sz = 0;
    file.read((char*)&sz, 4);
    string model(sz, 0);
    for (int i = 0; i < sz; ++i)
        file.read(&model[i], sizeof(model[0]));

    temp_scan.model = model;
    file.read((char*)&temp_scan.price, sizeof(temp_scan.price));
    file.read((char*)&temp_scan.size_x, sizeof(temp_scan.size_x));
    file.read((char*)&temp_scan.size_y, sizeof(temp_scan.size_y));
    file.read((char*)&temp_scan.optr, sizeof(temp_scan.optr));
    file.read((char*)&temp_scan.grey, sizeof(temp_scan.grey));
    return temp_scan;
}

/// <summary> Проверяет наличие записи о сканере в файле </summary>
bool check_scan_in_file(fstream& file, const scan_info scan)
{
    if (!file.is_open()) exit_with_message("Error: file does not exist!");

    file.seekg(0, ios_base::end);
    if (file.tellg() < 4)
        return false;

    int scaners_count = 0;
    file.seekg(0, ios_base::beg);
    file.read((char*)&scaners_count, 4);

    cout << scaners_count;
    bool scan_already_in_file = false;
    for (int i = 0; i < scaners_count; i++)
    {
        scan_info temp_s = read_scan_from_cur_pos_in_file(file);
        scan_already_in_file = scan == temp_s;
        cout << scan_already_in_file;
        if (scan_already_in_file) break;
    }
    return scan_already_in_file;
}

/// <summary> Записывает информацию о сканере в конец файла </summary>
void write_scan_to_end_file(fstream& file, const scan_info scan)
{
    if (!file.is_open()) exit_with_message("Error: file does not exist!");
    
    file.seekg(0, ios_base::end);
    int sz = scan.model.size();
    file.write((char*) &sz, 4);
    file.write(scan.model.data(), sz);
    file.write((char*) &scan.price, sizeof(scan.price));
    file.write((char*) &scan.size_x, sizeof(scan.size_x));
    file.write((char*) &scan.size_y, sizeof(scan.size_y));
    file.write((char*) &scan.optr, sizeof(scan.optr));
    file.write((char*) &scan.grey, sizeof(scan.grey));
}

/// <summary> Записывает информацию о сканере в конец файла и изменяет значение кол-ва сканеров в файле </summary>
void write_scan_to_file(fstream& file, const scan_info scan)
{
    if (!file.is_open()) { exit_with_message("Error: file does not exist!"); }

    int scaners_count = 0;

    file.seekg(0, ios_base::end);
    if (file.tellg() >= 4) //file not empty
    {
        file.seekg(0, ios_base::beg);
        file.read((char*)&scaners_count, 4);
    }
    scaners_count++;
    file.seekg(0, ios_base::beg);
    file.write((char*)&scaners_count, 4);
    write_scan_to_end_file(file, scan);
}

/// <summary> 
///Считывает информацию о сканере от пользователя и записывает в файл, если такой записи в нём нет.
///</summary>
void read_scan_from_user_and_write_to_file(fstream& file)
{
    if (!file.is_open()) exit_with_message("Error: file does not exist!");
    cout << "ДОБАВЛЕНИЕ НОВОГО СКАНЕРА В ФАЙЛ:\n";
    scan_info scan = read_scan_from_console();
    if (check_scan_in_file(file, scan))
    {
        cout << "Ошибка: Такой сканер уже занесен в файл!\n";
        return;
    }
    write_scan_to_file(file, scan);
}

/// <summary> Выводит информацию о сканерах из файла </summary>
void print_scans_from_file(fstream &file)
{
    if (!file.is_open()) exit_with_message("Error: file does not exist!");

    file.seekg(0, ios_base::end);
    if (file.tellg() < 4) //file is empty
    {
        return;
    }

    file.seekg(0, ios_base::beg);

    //Write number of scaner records in file
    int scaner_count = 0;
    file.read((char*)&scaner_count, 4);
    cout << "Записей о сканерах: " << scaner_count << "\n\n";

    for (int i = 0; i<scaner_count; i++)
    {
        scan_info temp_s = read_scan_from_cur_pos_in_file(file);
        print_scan_to_console(temp_s);
    }
    cout << endl;
}

int main()
{
    setlocale(0, ""); //Включаем кирриллицу
    fstream file("scaners.bin", ios::in | ios::out | ios::binary);

    print_scans_from_file(file);

    read_scan_from_user_and_write_to_file(file);

    scan_info temp_scan { "SCAN 3000" , 3000, 10.4, 3.4, 1200, 256};
    write_scan_to_file(file, temp_scan);

    //temp_scan.model = "SCAN 3220";
    //temp_scan.size_x = 10.4;
    //temp_scan.size_y = 4;
    //temp_scan.price = 4250;
    //temp_scan.optr = 600;
    //temp_scan.grey = 512;
    //write_scan_to_file(file, temp_scan);

    //temp_scan.model = "SCAN 3140";
    //temp_scan.size_x = 10.4;
    //temp_scan.size_y = 7;
    //temp_scan.price = 5000;
    //temp_scan.optr = 1800;
    //temp_scan.grey = 128;
    //write_scan_to_file(file, temp_scan);

    print_scans_from_file(file);

    file.close();
}
