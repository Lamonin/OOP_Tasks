//ВАРИАНТ 7 - 1
//Б9120-09.03.04прогин, подгруппа 4
//Рольщиков Максим Евгеньевич

#include <iostream>
using namespace std;

void isCorrectTriangle(double a, double b, double c)
{
    bool res = (a + b > c) && (a + c > b) && (b + c > a);
    if (!res) {
        cerr << "Ошибка: Введенные стороны не образуют треугольник!";
        exit(1);
    }
}

double calculateHeight(double side, double a, double b, double c)
{
    isCorrectTriangle(a, b, c);
    double p = (a + b + c) / 2; //Полупериметр
    return 2 / side * sqrt(p * (p - a) * (p - b) * (p - c));
}

double calculateMedian(double a, double b, double c)
{
    isCorrectTriangle(a, b, c);
    return 0.5 * sqrt(2 * b * b + 2 * c * c - a * a);
}

double calculateBisect(double a, double b, double c)
{
    isCorrectTriangle(a, b, c);
    double p = (a + b + c) / 2; //Полупериметр
    return 2 / (b + c) * sqrt(b * c * p * (p - a));
}

int main() {
    setlocale(LC_CTYPE, "rus"); //Киррилица в консоли

    double a, b, c;

    //ВАРИАНТ 7
    a = 11.2; b = 10.83; c = 9.31;

    //Для ручного ввода
    //do
    //{
    //    if (!cin) //Если была ошибка ввода.
    //    {
    //        cerr << "Ошибка! Вводите числа!" << endl;
    //        cin.clear(); //Переводим в "обычное" состояние
    //        cin.ignore(32767, '\n'); //Очищаем данные в вводе
    //    }
    //    cout << "Введите стороны треугольника: ";
    //    cin >> a >> b >> c;
    //} while (!cin);

    isCorrectTriangle(a, b, c);
    cout << endl;

    cout << "Высота проведенная к стороне (a) равна: " << calculateHeight(a, a, b, c) << endl;
    cout << "Высота проведенная к стороне (b) равна: " << calculateHeight(b, a, b, c) << endl;
    cout << "Высота проведенная к стороне (c) равна: " << calculateHeight(c, a, b, c) << endl;
    cout << endl;

    cout << "Медиана проведенная к стороне (a) равна: " << calculateMedian(a, b, c) << endl;
    cout << "Медиана проведенная к стороне (b) равна: " << calculateMedian(b, a, c) << endl;
    cout << "Медиана проведенная к стороне (c) равна: " << calculateMedian(c, b, a) << endl;
    cout << endl;

    cout << "Биссектрисса угла A равна: " << calculateBisect(a, b, c) << endl;
    cout << "Биссектрисса угла B равна: " << calculateBisect(b, a, c) << endl;
    cout << "Биссектрисса угла C равна: " << calculateBisect(c, b, a) << endl;

    return 0;
}