#include <iostream>
#include <chrono>
#include <ctime>
using namespace std;

long fibonacci(int n)
{
    if (n < 3) return 1;
    return fibonacci(n-1) + fibonacci(n-2);
}

int main() {

    chrono::time_point<chrono::system_clock> start, end;

    //store the current time (now()) in start, execute
    //Fibonacci function, then store current time in end
    start = chrono::system_clock::now();
    cout << "f(42) = " << fibonacci(42) << '\n';
    end = chrono::system_clock::now();

    //subtract end from beginning to get number of seconds elapsed
    chrono::duration<double> elapsed_seconds = end-start;
    time_t end_time = chrono::system_clock::to_time_t(end);

    //output the duration.
    cout << "finished computation at " << ctime(&end_time) << "elapsed time: " << elapsed_seconds.count() << "s\n";

}
