#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <iomanip>

using std::cin;
using std::cout;
using std::pair;
using std::vector;


class InterpolationFunction {
private:
    int count_point_;

    vector<double> table_points_;

    std::function<double(double)> func_;
public:

    InterpolationFunction(int count_point, double a, double b, std::function<double(double)> func) : count_point_(count_point),table_points_(count_point) {

        double length = (b - a)/(count_point-1);
        func_ = func;
        for(int i = 0; i < count_point; i++) {
            double tmp = a + length * i;
            table_points_[i] = tmp;
        }
    }

    double MethodLagrange(double x) {
        double sum = 0;
        for(int i = 0; i < count_point_; i++) {
            double c_up = 1, c_down = 1;

            for(int j = 0; j < count_point_; j++) {
                if(j == i)
                    continue;
                c_up *= x - table_points_[j];
                c_down *= table_points_[i] - table_points_[j];
            }
            sum += func_(table_points_[i]) * c_up / c_down;
        }
        return sum;
    }

    double GetErrorInterpolation(double x) {
        return abs(func_(x) - MethodLagrange(x));
    }

    void Print() {
        for(int i = 0; i < count_point_; i++) {
            double x = table_points_[i];
            cout << x << " | " << func_(x) << " ... " << MethodLagrange(x) << " error: " << GetErrorInterpolation(x) << "\n";

        }
    }

};

double func(double x) {
    return 1/(x * x + 25);
}


int main() {
    int a, b, count_point;
    cin >> count_point >> a >> b;

    InterpolationFunction obj(count_point,a,b,func);
    obj.Print();

    return 0;
}