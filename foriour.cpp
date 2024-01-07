#include <iostream>
#include <complex>
#include <cmath>
#include <vector>

using namespace std;

#define M_PI 3.14159265358979323846 // pi
typedef std::complex<double> Complex;

// 计算复数的幂函数
Complex power(Complex base, int exponent)
{
    Complex result = 1.0;
    for (int i = 0; i < exponent; i++)
    {
        result *= base;
    }
    return result;
}

// 快速傅里叶变换
void fft(std::vector<Complex> &data, bool inverse = false)
{
    int n = data.size();
    if (n <= 1)
    {
        return;
    }

    std::vector<Complex> even(n / 2);
    std::vector<Complex> odd(n / 2);
    for (int i = 0; i < n / 2; i++)
    {
        even[i] = data[2 * i];
        odd[i] = data[2 * i + 1];
    }

    fft(even, inverse);
    fft(odd, inverse);

    for (int k = 0; k < n / 2; ++k)
    {
        double angle = (inverse ? -2.0 : 2.0) * M_PI / n;
        Complex t = std::polar(1.0, angle * k) * odd[k];
        data[k] = even[k] + t;
        data[k + n / 2] = even[k] - t;
    }

    if (inverse)
    {
        for (int i = 0; i < n; i++)
        {
            data[i] /= n;
        }
    }
}

// 逆快速傅里叶变换
void ifft(std::vector<Complex> &data)
{
    fft(data, true);
}

int main()
{
    vector<Complex> x = {5,3,2,1};
    int N = x.size();

    // 傅里叶变换
    fft(x);

    cout << "傅里叶变换结果：" << endl;
    for (int i = 0; i < N; ++i)
    {
        cout << x[i] << " ";
    }
    cout << endl;

    // 逆傅里叶变换
    ifft(x);

    cout << "逆傅里叶变换结果：" << endl;
    for (int i = 0; i < N; ++i)
    {
        cout << x[i].real() << " ";
    }
    cout << endl;

    return 0;
}
