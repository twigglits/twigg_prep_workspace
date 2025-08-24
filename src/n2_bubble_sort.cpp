#include <bits/stdc++.h>
using namespace std;

static void bubble_sort(vector<int>& a) {
    size_t n = a.size();
    for (size_t i = 0; i + 1 < n; ++i) {
        bool swapped = false;
        for (size_t j = 0; j + 1 < n - i; ++j) {
            if (a[j] > a[j+1]) { swap(a[j], a[j+1]); swapped = true; }
        }
        if (!swapped) break;
    }
}

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n = (argc > 1) ? stoull(argv[1]) : 2000ULL; // keep small

    vector<int> v(n);
    mt19937 rng(123);
    uniform_int_distribution<int> dist(0, INT_MAX);
    for (auto &x : v) x = dist(rng);

    auto t0 = chrono::high_resolution_clock::now();
    bubble_sort(v); // O(n^2)
    auto t1 = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> ms = t1 - t0;
    cout << "O(n^2) bubble sort: n=" << n << ", elapsed=" << ms.count() << " ms\n";
    return 0;
}
