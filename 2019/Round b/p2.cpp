// Energy Stones

// Problem

// Duda the rock monster lives in the enchanted forest and has collected N energy stones for lunch. Since he has a small mouth, he eats energy stones one at a time. Some stones are tougher than others! The i-th stone takes him Si seconds to eat.

// Duda eats energy stones to get energy. Different stones give him different amounts of energy. Furthermore, the stones lose energy over time. The i-th stone initially contains Ei units of energy and will lose Li units of energy each second. When Duda starts to eat a stone, he will receive all the energy the stone contains immediately (no matter how much time it takes to actually finish eating the stone). The stone's energy stops decreasing once it hits zero.

// What is the largest amount of energy Duda could receive from eating his stones?

// Input

// The first line of the input gives the number of test cases, T. T test cases follow. Each test case starts with a line containing the integer N, the number of energy stones Duda has. Then, there are N more lines, the i-th of which contains the three integers Si, Ei and Li, as described above.

// Output

// For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the maximum amount of energy Duda could receive from eating stones.

// Limits

// Time limit: 30 seconds per test set.
// Memory limit: 1GB.
// 1 ≤ T ≤ 100.
// 1 ≤ N ≤ 100.
// 1 ≤ Si ≤ 100.
// 1 ≤ Ei ≤ 100000.
// 0 ≤ Li ≤ 100000.

// DP, with items being sorted by S_i * L_j < S_j * L_i

#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>

using namespace std;

typedef tuple<long, long, long> T;

bool compareTuples(const T& lhs, const T& rhs){
    return get<0>(lhs) * get<2>(rhs) < get<0>(rhs) * get<2>(lhs);
}

long eat(const vector<T>& arr, int n, long t){
    vector<vector<long>> table;
    for(long i = 0; i <= t; ++i){
        vector<long> row(n + 1, 0);
        table.push_back(row);
    }
    int j = n - 1;
    for(auto it = arr.rbegin(); it != arr.rend(); ++it, --j){
        for(long i = 0; i <= t - get<0>(*it); ++i){
            table[i][j] = max(table[i][j + 1], max(0L, get<1>(*it) - i * get<2>(*it)) + table[i + get<0>(*it)][j + 1]); 
        }
    }
    return table[0][0];
}

int main(){
    int N;
    cin >> N;
    int t = 1;
    while(N--){
        int n;
        cin >> n;
        long s, e, l;
        vector<T> arr;
        long total = 0;
        for(int i = 0; i < n; ++i){
            cin >> s >> e >> l;
            arr.push_back(make_tuple(s, e, l));
            total += s;
        }
        sort(arr.begin(), arr.end(), compareTuples);
        cout << "Case #" << t << ": " << eat(arr, n, total) << endl;
        ++t;
    }
    return 0;
}

// 3
// 4
// 20 10 1
// 5 30 5
// 100 30 1
// 5 80 60
// 3
// 10 4 1000
// 10 3 1000
// 10 8 1000
// 2
// 12 300 50
// 5 200 0

