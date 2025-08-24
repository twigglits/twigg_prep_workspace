#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n = (argc > 1) ? stoull(argv[1]) : 1000000ULL;
    vector<int> v(n);
    iota(v.begin(), v.end(), 0);

    // Number of searches is a constant factor; complexity wrt n is O(log n).
    const size_t Q = 200000;
    mt19937 rng(123);
    uniform_int_distribution<int> dist(-int(n), int(n * 2));

    size_t found = 0;
    auto t0 = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < Q; ++i) {
        int x = dist(rng);
        found += binary_search(v.begin(), v.end(), x);
    }
    auto t1 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> ms = t1 - t0;

    cout << "O(log n) binary search: n=" << n << ", queries=" << Q
         << ", elapsed=" << ms.count() << " ms, found=" << found << "\n";
    return 0;
}
