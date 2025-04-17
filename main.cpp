#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// Умножение матрицы на вектор
vector<double> matrixVectorMultiply(const vector<vector<double>>& A, const vector<double>& y) {
    int n = A.size();
    vector<double> result(n, 0.0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i] += A[i][j] * y[j];
        }
    }
    return result;
}

// Функция для вычисления производных
// Преобразуем систему 2-го порядка в систему 1-го порядка:
// dy/dt = v
// dv/dt = A*y
void derivatives(const vector<vector<double>>& A,
                 const vector<double>& y,
                 const vector<double>& v,
                 vector<double>& dydt,
                 vector<double>& dvdt) {
    dydt = v;  // dy/dt = v
    dvdt = matrixVectorMultiply(A, y);  // dv/dt = A*y
}

// Метод Эйлера с уточнением для системы 2-го порядка
void eulerWithRefinement(const vector<vector<double>>& A,
                         vector<double>& y,
                         vector<double>& v,
                         double& t,
                         double h) {
    int n = y.size();
    vector<double> dydt(n), dvdt(n);
    vector<double> y_temp(n), v_temp(n);
    vector<double> dydt_temp(n), dvdt_temp(n);

    // Шаг 1: вычисляем производные в начальной точке
    derivatives(A, y, v, dydt, dvdt);

    // Шаг 2: предварительный шаг Эйлера
    for (int i = 0; i < n; i++) {
        y_temp[i] = y[i] + h * dydt[i];
        v_temp[i] = v[i] + h * dvdt[i];
    }

    // Шаг 3: вычисляем производные в новой точке
    derivatives(A, y_temp, v_temp, dydt_temp, dvdt_temp);

    // Шаг 4: уточнение (используем среднее значение производных)
    for (int i = 0; i < n; i++) {
        y[i] += h * 0.5 * (dydt[i] + dydt_temp[i]);
        v[i] += h * 0.5 * (dvdt[i] + dvdt_temp[i]);
    }

    t += h;
}

int main() {
    // Параметры системы
    const int n = 2;  // Размерность системы
    double t0 = 0.0;  // Начальное время
    double h = 0.01;  // Шаг интегрирования
    int steps = 1000; // Количество шагов

    // Матрица коэффициентов A (пример для связанных осцилляторов)
    vector<vector<double>> A = {{-2.0, 1.0},
                                {1.0, -2.0}};

    // Начальные условия: y(0) и y'(0)
    vector<double> y = {1.0, 0.0};  // Начальные положения
    vector<double> v = {0.0, 0.0};  // Начальные скорости

    cout << "Метод Эйлера с уточнением для системы d^2y/dt^2 = A*y" << endl;
    cout << "Шаг h = " << h << endl;
    cout << setw(10) << "t" << setw(15) << "y1(t)" << setw(15) << "y2(t)"
         << setw(15) << "v1(t)" << setw(15) << "v2(t)" << endl;
    cout << setw(10) << t0 << setw(15) << y[0] << setw(15) << y[1]
         << setw(15) << v[0] << setw(15) << v[1] << endl;

    for (int i = 0; i < steps; i++) {
        eulerWithRefinement(A, y, v, t0, h);

        // Вывод результатов каждые 50 шагов
        if (i % 50 == 0) {
            cout << setw(10) << t0 << setw(15) << y[0] << setw(15) << y[1]
                 << setw(15) << v[0] << setw(15) << v[1] << endl;
        }
    }

    return 0;
}