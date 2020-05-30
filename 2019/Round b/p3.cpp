// Diverse Subarray

// Problem

// Vanity has N trinkets on her shelf, numbered 1, 2, ..., N from left to right. Trinkets come in different types, which are denoted by positive integers. The i-th trinket on her shelf is of type Ai.

// She is going to see her family overseas today and would like to bring as many trinkets as she can. However, since she is in a hurry, Vanity must take a consecutive interval of trinkets. Formally, Vanity selects two indices, l and r, and takes all of the trinkets numbered l, l+1, ..., r-1, r. Also, due to tax rules, airport security will throw away all trinkets of a type if Vanity has more than S of that type in the chosen interval.

// For example, suppose that S = 2, and Vanity brings six trinkets: one of type 0, two of type 1, and three of type 2. She will be allowed to keep the trinket of type 0 and both trinkets of type 1, but she will lose all of the trinkets of type 2!

// Vanity needs to choose l and r such that she can take the maximum number of trinkets for her family. What is the maximum number of trinkets she can bring?

// Input

// The first line of the input gives the number of test cases, T. T test cases follow. The first line of each test case contains the two integers N and S, the number of trinkets, and the maximum number of trinkets allowed of a single type, respectively. The second line contains N integers. The i-th integer gives Ai, the type of the i-th trinket.

// Output

// For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the maximum number of trinkets that Vanity can bring to her family.

// Limits

// Time limit: 30 seconds per test set.
// Memory limit: 1GB.
// 1 ≤ T ≤ 100.
// 1 ≤ Ai ≤ 100000.
// 1 ≤ S ≤ N.

// Segment Tree

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits>

using namespace std;

typedef struct TreeNode{
    long sum;
    long prefix;
} node;

int SuperCeiling(int n){
    int p;
    for(p = 1; p < n; p = 2 * p);
    return p;
}

int Parent(int i) {return i/2;}
int LeftChild(int i) {return 2*i;}
int RightChild(int i) {return 2*i+1;}

class SegTree{
    vector<node> q;
public:
    SegTree(int N){
        for(int i = 0; i < 2 * N; ++i){
            node x = {0L, numeric_limits<long>::min()};
            q.push_back(x);
        }
    }
    void update(int i, long val){
        q[i].sum += val;
        q[i].prefix = q[i].sum;
        i = Parent(i);
        while(i > 0){
            q[i].sum += val;
            q[i].prefix = max(q[LeftChild(i)].prefix, q[LeftChild(i)].sum + q[RightChild(i)].prefix);
            i = Parent(i);
        }
    }
    node no_value(){
        node ret = {numeric_limits<long>::min(), numeric_limits<long>::min()};
        return ret;
    }
    node query(int l, int r, int i, int j, int t){
        if(l == i && r == j){
            node ret = {q[t].sum, q[t].prefix};
            return ret;
        }else{
            int m = l + (r - l) / 2;
            auto t1 = (i <= m) ? query(l, m, i, min(m, j), LeftChild(t)) : no_value();
            auto t2 = (j > m) ? query(m + 1, r, max(m + 1, i), j, RightChild(t)) : no_value();
            if(t1.prefix > numeric_limits<long>::min()){
                node ret;
                ret.sum = t1.sum + t2.sum;
                ret.prefix = ((t2.prefix > numeric_limits<long>::min()) ? max(t1.prefix, t1.sum + t2.prefix) : t1.prefix);
                return ret;
            }
            return t2;
        }
    }
};

int main(){
    int T;
    cin >> T;
    int t = 1;
    while(T--){
        int n, s;
        cin >> n >> s;
        vector<int> arr(n);
        unordered_map<int, vector<int>> dict;
        unordered_map<int, int> ptr;
        for(int i = 0; i < n; ++i){
            cin >> arr[i];
            dict[arr[i]].push_back(i);
        }
        for(int i = 0; i < n; ++i){
            ptr[arr[i]] = dict[arr[i]].size() - 1;
        }
        int N = SuperCeiling(n);
        auto q = new SegTree(N);
        long ans = numeric_limits<long>::min();
        for(int i = n - 1; i >= 0; --i){
            int a = arr[i];
            q -> update(i + N, 1L);
            if(ptr[a] + s <= dict[a].size() - 1){
                q -> update(dict[a][ptr[a] + s] + N, (long)(-s - 1));
            }
            if(ptr[a] + s < dict[a].size() - 1){
                q -> update(dict[a][ptr[a] + s + 1] + N, (long)s);
            }
            --ptr[arr[i]];
            auto ret = q -> query(0, N - 1, i, n - 1, 1);
            ans = max(ans, ret.prefix);
        }
        cout << "Case #" << t << ": " << ans << endl;
        ++t;
    }
    return 0;
}

// Test cases
// 5
// 6 2
// 1 1 4 1 4 4
// 8 1
// 1 2 500 3 4 500 6 7
// 10 1
// 100 200 8 8 8 8 8 300 400 100
// 12 2
// 40 50 1 1 1 60 70 2 2 2 80 90
// 9 2
// 1 1 2 1 3 2 3 2 2
