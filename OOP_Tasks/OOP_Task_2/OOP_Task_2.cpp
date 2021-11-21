//ВАРИАНТ 7
//Б9120-09.03.04прогин, подгруппа 4
//Рольщиков Максим Евгеньевич

#include <iostream>
#include <string>
using std::cout;
using std::cerr;
using std::string;

/// <summary> Генерация случайного ЦЕЛОГО числа в диапазоне от min до max включительно. </summary>
int random(const int min, const int max) { return rand() % (max - min + 1) + min; }

/// <summary> Выбрасывает "мини-исключение" с сообщением err_msg и завершает работу программы с кодом 1 </summary>
void throw_mini_exception(string err_msg)
{
    cerr << err_msg;
    exit(1);
}

/// <summary>
/// Выводит на консоль welcome_msg, обрабатывает ввод пользователя. 
/// Если тип ввода не удовлетворяет T, то выводит err_msg и повторяет ввод.
/// </summary>
template <typename T>
T SafeTypeInput(string welcome_msg = "", string err_msg = "")
{
    std::cout << welcome_msg;
    T res;
    do {
        if (!std::cin) //Если ввод оказался с ошибкой
        {
            std::cout << err_msg;
            std::cin.clear(); //Переводим в "обычное" состояние
            std::cin.ignore(32767, '\n'); //Очищаем данные в вводе
        }
        std::cin >> res;
    } while (!std::cin);

    return res;
}

/// <summary> Класс двумерного динамического массива </summary>
template <class T>
class array2D
{
private:
    T** _array = nullptr;
    int _row, _column;

public:
    array2D(int row, int column)
    {
        if (row <= 0 || column <= 0)
            throw_mini_exception("array2D: Error! The number of rows or columns of the array is less than/equal to zero!");

        _row = row; _column = column;
        _array = new T * [_row];
        for (int i = 0; i < _row; i++)
            for (int j = 0; j < _column; j++)
                _array[i] = new T[_column];
    }

    ~array2D()
    {
        if (_array == nullptr) return;
        for (int i = 0; i < _row; i++)
            delete[] _array[i];
        _array = nullptr;
    }

    /// <summary> Производит обмен строки с номером l1 на строку с номером l2 </summary>
    void swap_rows(int l1, int l2)
    {
        if (l1 < 0 || l2 < 0)
            throw_mini_exception("swap_rows: Error! A row with a negative index is specified!");
        else if (l1 >= _row || l2 >= _row)
            throw_mini_exception("swap_rows: Error! A row with an index greater than the length of the array is specified!");

        T* tmp = _array[l1];
        _array[l1] = _array[l2];
        _array[l2] = tmp;
    }

    /// <summary> Выводит элементы массива в консоль </summary>
    void write_array()
    {
        for (int i = 0; i < _row; i++)
        {
            for (int j = 0; j < _column; j++)
                cout << _array[i][j] << " ";
            cout << "\n";
        }
    }

    int get_row_count() { return _row; }
    int get_column_count() { return _column; }
    int get_total_elem_count() { return _row * _column; }

    T* operator[](int index)
    {
        if (index < 0 || index >= _row)
            throw_mini_exception("Error: The index is less than zero, or greater than the length of the array!");

        return _array[index];
    }

    /// <summary> Применяет функцию fn ко всем элементам array2D </summary>
    void ForEach(void(*fn)(T&))
    {
        for (int i = 0; i < _row; i++)
            for (int j = 0; j < _column; j++)
                fn(_array[i][j]);
    }
};

int main()
{
    int N, M;

    cout << "Enter the number of rows: ";
    do
    {
        N = SafeTypeInput<int>("", "Entered is not a number! Try again: ");
        if (N <= 0)
            cout << "The number must be greater than zero! Try again: ";
    } while (N <= 0);

    cout << "Enter the number of columns: ";
    do
    {
        M = SafeTypeInput<int>("", "Entered is not a number! Try again: ");
        if (M <= 0)
            cout << "The number must be greater than zero! Try again: ";
    } while (M <= 0);

    array2D<int> arr(N, M); //Объявляем двумерный массив

    //######### Ввод значений вручную ###########
    /*cout << "\nEnter a matrix:\n";
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            arr[i][j] = SafeTypeInput<int>("arr[" + std::to_string(i) + ", " + std::to_string(j) + "]: ", "Input is not a number. Try again: ");*/

    //########## Ввод случайных значений ##########
    arr.ForEach([](auto& t) {t = random(1, 99); });

    //Вывод изначального массива
    cout << "\nInitial Matrix:\n";
    arr.write_array();

    //Сортируем пузырьком
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M-1; j++)
        {
            if (arr[j][0] > arr[j + 1][0])
                arr.swap_rows(j, j + 1);
        }

    //Вывод конечного массива
    cout << "\nFinal Matrix:\n";
    arr.write_array();

    //arr удалится автоматически

    return 0;
}