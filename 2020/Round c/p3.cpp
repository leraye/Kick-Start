// Perfect Subarray

// Problem

// Cristobal has an array of N (possibly negative) integers. The i-th integer in his array is Ai. A contiguous non-empty subarray of Cristobal's array is perfect if its total sum is a perfect square. A perfect square is a number that is the product of a non-negative integer with itself. For example, the first five perfect squares are 0, 1, 4, 9 and 16.

// How many subarrays are perfect? Two subarrays are different if they start or end at different indices in the array, even if the subarrays contain the same values in the same order.

// Input

// The first line of the input gives the number of test cases, T. T test cases follow. The first line of each test case contains the integer N. The second line contains N integers describing Cristobal's array. The i-th integer is Ai.

// Output

// For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the number of perfect subarrays.

// Limits

// Memory limit: 1GB.
// 1 ≤ T ≤ 100.
// -100 ≤ Ai ≤ 100, for all i.

// Prefix sum

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

typedef unordered_map<long, vector<int>> M;

long PerfectSubarray(vector<long>& arr, int n){
    long s = 0;
    vector<long> psum;
    for(auto a : arr){
        s += a;
        psum.push_back(s);
    }
    long diff = (*max_element(psum.begin(), psum.end())) - min(0L, *min_element(psum.begin(), psum.end()));
    vector<long> squares;
    long k = 0;
    while(k * k <= diff){
        squares.push_back(k * k);
        ++k;
    }
    long ans = 0;
    M prefix;
    prefix[0] = {-1};
    long MIN = 0;
    for(int i = 0; i < n; ++i){
        long x = psum[i];
        MIN = min(x, MIN);
        for(auto k : squares){
            if(x - k < MIN)
                break;
            if(prefix.find(x - k) != prefix.end()){
                ans += prefix[x - k].size();
            }
        }
        if(prefix.find(x) != prefix.end()){
            prefix[x].push_back(i);
        }else{
            prefix[x] = {i};
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
        vector<long> arr(n);
        for(int i = 0; i < n; ++i){
            cin >> arr[i];
        }
        cout << "Case #" << t << ": " << PerfectSubarray(arr, n) << endl;
        ++t;
    }
    return 0;
}

// 3
// 3
// 2 2 6
// Case #1: 1
// 5
// 30 30 9 1 30
// Case #2: 3
// 4
// 4 0 0 16
// Case #3: 9
