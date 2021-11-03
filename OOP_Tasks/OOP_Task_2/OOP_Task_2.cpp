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

/// <summary> Выбрасывает "мини-исключение" с сообщением err_msg </summary>
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
T CorrectTypeInput(string welcome_msg = "", string err_msg = "")
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
template <class T1, class T2>
class array2D
{
private:
    T1** _array2D = nullptr;
    int _row, _column;

public:
    array2D(int row, int column)
    {
        if (row <= 0 || column <= 0)
            throw_mini_exception("array2D: Error! The number of rows or columns of the array is less than/equal to zero!");

        _row = row; _column = column;
        _array2D = new T2 * [_row];
        for (int i = 0; i < _row; i++)
            for (int j = 0; j < _column; j++)
                _array2D[i] = new T2[_column];
    }

    ~array2D()
    {
        for (int i = 0; i < _row; i++)
            delete[] _array2D[i];
    }

    /// <summary>
    /// Обмен строки с номером l1 на строку с номером l2
    /// </summary>
    void swap_rows(int l1, int l2)
    {
        if (l1 < 0 || l2 < 0)
            throw_mini_exception("swap_rows: Error! A row with a negative index is specified!");
        else if (l1 >= _row || l2 >= _row)
            throw_mini_exception("swap_rows: Error! A row with an index greater than the length of the array is specified!");

        T2* tmp = _array2D[l1];
        _array2D[l1] = _array2D[l2];
        _array2D[l2] = tmp;
    }

    /// <summary>
    /// Выводит элементы массива в консоль
    /// </summary>
    void write_array()
    {
        for (int i = 0; i < _row; i++)
        {
            for (int j = 0; j < _column; j++)
                cout << _array2D[i][j] << " ";
            cout << "\n";
        }
    }

    int get_row_count() { return _row; }
    int get_column_count() { return _column; }
    int get_total_elem_count() { return _row * _column; }

    T2* operator[](int index)
    {
        if (index < 0 || index >= _row)
            throw_mini_exception("Error: The index is less than zero, or greater than the length of the array!");

        return _array2D[index];
    }
};

int main()
{
    int N, M;

    cout << "Enter the number of rows: ";
    do
    {
        N = CorrectTypeInput<int>("", "Entered is not a number! Try again: ");
        if (N <= 0)
            cout << "The number must be greater than zero! Try again: ";
    } while (N <= 0);

    cout << "Enter the number of columns: ";
    do
    {
        M = CorrectTypeInput<int>("", "Entered is not a number! Try again: ");
        if (M <= 0)
            cout << "The number must be greater than zero! Try again: ";
    } while (M <= 0);


    array2D<int, int> arr(N, M); //Объявляем двумерный массив

    //######### Ввод значений вручную ###########
    /*
    //Ввод значений массива
    cout << "\nEnter a matrix:\n";
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++) 
            arr[i][j] = CorrectTypeInput<int>("arr[" + std::to_string(i) + ", " + std::to_string(j) + "]: ", "Input is not a number. Try again: ");*/
    
    //########## Ввод случайных значений ##########
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            arr[i][j] = random(1, 99);

    //Вывод изначального массива
    cout << "\nInitial Matrix:\n";
    arr.write_array();

    //Сортируем пузырьком
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M-1; j++)
        {
            if (arr[j][0] > arr[j + 1][0]) {
                arr.swap_rows(j, j + 1);
            }
        }

    //Вывод конечного массива
    cout << "\nFinal Matrix:\n";
    arr.write_array();

    return 0;
}