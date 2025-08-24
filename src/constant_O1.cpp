#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // n only controls the size of the vector we create, not the work repeated.
    size_t n = (argc > 1) ? stoull(argv[1]) : 1000000ULL;
    vector<int> v(n);
    iota(v.begin(), v.end(), 0);

    const uint64_t ITER = 5000000ULL; // constant repetitions to get measurable time

    volatile int sink = 0; // prevent optimization
    auto t0 = chrono::high_resolution_clock::now();
    for (uint64_t i = 0; i < ITER; ++i) {
        sink ^= v.back(); // O(1) access, independent of n
    }
    auto t1 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> ms = t1 - t0;

    cout << "O(1) constant-time access (" << ITER << " repetitions), n=" << n
         << ", elapsed=" << ms.count() << " ms\n";
    // Use sink so compiler keeps the loop
    cerr << "(ignore) checksum=" << sink << "\n";
    return 0;
}
