// Countdown

// Problem

// Avery has an array of N positive integers. The i-th integer of the array is Ai.

// A contiguous subarray is an m-countdown if it is of length m and contains the integers m, m-1, m-2, ..., 2, 1 in that order. For example, [3, 2, 1] is a 3-countdown.

// Can you help Avery count the number of K-countdowns in her array?

// Input

// The first line of the input gives the number of test cases, T. T test cases follow. Each test case begins with a line containing the integers N and K. The second line contains N integers. The i-th integer is Ai.

// Output

// For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the number of K-countdowns in her array.

// Limits

// Time limit: 20 seconds per test set.
// Memory limit: 1GB.
// 1 ≤ T ≤ 100.
// 2 ≤ K ≤ N.
// 1 ≤ Ai ≤ 2 × 105, for all i.

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int countDown(vector<int>& arr, int N, int K){
    int p = -1;
    int ans = 0;
    for(int i = 0; i < N; ++i){
        if(arr[i] == K){
            p = i;
        }else if(arr[i] < K){
            if(p >= 0 && K - arr[i] == i - p){
                if(arr[i] == 1){
                    ++ans;
                    p = -1;
                }
            }else{
                p = -1;
            }
        }else{
            p = -1;
        }
    }
    return ans;
}

int main(){
    int T;
    cin >> T;
    int t = 1;
    while(T--){
        int n, k;
        cin >> n >> k;
        vector<int> arr(n);
        for(int i = 0; i < n; ++i){
            cin >> arr[i];
        }
        cout << "Case #" << t << ": " << countDown(arr, n, k) << endl;
        ++t;
    }
    return 0;
}

// 3
// 12 3
// 1 2 3 7 9 3 2 1 8 3 2 1
// Case #1: 2
// 4 2
// 101 100 99 98
// Case #2: 0
// 9 6
// 100 7 6 5 4 3 2 1 100
// Case #3: 1
