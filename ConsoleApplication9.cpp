#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>

using namespace std;

// Медианный фильтр
vector<int> applyMedianFilter(const vector<int>& input, int Size) {
    vector<int> result;
    int i, median, halfWindowSize;
    halfWindowSize = Size / 2;

    // Проходим по каждому элементу входного вектора
    for (i = 0; i < input.size(); ++i) {
        // Определяем границы окна для текущего элемента
        int start = max(0, i - halfWindowSize);
        int end = min(static_cast<int>(input.size()) - 1, i + halfWindowSize);

        // Создаем подвектор, соответствующий текущему окну
        vector<int> window(input.begin() + start, input.begin() + end + 1);

        // Сортируем подвектор
        sort(window.begin(), window.end());

        // Находим медиану и добавляем ее в результирующий вектор
        median = window[window.size() / 2];
        result.push_back(median);
    }

    return result;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");
    int value, Size;

    if (argc != 2) {
        cout << "Ошибка: Неверное количество аргументов." << endl;
        return 1;
    }

    try {
        // Преобразование аргумента размера окна в число
        Size = stoi(argv[1]);

        if (Size <= 0) {
            cout << "Ошибка: Размер окна должен быть положительным числом." << endl;
            return 1;
        }

        // Считывание входных данных
        vector<int> inputData;
        while (cin >> value) {
            inputData.push_back(value);
        }

        // Применение медианных фильтров
        vector<int> result = applyMedianFilter(inputData, Size);

        // Вывод результата с использованием цикла
        cout << "Результат применения медианных фильтров:" << endl;
        for (const int& value : result) {
            cout << value << ' ';
        }
        cout << '\n';

        return 0;
    }
    catch (const invalid_argument& e) {
        // Обработка ошибки при некорректном аргументе
        cout << "Ошибка: Некорректный аргумент - " << e.what() << endl;
        return 1;
    }
    catch (const out_of_range& e) {
        // Обработка ошибки при выходе за пределы диапазона
        cout << "Ошибка: Выход за пределы диапазона - " << e.what() << endl;
        return 1;
    }
}
