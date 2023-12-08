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

    if (argc != 2) {
        cout << "Ошибка: Неверное количество аргументов." << endl;
        return 1;
    }

    int Size = stoi(argv[1]);

    if (Size % 2 == 0 || Size <= 0) {
        cout << "Ошибка: Размер окна должен быть положительным нечетным числом." << endl;
        return 1;
    }

    // Считывание бинарных данных из stdin
    vector<int> inputData;
    int value = 0;
    while (cin.read(reinterpret_cast<char*>(&value), sizeof(int))) {
        inputData.push_back(value);
    }

    // Применение медианных фильтров
    vector<int> result = applyMedianFilter(inputData, Size);

    for (int val : result) {
        cout.write(reinterpret_cast<const char*>(&val), sizeof(int));
    }
    cout << endl;

    // Закомментированный блок записи в файл (если не требуется)
    /*
    ofstream outputFile("output.bin", ios::binary);
    if (outputFile.is_open()) {
        for (int val : result) {
            outputFile.write(reinterpret_cast<const char*>(&val), sizeof(int));
        }
        outputFile.close();
        cout << "Результат записан в файл: output.bin" << endl;
    }
    else {
        cout << "Ошибка при открытии файла для записи." << endl;
        return 1;
    }
    */

    return 0;
}
