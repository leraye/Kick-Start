// Plates

// Problem

// Dr. Patel has N stacks of plates. Each stack contains K plates. Each plate has a positive beauty value, describing how beautiful it looks.

// Dr. Patel would like to take exactly P plates to use for dinner tonight. If he would like to take a plate in a stack, he must also take all of the plates above it in that stack as well.

// Help Dr. Patel pick the P plates that would maximize the total sum of beauty values.

// Input

// The first line of the input gives the number of test cases, T. T test cases follow. Each test case begins with a line containing the three integers N, K and P. Then, N lines follow. The i-th line contains K integers, describing the beauty values of each stack of plates from top to bottom.

// Output

// For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the maximum total sum of beauty values that Dr. Patel could pick.

// Limits

// Time limit: 20 seconds per test set.
// Memory limit: 1GB.
// 1 ≤ T ≤ 100.
// 1 ≤ K ≤ 30.
// 1 ≤ P ≤ N * K.
// The beauty values are between 1 and 100, inclusive.

// DP: dp[i][j] which denotes the maximum sum that can be obtained using the first i stacks when we need to pick j plates in total. 

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int dp(vector<vector<int>>& arr, int m, int n, int p){
    vector<vector<int>> table;
    for(int i = 0; i <= m; ++i){
        vector<int> row(p + 1, 0);
        table.push_back(row);
    }
    for(int i = 1; i <= m; ++i){
        for(int j = 1; j <= p; ++j){
            int s = 0;
            for(int k = 0; k <= min(j, n); ++k){
                table[i][j] = max(table[i][j], s + table[i - 1][j - k]);
                s += arr[i - 1][k];
            }
        }
    }
    return table.back().back();
}

int main(){
    int T;
    cin >> T;
    int t = 1;
    while(T--){
        int N, K, P;
        cin >> N >> K >> P;
        vector<vector<int>> arr;
        for(int i = 0; i < N; ++i){
            vector<int> row(K);
            for(int j = 0; j < K; ++j){
                cin >> row[j];
            }
            arr.push_back(row);
        }
        cout << "Case #" << t << ": " << dp(arr, N, K, P) << endl;
        ++t;
    }
    return 0;
}

// 2
// 2 4 5
// 10 10 100 30
// 80 50 10 50
// Case #1: 250
// 3 2 3
// 80 80
// 15 50
// 20 10
// Case #2: 180
