#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <set>
#include <algorithm>

using namespace std;

/**
 * @brief Compute the valid range [left, right] for the next move.
 *
 * Given the current position (pivot), subarray size k, and array size n,
 * returns the minimum and maximum indices reachable in one reverse operation.
 *
 * @param n     The size of the array.
 * @param pivot The current position of the 1.
 * @param k     The size of the subarray to reverse.
 * @return      Pair of integers (left, right) representing the valid range.
 */
inline pair<int, int> getRange(int n, int pivot, int k) {
    int l1 = max(0, pivot - k + 1);
    int r1 = l1 + k - 1;

    int r2 = min(n - 1, pivot + k - 1);
    int l2 = r2 - k + 1;

    int left = r1 - (pivot - l1);
    int right = l2 + (r2 - pivot);
    return {left, right};
}

/**
 * @brief Compute the minimum number of reverse operations to move the 1.
 *
 * For each position in the array, determines the minimum number of reverse
 * operations needed to bring the single 1 to that position, or -1 if impossible.
 *
 * @param n      The size of the array.
 * @param p      The starting position of the 1.
 * @param banned Vector of banned positions where the 1 cannot be placed.
 * @param k      The size of the subarray to reverse in each operation.
 * @return       Vector of size n, where ans[i] is the minimum number of operations
 *               to reach position i, or -1 if impossible.
 */
vector<int> minReverseOperations2(int n, int p, vector<int>& banned, int k) {
    // Create a set of banned positions for quick lookup
    unordered_set<int> bans(banned.begin(), banned.end());
    // Initialize answer array with -1 (unreachable)
    vector<int> ans(n, -1);
    // Two sets to store available positions, split by parity (even/odd)
    set<int> s[2];

    // The starting position is always 0 operations
    ans[p] = 0;
    // Populate the sets with all non-banned, non-start positions
    for (int i = 0; i < n; i++)
        if (i != p && bans.find(i) == bans.end())
            s[i & 1].insert(i);

    // BFS queue
    queue<int> q;
    q.push(p);
    while (!q.empty()) {
        int pivot = q.front();
        q.pop();
        // Get the valid range for the next move
        auto range = getRange(n, pivot, k);
        // Determine which parity set to use based on k and pivot
        int o = (k % 2 == 0) ? ((1 - pivot) & 1) : (pivot & 1);

        // Iterate over all available positions in the valid range
        auto bg = s[o].lower_bound(range.first);
        auto ed = s[o].upper_bound(range.second);
        for (auto it = bg; it != ed; ++it) {
            ans[*it] = ans[pivot] + 1;
            q.push(*it);
        }
        // Remove visited positions from the set
        s[o].erase(bg, ed);
    }

    return ans;
}

#include <iostream>

int main() {
    int n = 4, p = 0, k = 4;
    std::vector<int> banned = {1, 2};
    std::vector<int> result = minReverseOperations2(n, p, banned, k);

    for (int x : result) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    return 0;
}