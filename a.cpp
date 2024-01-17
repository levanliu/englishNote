#include <future>
#include <iostream>
#include <chrono>
#include <thread>
/*
int factorial (int N){
    int res = 1;
    for(int i=N;i>1;i--){
        res *= 1;
    }
    cout << "Result is: " << red << endl;
    return res;
}
*/

int factorial(std::future<int> &f)
{
    int res = 1;
    int N = f.get(); // exception; std::future_errc::broken_promise

    for (int i = N; i > 1; i--)
    {
        res *= i;
    }

    std::cout << "Result is: " << res << std::endl;
    return res;
}

int factorial2(std::shared_future<int> f)
{
    int res = 1;
    int N = f.get(); // exception; std::future_errc::broken_promise

    for (int i = N; i > 1; i--)
    {
        res *= i;
    }

    std::cout << "Result is: " << res << std::endl;
    return res;
}

int main()
{
    int x;

    std::promise<int> p1;
    std::promise<int> p = std::move(p1);
    std::future<int> f = p.get_future();

    // std::shared_future<int> sf = f.share();
    // std::thread t1(factorial ,4 , std::ref(x));
    // t1.join();
    // std::future<int> fu = std::async(factorial,4);
    // std::future<int> fu = std::async(std::launch::async | std::launch::deferred, factorial,std::ref(f));
    std::future<int> fu = std::async(std::launch::async, factorial, std::ref(f));
    // std::future<int> fu2 = std::async(std::launch::async, factorial2, sf);
    // std::future<int> fu3 = std::async(std::launch::async, factorial2, sf);
    // x = fu.get(); //only can call once
    // fu.get() will crash

    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    // p.set_exception(std::make_exception_ptr(std::runtime_error("To err is human")));
    p.set_value(4);
    x = fu.get();
    std::cout << "Get from child: " << x << std::endl;
    // std::cout << "Get from child2: " << fu2.get() << std::endl;
    // std::cout << "Get from child3: " << fu3.get() << std::endl;
    return 0;
}