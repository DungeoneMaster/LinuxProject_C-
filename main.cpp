#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>

using namespace std;

// Компоненты электрического поля (константы)
const double Ex = 0.0;
const double Ey = 1.0;

// Функция вычисления производных
void derivatives(const vector<double>& r, const vector<double>& v,
                 vector<double>& drdt, vector<double>& dvdt) {
    // Пространственные производные
    drdt[0] = v[0];  // dx/dt = vx
    drdt[1] = v[1];  // dy/dt = vy

    // Производные скоростей (ускорения)
    dvdt[0] = Ex;  // dvx/dt = Ex
    dvdt[1] = Ey;  // dvy/dt = Ey
}

// Метод Эйлера с уточнением
void eulerWithRefinement(vector<double>& r, vector<double>& v, double& t, double h) {
    vector<double> drdt(2), dvdt(2);
    vector<double> r_temp(2), v_temp(2);
    vector<double> drdt_temp(2), dvdt_temp(2);

    // 1. Вычисляем производные в текущей точке
    derivatives(r, v, drdt, dvdt);

    // 2. Предварительный шаг Эйлера
    for (int i = 0; i < 2; i++) {
        r_temp[i] = r[i] + h * drdt[i];
        v_temp[i] = v[i] + h * dvdt[i];
    }

    // 3. Вычисляем производные в новой точке
    derivatives(r_temp, v_temp, drdt_temp, dvdt_temp);

    // 4. Уточнение решения
    for (int i = 0; i < 2; i++) {
        r[i] += h * 0.5 * (drdt[i] + drdt_temp[i]);
        v[i] += h * 0.5 * (dvdt[i] + dvdt_temp[i]);
    }

    t += h;
}

// Аналитическое решение
void analyticalSolution(double t, double x0, double y0,
                        double vx0, double vy0,
                        double& x, double& y,
                        double& vx, double& vy) {
    x = x0 + vx0*t + 0.5*Ex*t*t;
    y = y0 + vy0*t + 0.5*Ey*t*t;
    vx = vx0 + Ex*t;
    vy = vy0 + Ey*t;
}

int main() {
    // Параметры расчета
    double t0 = 0.0;
    double h = 0.01;
    int steps = 1000;

    // Начальные условия
    vector<double> r = {0.0, 0.0};  // положение (x, y)
    vector<double> v = {1.0, 0.0};  // скорость (vx, vy)

    // Для аналитического решения
    double x0 = r[0], y0 = r[1];
    double vx0 = v[0], vy0 = v[1];

    // Открываем файл для записи результатов
    ofstream outfile("particle_qm1.csv");
    outfile << "t,x_num,y_num,vx_num,vy_num,x_anal,y_anal,vx_anal,vy_anal\n";

    cout << "Расчет движения частицы с q/m = 1...\n";
    cout << "Электрическое поле E = (" << Ex << ", " << Ey << ")\n";
    cout << "Начальная скорость v0 = (" << vx0 << ", " << vy0 << ")\n\n";

    for (int i = 0; i <= steps; i++) {
        double t = t0 + i*h;

        // Численное решение (кроме первого шага)
        if (i > 0) {
            eulerWithRefinement(r, v, t0, h);
        }

        // Аналитическое решение
        double x_anal, y_anal, vx_anal, vy_anal;
        analyticalSolution(t, x0, y0, vx0, vy0,
                           x_anal, y_anal, vx_anal, vy_anal);

        // Запись в файл
        outfile << t << ","
                << r[0] << "," << r[1] << ","
                << v[0] << "," << v[1] << ","
                << x_anal << "," << y_anal << ","
                << vx_anal << "," << vy_anal << "\n";

        // Вывод в консоль
        if (i % 100 == 0) {
            cout << fixed << setprecision(4);
            cout << "t = " << setw(5) << t
                 << "  |x| = " << setw(8) << abs(r[0] - x_anal)
                 << "  |y| = " << setw(8) << abs(r[1] - y_anal)
                 << "  |vx| = " << setw(8) << abs(v[0] - vx_anal)
                 << "  |vy| = " << setw(8) << abs(v[1] - vy_anal)
                 << endl;
        }
    }

    outfile.close();
    cout << "\nРезультаты сохранены в particle_qm1.csv\n";

    return 0;
}