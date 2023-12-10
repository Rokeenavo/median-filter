#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <fstream>

using namespace std;

// Медианный фильтр
vector<int> applyMedianFilter(const vector<int>& input, int Size) {
    vector<int> result;
    int i, halfWindowSize;
    halfWindowSize = Size / 2;

    // Проходим через каждый элемент входного вектора
    for (i = 0; i < input.size(); ++i) {
        // Определяем границы окна для текущего элемента
        int start = max(0, i - halfWindowSize);
        int end = min(static_cast<int>(input.size()) - 1, i + halfWindowSize);

        // Создаем подвектор, соответствующий текущему окну
        vector<int> window(input.begin() + start, input.begin() + end + 1);

        // Если окно полностью заполнено и не является максимальным, сортируем подвектор
        if (window.size() == Size && Size % 2 != 0) {
            sort(window.begin(), window.end());

            // Находим медиану и добавляем ее в результирующий вектор
            result.push_back(window[halfWindowSize]);
        }
        else {
            // Если окно не полностью заполнено или является максимальным, добавляем текущий элемент как есть
            result.push_back(input[i]);
        }
    }

    return result;
}


int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    if (argc < 2 || argc > 3) {
        cout << "Ошибка: Неверное количество аргументов командной строки." << endl;
        return 1;
    }

    // Преобразование второго аргумента командной строки в размер окна
    int Size = stoi(argv[1]);

    if (Size % 2 == 0 || Size <= 0) {
        cout << "Ошибка: Некорректный размер окна." << endl;
        return 1;
    }

    // Проверка наличия данных в stdin
    if (cin.peek() != EOF) {
        vector<int> inputData;
        int value = 0;

        // Считывание бинарных данных из stdin
        while (cin.read(reinterpret_cast<char*>(&value), sizeof(int))) {
            inputData.push_back(value);
        }

        // Проверка успешности чтения из стандартного ввода
        if (cin.eof() && inputData.empty()) {
            cout << "Ошибка: Не удалось прочитать данные из стандартного ввода." << endl;
            return 1;
        }

        // Применение медианных фильтров
        vector<int> result = applyMedianFilter(inputData, Size);

        // Вывод результатов в стандартный вывод
        for (int val : result) {
            cout.write(reinterpret_cast<const char*>(&val), sizeof(int));
        }

        // Запись результатов в файл, если указан аргумент -o
        if (argc == 3 && string(argv[2]) == "-o") {
            ofstream outputFile("test_out.bin", ios::binary);
            if (outputFile.is_open()) {
                for (int val : result) {
                    outputFile.write(reinterpret_cast<const char*>(&val), sizeof(int));
                }
                outputFile.close();
            }
            else {
                cout << "Ошибка: Не удалось открыть файл для записи." << endl;
                return 1;
            }
        }
    }
    else {
        cout << "Ошибка: Нет входных данных для обработки." << endl;
        return 1;
    }

    return 0;
}
