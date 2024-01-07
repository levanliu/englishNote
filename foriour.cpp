#include <iostream>
#include <complex>
#include <cmath>
#include <vector>

using namespace std;

typedef complex<double> cd;

// FFT函数
void fft(vector<cd>& x) {
    int N = x.size();
    if (N <= 1) {
        return;
    }
    vector<cd> even, odd;
    for (int i = 0; i < N; i += 2) {
        even.push_back(x[i]);
        odd.push_back(x[i + 1]);
    }
    fft(even);
    fft(odd);
    for (int k = 0; k < N / 2; ++k) {
        cd t = polar(1.0, -2 * M_PI * k / N) * odd[k];
        x[k] = even[k] + t;
        x[k + N / 2] = even[k] - t;
    }
}

// IFFT函数
void ifft(vector<cd>& x) {
    int N = x.size();
    for (int i = 0; i < N; ++i) {
        x[i] = conj(x[i]);
    }
    fft(x);
    for (int i = 0; i < N; ++i) {
        x[i] = conj(x[i]) / N;
    }
}

// 示例使用
int main() {
    vector<cd> x = {1, 2, 3, 4};
    int N = x.size();
    
    // 傅里叶变换
    fft(x);
    
    cout << "傅里叶变换结果：" << endl;
    for (int i = 0; i < N; ++i) {
        cout << x[i] << " ";
    }
    cout << endl;
    
    // 逆傅里叶变换
    ifft(x);
    
    cout << "逆傅里叶变换结果：" << endl;
    for (int i = 0; i < N; ++i) {
        cout << x[i].real() << " ";
    }
    cout << endl;
    
    return 0;
}
