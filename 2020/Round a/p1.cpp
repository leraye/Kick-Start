// Allocation

// Problem

// There are N houses for sale. The i-th house costs Ai dollars to buy. You have a budget of B dollars to spend.

// What is the maximum number of houses you can buy?

// Input

// The first line of the input gives the number of test cases, T. T test cases follow. Each test case begins with a single line containing the two integers N and B. The second line contains N integers. The i-th integer is Ai, the cost of the i-th house.

// Output

// For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the maximum number of houses you can buy.

// Limits

// Time limit: 15 seconds per test set.
// Memory limit: 1GB.
// 1 ≤ T ≤ 100.
// 1 ≤ B ≤ 105.
// 1 ≤ Ai ≤ 1000, for all i.

// Greedy
#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;

int allocate(vector<int>& arr, int N, int B){
    sort(arr.begin(), arr.end());
    unsigned int t = 0;
    int s = 0;
    for(int x : arr){
        s += x;
        if(s <= B){
            ++t;
        }
    }
    return t;
}

int main(){
    int N;
    cin >> N;
    int t = 1;
    while(N--){
        int n;
        cin >> n;
        int b;
        cin >> b;
        vector<int> arr(n);
        for(unsigned int i = 0; i < n; ++i){
            cin >> arr[i];
        }
        cout << "Case #" << t << ": " << allocate(arr, n, b) << endl;
        t += 1;
    }
    return 0;
}

// Test Case
// 3
// 4 100
// 20 90 40 90
// Case #1: 2
// 4 50
// 30 30 10 10
// Case #2: 3
// 3 300
// 999 999 999
// Case #3: 0
