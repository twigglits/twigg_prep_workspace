Language: cpp

Difficulty: Hard

Task Category: code_explanation

Problem Statement: Problem: Segement Covering

ChthollyNotaSeniorious gives DataStructures a number axis with m distinct segments on it. Let f(l,r) be the number of ways to choose an even number of segments such that the union of them is exactly [l,r], and g(l,r) be the number of ways to choose an odd number of segments such that the union of them is exactly [l,r].

Description: Given m distinct segments on a number axis, define:

f(l,r) = number of ways to choose an even number of segments whose union is exactly [l,r]
g(l,r) = number of ways to choose an odd number of segments whose union is exactly [l,r]
For q queries, each providing [l,r], compute (f(l,r) - g(l,r)) mod 998244353.

Function Signature: vector solve(int m, int q, vector>& segments, vector>& queries);

Input Format: The function receives:

m: number of segments (1 ≤ m ≤ 2×10^5)
q: number of queries (1 ≤ q ≤ 2×10^5)
segments: vector of pairs where segments[i] = {x_i, y_i} (1 ≤ x_i < y_i ≤ 10^9)
queries: vector of pairs where queries[i] = {l_i, r_i} (1 ≤ l_i < r_i ≤ 10^9)
Output Format: Return a vector where each element is: (f(l,r) - g(l,r)) mod 998244353 for the corresponding query

Constraints:

All segments are distinct (no duplicate [x_i,y_i] pairs)
All values are integers
Must handle maximum constraints efficiently
Examples:

Example 1: Input: m = 4, q = 2 segments = {{1,3}, {4,6}, {2,4}, {3,5}} queries = {{1,4}, {1,5}}

Output: {1, 0}

Notes:

998244352 is congruent to -1 mod 998244353
Result depends on whether [l,r] can be exactly formed and the parity of required segments
Solution must efficiently handle the upper constraint limits