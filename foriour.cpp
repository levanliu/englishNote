#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <iomanip>

const double eps = 1e-6;
const double pi = acos(-1.0);

void FFT(std::vector<std::complex<double>>& a, int n, int inv) {
    if (n == 1)
        return;

    int mid = n / 2;
    std::vector<std::complex<double>> A1(mid), A2(mid);

    for (int i = 0; i < n; i += 2) {
        A1[i / 2] = a[i];
        A2[i / 2] = a[i + 1];
    }

    FFT(A1, mid, inv);
    FFT(A2, mid, inv);

    std::complex<double> w0(1, 0), wn(std::cos(2 * pi / n), inv * std::sin(2 * pi / n));

    for (int i = 0; i < mid; ++i, w0 *= wn) {
        a[i] = A1[i] + w0 * A2[i];
        a[i + n / 2] = A1[i] - w0 * A2[i];
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::complex<double>> a(n), b(m);

    for (int i = 0; i < n; ++i) {
        double x;
        std::cin >> x;
        a[i].real(x);
    }

    for (int i = 0; i < m; ++i) {
        double x;
        std::cin >> x;
        b[i].real(x);
    }

    int len = 1 << (int)std::ceil(std::log2(n + m));
    a.resize(len);
    b.resize(len);

    FFT(a, len, 1);
    FFT(b, len, 1);

    for (int i = 0; i < len; ++i)
        a[i] = a[i] * b[i];

    FFT(a, len, -1);

    for (int i = 0; i < n + m - 1; ++i)
        std::cout << std::fixed << std::setprecision(0) << a[i].real() / len + eps << " ";

    return 0;
}



/**
4 4
5 3 2 1
1 2 3 5
*/