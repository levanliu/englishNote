#include <iostream>
#include <cmath>
#include <fstream>

const double PI = 3.14159265358979323846;

int main() {
    double dx = 0.001;
    double L = PI;
    int n = static_cast<int>(2*L/dx) + 1;
    int nquart = static_cast<int>(std::floor(n/4));

    // Define hat function
    double* f = new double[n];
    for (int i = nquart; i < 2*nquart; i++) {
        f[i] = (4.0/n)*(i-nquart+1);
    }
    for (int i = 2*nquart; i < 3*nquart; i++) {
        f[i] = 1.0 - (4.0/n)*(i-2*nquart);
    }

    std::ofstream outFile;
    outFile.open("plot_data.txt");
    for (int i = 0; i < n; i++) {
        outFile << i*dx - L << " " << f[i] << std::endl;
    }
    outFile.close();

    // Compute Fourier series
    double* A = new double[20];
    double* B = new double[20];
    double A0 = 0;
    for (int i = 0; i < n; i++) {
        A0 += f[i] * dx;
    }
    A0 /= 2;

    double* fFS = new double[n];
    for (int k = 0; k < 20; k++) {
        A[k] = 0;
        B[k] = 0;
        for (int i = 0; i < n; i++) {
            A[k] += f[i] * std::cos((k+1)*PI*(i*dx)/L) * dx;
            B[k] += f[i] * std::sin((k+1)*PI*(i*dx)/L) * dx;
            fFS[i] += A[k]*std::cos((k+1)*PI*(i*dx)/L) + B[k]*std::sin((k+1)*PI*(i*dx)/L);
        }
    }

    outFile.open("fourier_data.txt");
    for (int i = 0; i < n; i++) {
        outFile << i*dx - L << " " << fFS[i] << std::endl;
    }
    outFile.close();

    delete[] f;
    delete[] A;
    delete[] B;
    delete[] fFS;

    return 0;
}
