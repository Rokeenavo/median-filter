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

    // Проверка на наличие аргумента командной строки
    if (argc != 2) {
        cout << "Ошибка: Ожидается один аргумент командной строки." << endl;
        return 1;
    }

    int Size = stoi(argv[1]);

    // Проверка корректности введенного размера окна
    if (Size % 2 == 0 || Size <= 0) {
        cout << "Ошибка: Некорректный размер окна." << endl;
        return 1;
    }

    // Считывание бинарных данных из stdin
    vector<int> inputData;
    int value = 0;
    while (cin.read(reinterpret_cast<char*>(&value), sizeof(int))) {
        inputData.push_back(value);
    }

    // Проверка успешности чтения из стандартного ввода
    if (cin.eof()) {
        cout << "Ошибка: Не удалось прочитать данные из стандартного ввода." << endl;
        return 1;
    }

    // Применение медианных фильтров
    vector<int> result = applyMedianFilter(inputData, Size);

    // Вывод результатов в стандартный вывод
    for (int val : result) {
        cout.write(reinterpret_cast<const char*>(&val), sizeof(int));
    }
    cout << endl;

    // Закомментированный блок записи в файл (если не требуется)
    /*
    ofstream outputFile("output.bin", ios::binary);
    if (!outputFile.is_open()) {
        cout << "Ошибка: Не удалось открыть файл для записи." << endl;
        return 1;
    }

    for (int val : result) {
        outputFile.write(reinterpret_cast<const char*>(&val), sizeof(int));
    }
    outputFile.close();
    cout << "Результат записан в файл: output.bin" << endl;
    */

    return 0;
}
