//ВАРИАНТ 7 - 2
//Б9120-09.03.04прогин, подгруппа 4
//Рольщиков Максим Евгеньевич

#include <iostream>
#include <cmath>
using namespace std;


template <typename T>
void function(T x)
{
    constexpr bool is_float_or_double =
        std::is_same<T, float>::value || std::is_same<T, double>::value;
    
    if (!is_float_or_double)
    {
        cerr << "function: Ошибка! Аргумент (x) не имеет тип float, или double!";
        exit(1);
    }

    T y = abs(3 * x - 0.512) * 9.81 * x*x;
    cout << "y = " << y << endl;

    T temp = (pow(x, 3) - 2 * x * y + 4 * y * y);
    if (temp == 0) 
    { 
        cout << "z = деление на ноль!" << endl; 
        return; 
    }

    T z = (5 * x*x * y - 3) / temp;
    cout << "z = " << z << endl;
}

int main() {
    setlocale(LC_CTYPE, "rus"); //Киррилица в консоли
    cout << endl;

    float xf;
    do {
        if (!cin) //Если была ошибка ввода.
        {
            cout << "Ошибка: Введено не число!" << endl;
            cin.clear(); //Переводим в "обычное" состояние
            cin.ignore(32767, '\n'); //Очищаем данные в вводе
        }
        cout << "Введите параметр X (float): ";
        cin >> xf;
    } while (!cin);

    function(xf);

    double xd;
    do {
        if (!cin) //Если была ошибка ввода.
        {
            cout << "Ошибка: Введено не число!" << endl;
            cin.clear(); //Переводим в "обычное" состояние
            cin.ignore(32767, '\n'); //Очищаем данные в вводе
        }
        cout << "Введите параметр X (double): ";
        cin >> xd;
    } while (!cin);

    function(xd);

    return 0;
}
