#include <vector>
#include <algorithm>
#include <tuple>
#include <cmath>
#include <iostream>
#include <utility>

using namespace std;

using tp = tuple<int,int,int>;
const int MOD = 998244353;
const int sgn[] = {1, MOD - 1};

vector<int> solve(int m, int q, const vector<pair<int,int>>& segments, const vector<pair<int,int>>& queries) {
    vector<int> results;
    vector<tp> V;
    vector<bool> del(m + 2, false);
    vector<vector<int>> fa(18, vector<int>(m + 2));
    vector<int> x(m + 2), y(m + 2);

    // Process segments
    for (int i = 1; i <= m; ++i) {
        x[i] = segments[i-1].first;
        y[i] = segments[i-1].second;
        V.emplace_back(y[i], -x[i], i);
    }
    
    sort(V.begin(), V.end());
    int mxl = 0;
    for (auto [y_val, x_val, i] : V) {
        if (-x_val <= mxl) del[i] = true;
        mxl = max(mxl, -x_val);
    }
    
    V.clear();
    x[m + 1] = y[m + 1] = 1000000001;
    for (int i = 1; i <= m + 1; ++i) {
        if (!del[i]) V.emplace_back(x[i], y[i], i);
    }
    
    sort(V.begin(), V.end());
    for (auto [x_val, y_val, id] : V) {
        auto it = lower_bound(V.begin(), V.end(), tp{y_val + 1, 0, 0});
        int t = (it != V.end()) ? get<2>(*it) : m + 1;
        fa[0][id] = t;
    }
    
    fa[0][m + 1] = m + 1;
    for (int k = 1; k <= 17; ++k) {
        for (int i = 1; i <= m + 1; ++i) {
            fa[k][i] = fa[k - 1][fa[k - 1][i]];
        }
    }
    
    // Process queries
    for (auto [l, r] : queries) {
        auto it = lower_bound(V.begin(), V.end(), tp{l, 0, 0});
        if (it == V.end()) {
            results.push_back(0);
            continue;
        }
        
        int u = get<2>(*it);
        if (x[u] != l || y[u] > r) {
            results.push_back(0);
            continue;
        }
        
        if (y[u] == r) {
            results.push_back(sgn[1]);
            continue;
        }
        
        if (it + 1 == V.end()) {
            results.push_back(0);
            continue;
        }
        
        int v = get<2>(*(it + 1));
        if (y[v] > r || x[v] > y[u]) {
            results.push_back(0);
            continue;
        }
        
        int numu = 0, numv = 0;
        int u_copy = u, v_copy = v;
        
        for (int i = 17; i >= 0; --i) {
            if (y[fa[i][u_copy]] <= r) {
                u_copy = fa[i][u_copy];
                numu += (i == 0);
            }
        }
        
        for (int i = 17; i >= 0; --i) {
            if (y[fa[i][v_copy]] <= r) {
                v_copy = fa[i][v_copy];
                numv += (i == 0);
            }
        }
        
        if (u_copy == v_copy || (y[u_copy] != r && y[v_copy] != r)) {
            results.push_back(0);
        } else {
            results.push_back(sgn[numu ^ numv]);
        }
    }
    
    return results;
}

#ifdef BUILD_SEGMENT_EXAMPLE
int main() {
    // Example from segment.md
    int m = 4;
    int q = 2;
    vector<pair<int,int>> segments = {{1,3}, {4,6}, {2,4}, {3,5}};
    vector<pair<int,int>> queries = {{1,4}, {1,5}};

    vector<int> ans = solve(m, q, segments, queries);

    for (size_t i = 0; i < ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << "\n";
    return 0;
}
#endif