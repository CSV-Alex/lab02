// Actividad 03: Multiplicacion de matrices por bloques (6 bucles anidados)
// C = A * B usando bloques de tamano BS

#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <limits>
#include <algorithm>

using namespace std;
using namespace std::chrono;

void matmul_blocked(int n, int BS, const vector<double>& A, const vector<double>& B, vector<double>& C) {
    // C = 0
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i * n + j] = 0.0;

    for (int ii = 0; ii < n; ii += BS) {
        for (int jj = 0; jj < n; jj += BS) {
            for (int kk = 0; kk < n; kk += BS) {

                int i_max = min(ii + BS, n);
                int j_max = min(jj + BS, n);
                int k_max = min(kk + BS, n);

                for (int i = ii; i < i_max; i++) {
                    for (int j = jj; j < j_max; j++) {
                        double sum = 0.0;
                        for (int k = kk; k < k_max; k++) {
                            sum += A[i * n + k] * B[k * n + j];
                        }
                        C[i * n + j] += sum;
                    }
                }
            }
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 4) {
        cerr << "Uso: " << argv[0] << " <n> <BS> <reps>\n";
        return 1;
    }
    int n = atoi(argv[1]);
    int BS = atoi(argv[2]);
    int reps = atoi(argv[3]);

    vector<double> A(n * n), B(n * n), C(n * n);
    srand(12345);
    for (int i = 0; i < n * n; i++) A[i] = (double)rand() / RAND_MAX;
    for (int i = 0; i < n * n; i++) B[i] = (double)rand() / RAND_MAX;

    double best = numeric_limits<double>::max();

    for (int r = 0; r < reps; r++) {
        auto t0 = high_resolution_clock::now();
        matmul_blocked(n, BS, A, B, C);
        auto t1 = high_resolution_clock::now();
        double dt = duration_cast<duration<double>>(t1 - t0).count();
        if (dt < best) best = dt;
    }

    double checksum = 0.0;
    for (int i = 0; i < n; i++) checksum += C[i * n + i];

    cout << "n,BS,algoritmo,tiempo_min_s,checksum\n";
    cout << n << "," << BS << ",bloques," << best << "," << checksum << "\n";
    return 0;
}