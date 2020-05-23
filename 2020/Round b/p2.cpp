// Bus Routes

// Problem

//  Bucket is planning to make a very long journey across the countryside by bus. Her journey consists of N bus routes, numbered from 1 to N in the order she must take them. The buses themselves are very fast, but do not run often. The i-th bus route only runs every Xi days.

// More specifically, she can only take the i-th bus on day Xi, 2Xi, 3Xi and so on. Since the buses are very fast, she can take multiple buses on the same day.

// Bucket must finish her journey by day D, but she would like to start the journey as late as possible. What is the latest day she could take the first bus, and still finish her journey by day D?

// It is guaranteed that it is possible for Bucket to finish her journey by day D.

// Input

// The first line of the input gives the number of test cases, T. T test cases follow. Each test case begins with a line containing the two integers N and D. Then, another line follows containing N integers, the i-th one is Xi.

// Output

// For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the latest day she could take the first bus, and still finish her journey by day D.

// Limits

// Time limit: 10 seconds per test set.
// Memory limit: 1GB.
// 1 ≤ T ≤ 100.
// 1 ≤ Xi ≤ D.
// 1 ≤ N ≤ 1000.
// It is guaranteed that it is possible for Bucket to finish her journey by day D.

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

long latestDay(vector<long>& arr, long d){
    long ans = d;
    for(auto it = arr.rbegin(); it != arr.rend(); ++it){
        ans -= ans % *it;
    }
    return ans;
}

int main(){
    int T;
    cin >> T;
    int t = 1;
    while(T--){
        int n;
        long d;
        cin >> n >> d;
        vector<long> arr(n);
        for(int i = 0; i < n; ++i){
            cin >> arr[i];
        }
        cout << "Case #" << t << ": " << latestDay(arr, d) << endl;
        ++t;
    }
    return 0;
}

// 3
// 3 10
// 3 7 2
// Case #1: 6
// 4 100
// 11 10 5 50
// Case #2: 99
// 1 1
// 1
// Case #3: 1
