#include <vector>
#include <algorithm>
#include <tuple>
#include <cmath>
#include <iostream>
#include <utility>
using namespace std;

// Declaration of the solve function (must match segment.cpp)
vector<int> solve(int m, int q, const vector<pair<int,int>>& segments, const vector<pair<int,int>>& queries);

// Test tracking
int tests_passed = 0;
int tests_total = 0;

// Define MOD constant
const int MOD = 998244353;

void test_assert(bool condition, const string& test_name) {
    tests_total++;
    if (condition) {
        cout << "✓ PASS: " << test_name << endl;
        tests_passed++;
    } else {
        cout << "✗ FAIL: " << test_name << endl;
    }
}

bool compare_output(const vector<int>& result, const vector<int>& expected) {
    if (result.size() != expected.size()) return false;
    for (size_t i = 0; i < result.size(); i++) {
        if (result[i] != expected[i]) return false;
    }
    return true;
}

// ------------- TEST CASES -------------------

void test_case_1() {
    vector<pair<int,int>> segments = {{1, 3}, {4, 6}, {2, 4}, {3, 5}};
    vector<pair<int,int>> queries = {{1, 4}, {1, 5}};
    vector<int> expected = {1, 0};
    auto result = solve(4, 2, segments, queries);
    test_assert(compare_output(result, expected), "Test Case 1 - Example Input");
}

void test_case_2() {
    vector<pair<int,int>> segments = {{1, 5}};
    vector<pair<int,int>> queries = {{1, 5}, {2, 4}, {1, 3}};
    vector<int> expected = {MOD-1, 0, 0};
    auto result = solve(1, 3, segments, queries);
    test_assert(compare_output(result, expected), "Test Case 2 - Single Segment");
}

void test_case_3() {
    vector<pair<int,int>> segments = {{1, 3}, {2, 4}, {3, 5}, {1, 5}};
    vector<pair<int,int>> queries = {{1, 5}, {1, 3}, {2, 4}, {3, 5}};
    vector<int> expected = {0, MOD-1, MOD-1, MOD-1};
    auto result = solve(4, 4, segments, queries);
    test_assert(compare_output(result, expected), "Test Case 3 - Overlapping Segments");
}

void test_case_4() {
    vector<pair<int,int>> segments = {{1, 2}, {3, 4}, {5, 6}};
    vector<pair<int,int>> queries = {{1, 2}, {3, 4}, {5, 6}, {1, 6}};
    vector<int> expected = {MOD-1, MOD-1, MOD-1, 0};
    auto result = solve(3, 4, segments, queries);
    test_assert(compare_output(result, expected), "Test Case 4 - Non-overlapping Segments");
}


void test_case_6() {
    vector<pair<int,int>> segments = {{1, 2}, {1, 5}, {2, 3}, {2, 6}, {4, 8}, {7, 9}, {10, 11}};
    vector<pair<int,int>> queries = {{1, 7}, {2, 8}, {2, 9}, {1, 3}};
    vector<int> expected = {0, 0, 0, 1};
    auto result = solve(7, 4, segments, queries);
    test_assert(compare_output(result, expected), "Test Case 6 - First Additional Input");
}

void test_case_7() {
    vector<pair<int,int>> segments = {{1, 2}, {1, 1000000000}, {999999999, 1000000000}};
    vector<pair<int,int>> queries = {{1, 2}};
    vector<int> expected = {MOD-1};
    auto result = solve(3, 1, segments, queries);
    test_assert(compare_output(result, expected), "Test Case 7 - Second Additional Input Part 1");
}

void test_case_8() {
    vector<pair<int,int>> segments = {{1, 2}, {1, 1000000000}, {999999999, 1000000000}};
    vector<pair<int,int>> queries = {{1, 1000000000}};
    vector<int> expected = {0};
    auto result = solve(3, 1, segments, queries);
    test_assert(compare_output(result, expected), "Test Case 8 - Second Additional Input Part 2");
}

void test_case_9() {
    vector<pair<int,int>> segments = {{1, 2}, {1, 1000000000}, {999999999, 1000000000}};
    vector<pair<int,int>> queries = {{999999999, 1000000000}};
    vector<int> expected = {MOD-1};
    auto result = solve(3, 1, segments, queries);
    test_assert(compare_output(result, expected), "Test Case 9 - Second Additional Input Part 3");
}

// ------------- MAIN -------------------

int main() {
    cout << "Running Segment Union Tests...\n";
    cout << "=============================\n";

    test_case_1();
    test_case_2();
    test_case_3();
    test_case_4();
    test_case_6();
    test_case_7();
    test_case_8();
    test_case_9();

    cout << "=============================\n";
    cout << "Tests passed: " << tests_passed << "/" << tests_total << endl;

    if (tests_passed == tests_total) {
        cout << " All tests passed!" << endl;
        return 0;
    } else {
        cout << " Some tests failed!" << endl;
        return 1;
    }
}
