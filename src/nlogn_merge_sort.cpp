#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n = (argc > 1) ? stoull(argv[1]) : 2000000ULL;

    vector<int> v(n);
    mt19937 rng(123);
    uniform_int_distribution<int> dist(0, INT_MAX);
    for (auto &x : v) x = dist(rng);

    auto t0 = chrono::high_resolution_clock::now();
    sort(v.begin(), v.end()); // O(n log n)
    auto t1 = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> ms = t1 - t0;
    cout << "O(n log n) sort: n=" << n << ", elapsed=" << ms.count() << " ms\n";
    return 0;
}
