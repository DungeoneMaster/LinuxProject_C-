#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

void Euler(double x0, double y0, double Vx0, double Vy0, double h, vector<double>& Netx, vector<double>& Nety) {
    double x = x0;
    double y = y0;
    double Vx = Vx0;
    double Vy = Vy0;
    do {
        x0 = x;
        y0 = y;
        Vx0 = Vx;
        Vy0 = Vy;

        x = x0 + (h * Vx0);
        y = y0 + (h * Vy0);

        Netx.push_back(x);
        Nety.push_back(y);

        Vx = Vx0 + (h  * x0);
        Vy = Vy0 + (h * y0);


    } while ((x < 1) && (y < 1));

}

int main() {
    double x0 = 0.01 * 7;
    double y0 = 1;
    double Vx0 = 0.01 * 7;
    double Vy0 = -1;
    double Ca = 0.01 * 7;
    double h = 0.1;
    double H = h / 2;

    int k = 0;

    vector<double> Net1x,Net1y,Net2x,Net2y,resx,resy;
    Net1x.push_back(x0);

    Net1y.push_back(y0);
    Net2x.push_back(x0);
    Net2y.push_back(y0);

    Euler(x0, y0, Vx0, Vy0, h, Net1x, Net1y);
    Euler(x0, y0, Vx0, Vy0, H, Net2x, Net2y);


    for (int i = 0; i < Net1x.size()-1; ++i) {
        resx.push_back(2 * Net1x[i] - Net2x[i+k]);
        resy.push_back(2 * Net1y[i] - Net2y[i+k]);
        ++k;
    }
    for (int i = 0; i < resx.size(); ++i)
        cout << fabs(resx[i] * resy[i] - Ca) << "\n";


}