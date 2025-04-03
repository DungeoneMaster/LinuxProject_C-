#include <iostream>
#include <utility>
#include <vector>
#include <functional>
#include <cmath>
#include <iomanip>

using std::pair;
using std::vector;

class InterpolationFunction {
protected:
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

class SplineCube : protected InterpolationFunction{
private:

    vector<vector<double>> TableValue;

    vector<double> MethodPushDown(vector<double> d_up, vector<double> d_mid, vector<double> d_down, vector<double> d) {

        size_t s = d_mid.size();
        vector<double> x(s), a(s-1), b(s-1);

        a[0] = -d_up[0] / d_mid[0];
        b[0] = d[0] / d_mid[0];

        for(int i = 1; i < s-1; i++) {
            if(i == s - 1)
                continue;

            a[i] = -d_up[i] / (d_mid[i] + a[i-1]*d_down[i-1]);
            b[i] = (d[i] - d_down[i-1]*b[i-1])/(d_mid[i] + a[i-1]*d_down[i-1]);

        }

        x[s-1] = (d[s-1] - d_down[s-2]*b[s-2])/(d_mid[s-1] + a[s-2]*d_down[s-2]);

        for(int i = (int)(s-2); i >= 0; i--) {
            x[i] = b[i] + a[i]*x[i+1];
        }

        return x;
    }



public:

    SplineCube(int count_point, int a, int b, std::function<double(double)> func) :
    InterpolationFunction(count_point, a, b, std::move(func)), TableValue(4,vector<double>(count_point)) {
        for(int i = 0; i < count_point; i++) {
            TableValue[0][i] = table_points_[i].second;
        }
    }



    void re() {

        TableValue[2][0] = TableValue[2][count_point_ - 1] = TableValue[1][0] = TableValue[3][0] = 0;

        vector<double> a(count_point_ - 3), b(count_point_ - 2), c(count_point_ - 3), d(count_point_ - 2), x(count_point_ - 2);

        auto h = [this](int i){return table_points_[i].first - table_points_[i-1].first;};

        auto f = [this, &h](int i){return (table_points_[i+1].second - table_points_[i].second) / h(i+1);};

        for(int i = 1; i < count_point_ - 1; i++) {
            b[i - 1] = 2 * (h(i) + h(i + 1));

            d[i - 1] = 6*(f(i) - f(i - 1));
        }

        for(int i = 1; i < count_point_ - 2; i++) {
            a[i - 1] = h(i);

            b[i - 1] = h(i+1);
        }

        x = MethodPushDown(a,b,c,d);

        for(int i = 1; i < count_point_ - 1; i++)
            TableValue[2][i] = x[i - 1];

        for(int i = 1; i < count_point_; i++) {
            TableValue[3][i] = (x[i] - x[i - 1]) / h(i);

            TableValue[1][i] = (h(i) * x[i] / 2) - (h(i) * h(i) * TableValue[3][i] / 6) + f(i-1);

        }




    }
};


double func(double x) {
    return 1/(x * x + 25);
}


int main() {
    int a, b, count_point;
    std::cin >> count_point >> a >> b;

    //InterpolationFunction obj(count_point,a,b,func);
    //obj.CheckNewPoint(10);



    return 0;
}