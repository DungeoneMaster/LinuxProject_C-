
#include "iostream"
#include "vector"
#include "functional"

using std::cin;
using std::cout;
using std::pair;
using std::vector;


class InterpolationFunction {
private:
    int count_point_;

    vector<pair<double,double>> table_points_;

public:

    InterpolationFunction(int count_point, double a, double b, std::function<double(double)> func) : count_point_(count_point),table_points_(count_point) {

        double length = (b - a)/(count_point-1);

        for(int i = 0; i < count_point; i++) {
            double tmp = b + length * i;
            table_points_[i].first = tmp;
            table_points_[i].second = func(tmp);
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


    return 0;
}