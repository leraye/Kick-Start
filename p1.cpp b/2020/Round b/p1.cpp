// Bike Tour

// Problem
//  Li has planned a bike tour through the mountains of Switzerland. His tour consists of N checkpoints, numbered from 1 to N in the order he will visit them. The i-th checkpoint has a height of Hi.

// A checkpoint is a peak if:

//    It is not the 1st checkpoint or the N-th checkpoint, and
//    The height of the checkpoint is strictly greater than the checkpoint immediately before it and the checkpoint immediately after it.

// Please help Li find out the number of peaks.

// Input

// The first line of the input gives the number of test cases, T. T test cases follow. Each test case begins with a line containing the integer N. The second line contains N integers. The i-th integer is Hi.

// Output

// For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the number of peaks in Li's bike tour.

// Limits

// Time limit: 10 seconds per test set.
// Memory limit: 1GB.
// 1 ≤ T ≤ 100.
// 1 ≤ Hi ≤ 100.

#include <iostream>
#include <vector>
using namespace std;

int countPeaks(vector<int>& arr, int N){
    int ans = 0;
    for(int i = 1; i < N - 1; ++i){
        if(arr[i] > arr[i - 1] && arr[i] > arr[i + 1]){
            ++ans;
        }
    }
    return ans;
}

int main(){
    int T;
    cin >> T;
    int t = 1;
    while(T--){
        int n;
        cin >> n;
        vector<int> arr(n);
        for(int i = 0; i < n; ++i){
            cin >> arr[i];
        }
        cout << "Case #" << t << ": " << countPeaks(arr, n) << endl;
        ++t;
    }
    return 0;
}

// 4
// 3
// 10 20 14
// Case #1: 1
// 4
// 7 7 7 7
// Case #2: 0
// 5
// 10 90 20 90 10
// Case #3: 2
// 3
// 10 3 10
// Case #4: 0