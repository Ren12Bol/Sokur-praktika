#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <limits>
#include <algorithm>    // для std::max
#define NOMINMAX         // <-- важно!
#include <windows.h>    // для SetConsoleCP / SetConsoleOutputCP

using namespace std;

// Метод Гаусса–Жордана
bool gaussJordan(vector<vector<double>> matrix, vector<double>& solution) {
    size_t n = matrix.size();  // <-- size_t вместо int

    for (size_t i = 0; i < n; ++i) {
        size_t maxRow = i;
        for (size_t k = i + 1; k < n; ++k)
            if (std::fabs(matrix[k][i]) > std::fabs(matrix[maxRow][i]))
                maxRow = k;

        if (std::fabs(matrix[maxRow][i]) < 1e-9)
            return false;

        swap(matrix[i], matrix[maxRow]);

        double pivot = matrix[i][i];
        for (size_t j = i; j <= n; ++j)
            matrix[i][j] /= pivot;

        for (size_t k = 0; k < n; ++k) {
            if (k != i) {
                double factor = matrix[k][i];
                for (size_t j = i; j <= n; ++j)
                    matrix[k][j] -= factor * matrix[i][j];
            }
        }
    }

    solution.resize(n);
    for (size_t i = 0; i < n; ++i)
        solution[i] = matrix[i][n];

    return true;
}

int main() {
    // Установка русской локали и кодировки
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    int n;
    cout.precision(6);
    cout << "Введите размерность системы (n): ";
    while (!(cin >> n) || n <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка: Введите натуральное число для n: ";
    }

    vector<vector<double>> matrix(n, vector<double>(n + 1));
    cout << "Введите расширенную матрицу (" << n << " строк по " << n + 1 << " чисел):\n";

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= n; ++j) {
            while (true) {
                cout << "Матрица[" << i << "][" << j << "] = ";
                double val;
                if (cin >> val) {
                    matrix[i][j] = val;
                    break;
                }
                else {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Ошибка ввода. Пожалуйста, введите число.\n";
                }
            }
        }
    }

    vector<double> solution;

    if (gaussJordan(matrix, solution)) {
        cout << "\nРешение системы:\n";
        for (size_t i = 0; i < solution.size(); ++i)
            cout << "x[" << i << "] = " << solution[i] << endl;
    }
    else {
        cout << "\nСистема не имеет единственного решения.\n";
    }

    return 0;
}