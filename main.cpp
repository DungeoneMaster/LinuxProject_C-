#include <iostream>
#include <utility>
#include <vector>
#include <functional>
#include <cmath>
#include <iomanip>

using std::pair;
using std::vector;

class InterpolationFunction {
private:
    int count_point_;

    double a_, b_;

    vector<pair<double,double>> table_points_;

    std::function<double(double)> func_;

    void GetTablePoints(vector<pair<double,double>>& table) {
        size_t n = table.size();
        double length = (b_ - a_)/(int)(n - 1);

        for(int i = 0; i < n; i++) {
            double tmp = a_ + length * i;
            table[i].first = tmp;
            table[i].second = func_(tmp);
        }
    }
public:

    InterpolationFunction(int count_point, double a, double b, std::function<double(double)> func) :
        count_point_(count_point), table_points_(count_point), a_(a), b_(b) {
        func_ = std::move(func);

        GetTablePoints(table_points_);
    }



    double MethodLagrange(double x) {
        double sum = 0;
        for(int i = 0; i < count_point_; i++) {
            double c_up = 1, c_down = 1;

            for(int j = 0; j < count_point_; j++) {
                if(j == i)
                    continue;
                c_up *= x - table_points_[j].first;
                c_down *= table_points_[i].first - table_points_[j].first;
            }
            sum += table_points_[i].second * c_up / c_down;
        }
        return sum;
    }

    double GetErrorInterpolation(double x) {
        return std::abs(func_(x) - MethodLagrange(x));
    }

    void CheckNewPoint(int new_count_point) {
        vector<pair<double, double>> checked_table_points_(new_count_point);
        int size = 20;

        GetTablePoints(checked_table_points_);

        std::cout << std::left << std::setw(3) << "i"
                  << "| "<< std::setw(size) << "x_i"
                  << "| "<< std::setw(size) << "f(x_i)"
                  << "| "<< std::setw(size) << "Lagrange"
                  << "| "<< std::setw(size) << "Error" << std::endl;

        std::cout << std::setfill('-') << std::setw(size*4) << "" << std::setfill(' ') << std::endl;

        double max = 0;
        for (int i = 0; i < new_count_point; i++) {
            double x = checked_table_points_[i].first, y = checked_table_points_[i].second;
            double lagrange = MethodLagrange(x), error = std::abs(y - lagrange);
            if(max < error)
                max = error;

            std::cout << std::fixed << std::setprecision(10) << std::left << std::setw(3) << i
                      << "| " << std::setw(size) << x
                      << "| " << std::setw(size) << y
                      << "| " << std::setw(size) << lagrange
                      << "| " << std::setw(size) << error << std::endl;
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