// Actividad 01 Pacheco (Cap. 2)
// Primera version: i externo, j interno  -> acceso contiguo a A
// Segunda version: j externo, i interno  -> acceso con salto en A

#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <limits>

using namespace std;
using namespace std::chrono;

double loops1(int n, const vector<double>& A, const vector<double>& x, vector<double>& y) {
    // y = 0
    for (int i = 0; i < n; i++) y[i] = 0.0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            y[i] += A[i * n + j] * x[j];

    double s = 0.0;
    for (int i = 0; i < n; i++) s += y[i];
    return s;
}

double loops2(int n, const vector<double>& A, const vector<double>& x, vector<double>& y) {
    // y = 0
    for (int i = 0; i < n; i++) y[i] = 0.0;

    for (int j = 0; j < n; j++)
        for (int i = 0; i < n; i++)
            y[i] += A[i * n + j] * x[j];

    double s = 0.0;
    for (int i = 0; i < n; i++) s += y[i];
    return s;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        cerr << "Uso: " << argv[0] << " <n> <reps>\n";
        return 1;
    }
    int n = atoi(argv[1]);
    int reps = atoi(argv[2]);

    vector<double> A(n * n), x(n), y(n);
    srand(12345);
    for (int i = 0; i < n * n; i++) A[i] = (double)rand() / RAND_MAX;
    for (int i = 0; i < n; i++)     x[i] = (double)rand() / RAND_MAX;

    double best1 = numeric_limits<double>::max();
    double best2 = numeric_limits<double>::max();
    double c1 = 0.0, c2 = 0.0;

    for (int r = 0; r < reps; r++) {
        auto t0 = high_resolution_clock::now();
        c1 = loops1(n, A, x, y);
        auto t1 = high_resolution_clock::now();
        double dt = duration_cast<duration<double>>(t1 - t0).count();
        if (dt < best1) best1 = dt;
    }

    for (int r = 0; r < reps; r++) {
        auto t0 = high_resolution_clock::now();
        c2 = loops2(n, A, x, y);
        auto t1 = high_resolution_clock::now();
        double dt = duration_cast<duration<double>>(t1 - t0).count();
        if (dt < best2) best2 = dt;
    }

    cout << "n,version,tiempo_min_s,checksum\n";
    cout << n << ",primera," << best1 << "," << c1 << "\n";
    cout << n << ",segunda," << best2 << "," << c2 << "\n";
    return 0;
}