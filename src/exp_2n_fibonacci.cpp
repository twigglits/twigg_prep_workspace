#include <bits/stdc++.h>
using namespace std;

long long fib(int n) {
    if (n <= 1) return n;
    return fib(n-1) + fib(n-2); // O(2^n)
}

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = (argc > 1) ? stoi(argv[1]) : 30; // adjust as needed

    auto t0 = chrono::high_resolution_clock::now();
    long long f = fib(n);
    auto t1 = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> ms = t1 - t0;
    cout << "O(2^n) naive fibonacci: n=" << n << ", fib(n)=" << f
         << ", elapsed=" << ms.count() << " ms\n";
    return 0;
}
