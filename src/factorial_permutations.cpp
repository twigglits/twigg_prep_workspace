#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = (argc > 1) ? stoi(argv[1]) : 9; // keep small; 9! = 362,880
    vector<int> a(n);
    iota(a.begin(), a.end(), 1);

    long long count = 0;
    auto t0 = chrono::high_resolution_clock::now();
    do {
        // visiting one permutation — O(1) work per permutation
        ++count;
    } while (next_permutation(a.begin(), a.end())); // O(n!) permutations
    auto t1 = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> ms = t1 - t0;
    cout << "O(n!) permutations visited: n=" << n << ", count=" << count
         << ", elapsed=" << ms.count() << " ms\n";
    return 0;
}
