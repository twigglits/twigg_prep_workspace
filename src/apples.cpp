#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;
using ll = long long;

vector<int> solve(int n, int m, vector<vector<int>> apples) {
    // vector last(m + 1, -1);
    unordered_map<int, int> last;
    auto get_last = [&](int i) {
        if (!last.count(i)) {
            return -1;
        } else {
            return last[i];
        }
    };

    vector can_zero(n + 1, false);
    vector prev(n + 1, 0);
    can_zero[0] = true;
    int oops = -1;

    for (int i = 0; i < n; ++i) {
        if (apples[i].empty()) {
            can_zero[i + 1] = true;
            last[0] = i;
        } else {
            int nearest_pair = get_last(0);
            int new_oops = oops;
            for (int x : apples[i]) {
                nearest_pair = max(nearest_pair, get_last(x));
                new_oops = max(new_oops, get_last(x));
                last[x] = i;
            }
            if (nearest_pair != -1) {
                int nearest_zero = prev[nearest_pair];
                if (oops < nearest_zero) {
                    can_zero[i + 1] = true;
                }
            }
            oops = new_oops;
        }
        if (can_zero[i + 1]) {
            prev[i + 1] = i + 1;
        } else {
            prev[i + 1] = prev[i];
        }
    }

    // vector used(m + 1, false);
    unordered_set<int> used;
    vector max_cnt(n + 1, 0);
    int current_cnt = 0;

    for (int i = n - 1; i >= 0; --i) {
        bool fail = false;
        if (apples[i].empty()) {
            used.insert(0);
        }
        for (int x : apples[i]) {
            if (used.count(x)) {
                fail = true;
                break;
            }
            used.insert(x);
            ++current_cnt;
        }
        if (fail) {
            break;
        }
        if (used.count(0)) {
            max_cnt[i] = m;
        } else {
            max_cnt[i] = current_cnt;
        }
    }

    int ans = 0;
    for (int i = 0; i <= n; ++i) {
        if (can_zero[i]) {
            ans = max(ans, max_cnt[i]);
        }
    }
    return {ans};
}