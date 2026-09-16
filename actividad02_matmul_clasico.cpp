// Actividad 02: Multiplicacion clasica de matrices C = A * B
// Tres bucles anidados: i, j, k

#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <limits>

using namespace std;
using namespace std::chrono;

void matmul(int n,
            const vector<double>& A,
            const vector<double>& B,
            vector<double>& C) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double sum = 0.0;
            for (int k = 0; k < n; k++) {
                sum += A[i * n + k] * B[k * n + j];
            }
            C[i * n + j] = sum;
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 3) {
        cerr << "Uso: " << argv[0] << " <n> <reps>\n";
        return 1;
    }
    int n    = atoi(argv[1]);
    int reps = atoi(argv[2]);

    vector<double> A(n * n), B(n * n), C(n * n);
    srand(12345);
    for (int i = 0; i < n * n; i++) A[i] = (double)rand() / RAND_MAX;
    for (int i = 0; i < n * n; i++) B[i] = (double)rand() / RAND_MAX;

    double best = numeric_limits<double>::max();

    for (int r = 0; r < reps; r++) {
        auto t0 = high_resolution_clock::now();
        matmul(n, A, B, C);
        auto t1 = high_resolution_clock::now();
        double dt = duration_cast<duration<double>>(t1 - t0).count();
        if (dt < best) best = dt;
    }

    double checksum = 0.0;
    for (int i = 0; i < n; i++) checksum += C[i * n + i];

    cout << "n,algoritmo,tiempo_min_s,checksum\n";
    cout << n << ",clasica," << best << "," << checksum << "\n";
    return 0;
}