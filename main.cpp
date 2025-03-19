#include <iostream>
#include <utility>
#include <vector>
#include <functional>
#include <cmath>
#include <iomanip>

using std::vector;

class InterpolationFunction {
private:
    int count_point_;

    double a_, b_;

    vector<double> table_points_;

    std::function<double(double)> func_;
public:

    InterpolationFunction(int count_point, double a, double b, std::function<double(double)> func) :
        count_point_(count_point), table_points_(count_point), a_(a), b_(b) {

        double length = (b - a)/(count_point - 1);
        func_ = std::move(func);

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
        return std::abs(func_(x) - MethodLagrange(x));
    }

    void CheckNewPoint(int new_count_point) {
        vector<double> checked_table_points_(new_count_point);

        double length = (b_ - a_) / (new_count_point - 1);

        for (int i = 0; i < new_count_point; i++) {
            double tmp = a_ + length * i;
            checked_table_points_[i] = tmp;
        }

        std::cout << std::left << std::setw(3) << "i"
                  << "| "<< std::setw(20) << "x_i"
                  << "| "<< std::setw(20) << "f(x_i)"
                  << "| "<< std::setw(20) << "Lagrange"
                  << "| "<< std::setw(20) << "Error" << std::endl;

        std::cout << std::setfill('-') << std::setw(83) << "" << std::setfill(' ') << std::endl;

        double max = 0;
        for (int i = 0; i < new_count_point; i++) {
            double x = checked_table_points_[i],tmp = GetErrorInterpolation(x);

            if(max < tmp)
                max = tmp;

            std::cout << std::fixed << std::setprecision(10) << std::left << std::setw(3) << i
                      << "| " << std::setw(20) << x
                      << "| " << std::setw(20) << func_(x)
                      << "| " << std::setw(20) << MethodLagrange(x)
                      << "| " << std::setw(20) << tmp << std::endl;
        }
        std::cout << "MaxError: " <<max;
    }
};

double func(double x) {
    return 1/(x * x + 25);
}


int main() {
    int a, b, count_point;
    std::cin >> count_point >> a >> b;

    InterpolationFunction obj(count_point,a,b,func);
    obj.CheckNewPoint(10);

    return 0;
}