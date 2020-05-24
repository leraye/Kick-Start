// Candies

// Problem

// Carl has an array of N candies. The i-th element of the array (indexed starting from 1) is Ai representing sweetness value of the i-th candy. He would like to perform a series of Q operations. There are two types of operation:

//    Update the sweetness value of a candy in the array.
//    Query the sweetness score of a subarray.

// The sweetness score of a subarray from index l to r is: Al × 1 - Al+1 × 2 + Al+2 × 3 - Al+3 × 4 + Al+4 × 5 ...

// More formally, the sweetness score is the sum of (-1)i-lAi × (i - l + 1), for all i from l to r inclusive.

// For example, the sweetness score of:

//    [3, 1, 6] is 3 × 1 - 1 × 2 + 6 × 3 = 19
//    [40, 30, 20, 10] is 40 × 1 - 30 × 2 + 20 × 3 - 10 × 4 = 0
//    [2, 100] is 2 × 1 - 100 × 2 = -198

// Carl is interested in finding out the total sum of sweetness scores of all queries. If there is no query operation, the sum is considered to be 0. Can you help Carl find the sum?

// Input

// The first line of the input gives the number of test cases, T. T test cases follow. Each test case begins with a line containing N and Q. The second line contains N integers describing the array. The i-th integer is Ai. The j-th of the following Q lines describe the j-th operation. Each line begins with a single character describing the type of operation (U for update, Q for query).

//    For an update operation, two integers Xj and Vj follow, indicating that the Xj-th element of the array is changed to Vj.
//    For a query operation, two integers Lj and Rj follow, querying the sweetness score of the subarray from the Lj-th element to the Rj-th element (inclusive).

// Output

// For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the total sum of sweetness scores of all the queries.

// Limits

// Time limit: 20 seconds per test set.
// Memory limit: 1GB.
// 1 ≤ T ≤ 100.
// 1 ≤ Ai ≤ 100, for all i.
// 1 ≤ N ≤ 2 × 105 and 1 ≤ Q ≤ 105 for at most 6 test cases.
// For the remaining cases, 1 ≤ N ≤ 300 and 1 ≤ Q ≤ 300.
// If the j-th operation is an update operation, 1 ≤ Xj ≤ N and 1 ≤ Vj ≤ 100.
// If the j-th operation is a query operation, 1 ≤ Lj ≤ Rj ≤ N.

// BIT

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class DoubleBITree{
    vector<long> A;
    vector<long> Tree1;
    vector<long> Tree2;
    int LSB(int i){
        return (i & (-i));
    }
    int SIZE;
public:
    DoubleBITree(vector<long>& arr, int n){
        A.push_back(0);
        Tree1.push_back(0);
        Tree2.push_back(0);
        for(auto a : arr){
            A.push_back(a);
            Tree1.push_back(0);
            Tree2.push_back(0);
        }
        SIZE = n;
        int j;
        long k = 1;
        for(int i = 1; i <= SIZE; ++i){
            Tree1[i] += A[i] * k;
            Tree2[i] += A[i] * k * i;
            j = i + LSB(i);
            while(j <= SIZE){
                Tree1[j] += A[i] * k;
                Tree2[j] += A[i] * k * i;
                j += LSB(j);
            }
            k *= -1;
        }
    }
    void update(int i, long val){
        long x, y;
        if(i & 1){
            x = val - A[i];
            y = i * x;
        }else{
            x = -1 * val + A[i];
            y = i * x;
        }
        A[i] = val;
        while(i <= SIZE){
            Tree1[i] += x;
            Tree2[i] += y;
            i += LSB(i);
        }
    }
    long sum(int i, bool bit1=true){
        long sum = 0;
        while(i > 0){
            if(bit1){
                sum += Tree1[i];
            }else{
                sum += Tree2[i];
            }
            i -= LSB(i);
        }
        return sum;
    }
    long rangeSum(int i, int j){
        long r = 0;
        if((i & 1) ^ (j & 1)){
            if(j & 1){
                r += -1 * this -> sum(j, false) + this -> sum(i - 1, false);
                r -= (i - 1) * (-1 * this -> sum(j) + this -> sum(i - 1));
            }else{
                r += this -> sum(j, false) - this -> sum(i - 1, false);
                r -= (i - 1) * (this -> sum(j) - this -> sum(i - 1));
            }
        }else{
            if(j & 1){
                r += this -> sum(j, false) - this -> sum(i - 1, false);
                r -= (i - 1) * (this -> sum(j) - this -> sum(i - 1));
            }else{
                r += -1 * this -> sum(j, false) + this -> sum(i - 1, false);
                r -= (i - 1) * (-1 * this -> sum(j) + this -> sum(i - 1));
            }
        }
        return r;
    }
};

int main(){
    int T;
    cin >> T;
    int t = 1;
    while(T--){
        int n, q;
        cin >> n >> q;
        vector<long> arr(n);
        for(int k = 0; k < n; ++k){
            cin >> arr[k];
        }
        long ans = 0;
        auto pt = new DoubleBITree(arr, n);
        string s, n1, n2;
        for(int j = 0; j < q; ++j){
            cin >> s >> n1 >> n2;
            int i = stoi(n1);
            int x = stoi(n2);
            if(s == "Q"){
                ans += pt -> rangeSum(i, x);
            }else{
                pt -> update(i, x);
            }
        }
        cout << "Case #" << t << ": " << ans << endl;
        ++t;
    }
    return 0;
}

// 2
// 5 4
// 1 3 9 8 2
// Q 2 4
// Q 5 5
// U 2 10
// Q 1 2
// Case #1: -8
// 3 3
// 4 5 5
// U 1 2
// U 1 7
// Q 1 2
// Case #2: -3
