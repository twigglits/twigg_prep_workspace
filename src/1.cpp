#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> minReverseOperations(int n, int p, vector<int>& banned, int k) {
    vector<int> answer(n, -1);
    unordered_set<int> bannedSet(banned.begin(), banned.end());
    queue<int> q;
    q.push(p);
    answer[p] = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        // Try to reverse subarray ending at current + k - 1
        for (int i = max(0, current - k + 1); i <= min(n - k, current); ++i) {
            int newPos = i + k - 1 - (current - i);
            if (bannedSet.find(newPos) == bannedSet.end() && answer[newPos] == -1) {
                answer[newPos] = answer[current] + 1;
                q.push(newPos);
            }
        }
    }

    return answer;
}


int main() {
    int n = 4, p = 0, k = 4;
    std::vector<int> banned = {1, 2};
    std::vector<int> result = minReverseOperations(n, p, banned, k);

    for (int x : result) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    return 0;
}