#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Функция для проверки условия сходимости метода Зейделя
bool isConvergent(const vector<vector<double>>& A) {
    int n = A.size();
    for (int i = 0; i < n; ++i) {
        double sum = 0.0;
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                sum += abs(A[i][j]);
            }
        }
        if (abs(A[i][i]) <= sum) {
            return false; // Не выполнено условие сходимости
        }
    }
    return true; // Условие сходимости выполнено
}

// Функция для решения СЛАУ методом Зейделя
vector<double> gaussSeidel(const vector<vector<double>>& A, const vector<double>& b, double tol, int maxIter) {
    int n = A.size();
    vector<double> x(n, 0.0); // Инициализация начального приближения

    if (!isConvergent(A)) {
        cerr << "Метод Зейделя не сходится для данной системы уравнений." << endl;
        return {};
    }

    vector<double> x_new(n, 0.0); // Временный вектор для хранения нового приближения

    // Итерационный процесс
    int iter = 0;
    while (iter < maxIter) {
        for (int i = 0; i < n; ++i) {
            double sum1 = 0.0;
            double sum2 = 0.0;
            for (int j = 0; j < i; ++j) {
                sum1 += A[i][j] * x_new[j];
            }
            for (int j = i + 1; j < n; ++j) {
                sum2 += A[i][j] * x[j];
            }
            x_new[i] = (b[i] - sum1 - sum2) / A[i][i];
        }

        // Проверка на критерий останова
        double diff = 0.0;
        for (int i = 0; i < n; ++i) {
            diff += abs(x_new[i] - x[i]);
        }
        if (diff < tol) {
            break; // Решение достаточно близко к точному
        }

        x = x_new; // Обновляем текущее приближение
        iter++;
    }

    if (iter == maxIter) {
        cerr << "Достигнуто максимальное количество итераций. Возможно, решение не найдено с заданной точностью." << endl;
        return {};
    }

    return x_new; // Возвращаем решение
}

int main() {

    vector<vector<double>> A = {{3.6, 1.8}, {8, -28}}; // Матрица коэффициентов
    vector<double> b = {7, 24}; // Вектор правых частей
    double tol = 1e-6; // Точность решения
    int maxIter = 1000; // Максимальное количество итераций

    vector<double> solution = gaussSeidel(A, b, tol, maxIter);

    if (!solution.empty()) {
        cout << "Решение:" << endl;
        for (size_t i = 0; i < solution.size(); ++i) {
            cout << "x[" << i << "] = " << solution[i] << endl;
        }
    }

    return 0;
}
