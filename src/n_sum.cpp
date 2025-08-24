#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n = (argc > 1) ? stoull(argv[1]) : 10000000ULL;

    vector<int> v(n);
    iota(v.begin(), v.end(), 1);

    long long sum = 0;
    auto t0 = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < n; ++i) sum += v[i]; // O(n)
    auto t1 = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> ms = t1 - t0;
    cout << "O(n) sum: n=" << n << ", sum=" << sum << ", elapsed=" << ms.count() << " ms\n";
    return 0;
}
