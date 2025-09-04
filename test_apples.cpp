#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> solve(int n, int m, vector<vector<int>> apples);

int tests_passed = 0;
int tests_total = 0;

void test_assert(bool condition, const string& test_name) {
    tests_total++;
    if (condition) {
        cout << "✓ PASS: " << test_name << endl;
        tests_passed++;
    } else {
        cout << "✗ FAIL: " << test_name << endl;
    }
}

void test_case_1() {
    int n = 3, m = 4;
    vector<vector<int>> apples = {
        {1, 2},
        {},
        {3, 4}
    };
    vector<int> expected = {4};
    auto result = solve(n, m, apples);
    test_assert(result == expected, "Test Case 1: Basic case with empty day");
}

void test_case_2() {
    int n = 2, m = 3;
    vector<vector<int>> apples = {
        {1, 2, 3},
        {1, 2}
    };
    vector<int> expected = {0};
    auto result = solve(n, m, apples);
    test_assert(result == expected, "Test Case 2: All days have apples");
}

void test_case_3() {
    int n = 4, m = 5;
    vector<vector<int>> apples = {
        {},
        {1},
        {2, 3},
        {4, 5}
    };
    vector expected = {5};
    auto result = solve(n, m, apples);
    test_assert(result == expected, "Test Case 3: First day empty");
}

void test_case_4() {
    int n = 1, m = 10;
    vector<vector<int>> apples = {
        {}
    };
    vector<int> expected = {10};
    auto result = solve(n, m, apples);
    test_assert(result == expected, "Test Case 4: Single empty day");
}

void test_case_5() {
    int n = 5, m = 3;
    vector<vector<int>> apples = {
        {1},
        {2},
        {3},
        {1},
        {2}
    };
    vector expected = {1};
    auto result = solve(n, m, apples);
    test_assert(result == expected, "Test Case 5: Repeating apples");
}

void test_case_6() {
    int n = 3, m = 4;
    vector<vector<int>> apples = {
        {1, 2},
        {4, 1},
        {1, 2}
    };
    vector<int> expected = {2};
    auto result = solve(n, m, apples);
    test_assert(result == expected, "Test Case 6: Example 1 from problem");
}

void test_case_7() {
    int n = 4, m = 4;
    vector<vector<int>> apples = {
        {1, 2},
        {3, 4},
        {},
        {1}
    };
    vector expected = {1};
    auto result = solve(n, m, apples);
    test_assert(result == expected, "Test Case 7: Example 2 from problem");
}

void test_case_8() {
    int n = 2, m = 5;
    vector<vector<int>> apples = {
        {},
        {}
    };
    vector<int> expected = {5};
    auto result = solve(n, m, apples);
    test_assert(result == expected, "Test Case 8: Example 3 from problem");
}

void test_case_9() {
    int n = 5, m = 3;
    vector<vector<int>> apples = {
        {},
        {1, 2, 3},
        {3, 1},
        {},
        {3}
    };
    vector<int> expected = {3};
    auto result = solve(n, m, apples);
    test_assert(result == expected, "Test Case 9: Example 4 from problem");
}

void test_case_10() {
    int n = 6, m = 10;
    vector<vector<int>> apples = {
        {1, 2, 3},
        {4, 5, 6},
        {},
        {7, 8, 9},
        {10},
        {}
    };
    vector expected = {10};
    auto result = solve(n, m, apples);
    test_assert(result == expected, "Test Case 10: Larger test case");
}

int main() {
    cout << "Running Tests for solve..." << endl;
    cout << "=========================" << endl;

    test_case_1();
    test_case_2();
    test_case_3();
    test_case_4();
    test_case_5();
    test_case_6();
    test_case_7();
    test_case_8();
    test_case_9();
    test_case_10();

    cout << "=========================" << endl;
    cout << "Tests passed: " << tests_passed << "/" << tests_total << endl;

    if (tests_passed == tests_total) {
        cout << "🎉 All tests passed!" << endl;
        return 0;
    } else {
        cout << "❌ Some tests failed!" << endl;
        return 1;
    }
}
