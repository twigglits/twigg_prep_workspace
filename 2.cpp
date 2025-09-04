#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    int degree;
};

void solve(int n, vector<Node> nodes) {
    vector<int> degrees(n);
    for (int i = 0; i < n; ++i) {
        degrees[i] = nodes[i].degree;
    }

    int sum = 0;
    for (int d : degrees) {
        sum += d;
    }

    if (sum != 2 * n) {
        cout << "No" << endl;
        return;
    }

    int max_deg = *max_element(degrees.begin(), degrees.end());
    if (max_deg < 2 || max_deg > n) {
        cout << "No" << endl;
        return;
    }

    int cycle_len = 0;
    for (int d : degrees) {
        if (d == 2) ++cycle_len;
    }

    if (cycle_len != n) {
        cout << "No" << endl;
        return;
    }

    cout << "Yes" << endl;
    for (int i = 0; i < n; ++i) {
        cout << (i + 1) << " " << ((i + 1) % n + 1) << endl;
    }
}

int main() {
    int n = 12;
    vector<Node> nodes(n);
    for (int i = 0; i < n; ++i) {
        cin >> nodes[i].degree;
    }
    solve(n, nodes);
    return 0;
}