#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// Функция для ОДУ 1-го порядка: y' = f(x, y)
double f(double x, double y) {
    return x * y; // Пример: y' = x*y
}

// Функции для системы ОДУ 2-го порядка: y'' = f(x, y, y')
double f1(double x, double y, double z) {
    return z; // y' = z
}

double f2(double x, double y, double z) {
    return -y; // z' = -y (пример: y'' + y = 0)
}

// Метод Эйлера с уточнением для ОДУ 1-го порядка
void euler_refined_1st_order(double (*f)(double, double), double x0, double y0, double h, int steps) {
    double x = x0, y = y0;
    cout << "Метод Эйлера с уточнением (1-го порядка):" << endl;
    cout << "x\t\ty" << endl;
    cout << fixed << setprecision(6);
    cout << x << "\t\t" << y << endl;

    for (int i = 0; i < steps; ++i) {
        double y_pred = y + h * f(x, y);
        double y_corr = y + (h / 2) * (f(x, y) + f(x + h, y_pred));

        x += h;
        y = y_corr;

        cout << x << "\t\t" << y << endl;
    }
}

// Метод Эйлера с уточнением для системы ОДУ 2-го порядка
void euler_refined_2nd_order(
        double (*f1)(double, double, double),
        double (*f2)(double, double, double),
        double x0, double y0, double z0, double h, int steps
) {
    double x = x0, y = y0, z = z0;
    cout << "Метод Эйлера с уточнением (2-го порядка):" << endl;
    cout << "x\t\ty\t\tz" << endl;
    cout << fixed << setprecision(6);
    cout << x << "\t\t" << y << "\t\t" << z << endl;

    for (int i = 0; i < steps; ++i) {
        // Предсказание
        double y_pred = y + h * f1(x, y, z);
        double z_pred = z + h * f2(x, y, z);

        // Коррекция
        double y_corr = y + (h / 2) * (f1(x, y, z) + f1(x + h, y_pred, z_pred));
        double z_corr = z + (h / 2) * (f2(x, y, z) + f2(x + h, y_pred, z_pred));

        x += h;
        y = y_corr;
        z = z_corr;

        cout << x << "\t\t" << y << "\t\t" << z << endl;
    }
}

int main() {
    double x0 = 0.0, y0 = 1.0, z0 = 0.0; // Начальные условия
    double h = 0.1; // Шаг
    int steps = 10; // Количество шагов

    // Решение ОДУ 1-го порядка
    euler_refined_1st_order(f, x0, y0, h, steps);

    // Решение системы ОДУ 2-го порядка (пример: y'' + y = 0)
    euler_refined_2nd_order(f1, f2, x0, y0, z0, h, steps);

    return 0;
}