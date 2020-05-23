// Workout

// Problem

// Tambourine has prepared a fitness program so that she can become more fit! The program is made of N sessions. During the i-th session, Tambourine will exercise for Mi minutes. The number of minutes she exercises in each session are strictly increasing.

// The difficulty of her fitness program is equal to the maximum difference in the number of minutes between any two consecutive training sessions.

// To make her program less difficult, Tambourine has decided to add up to K additional training sessions to her fitness program. She can add these sessions anywhere in her fitness program, and exercise any positive integer number of minutes in each of them. After the additional training session are added, the number of minutes she exercises in each session must still be strictly increasing. What is the minimum difficulty possible?

// Input

// The first line of the input gives the number of test cases, T. T test cases follow. Each test case begins with a line containing the two integers N and K. The second line contains N integers, the i-th of these is Mi, the number of minutes she will exercise in the i-th session.

// Output

// For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the minimum difficulty possible after up to K additional training sessions are added.

// Limits

// Time limit: 20 seconds per test set.
// Memory limit: 1GB.
// 1 ≤ T ≤ 100.
// For at most 10 test cases, 2 ≤ N ≤ 105.
// For all other test cases, 2 ≤ N ≤ 300.
// 1 ≤ Mi ≤ 109.
// Mi < Mi+1 for all i.

// 力扣原题: trial & error; binary search

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int guess(vector<int>& arr, int n, int k){
    int l = 1;
    int r = 0;
    for(int i = 1; i < n; ++i){
        r = max(r, arr[i] - arr[i - 1]);
    }
    int ans = r;
    while(l <= r){
        int m = l + (r - l) / 2;
        int cnt = 0;
        for(int i = 1; i < n; ++i){
            int diff = arr[i] - arr[i - 1];
            if(diff >= m){
                if(diff % m == 0){
                    cnt += diff / m - 1;
                }else{
                    cnt += diff / m;
                }
            }
        }
        if(cnt <= k){
            ans = min(ans, m);
            r = m - 1;
        }else{
            l = m + 1;
        }
    }
    return ans;
}

int main(){
    int T;
    cin >> T;
    int t = 1;
    while(T--){
        int N, K;
        cin >> N >> K;
        vector<int> arr(N);
        for(int i = 0; i < N; ++i){
            cin >> arr[i];
        }
        cout << "Case #" << t << ": " << guess(arr, N, K) << endl;
        ++t;
    }
    return 0;
}

// 1
// 3 1
// 100 200 230
// Case #1: 50

// 3
// 5 2
// 10 13 15 16 17
// Case #1: 2
// 5 6
// 9 10 20 26 30
// Case #2: 3
// 8 3
// 1 2 3 4 5 6 7 10
// Case #3: 1
