// Building Palindromes

// Problem

// Anna has a row of N blocks, each with exactly one letter from A to Z written on it. The blocks are numbered 1, 2, ..., N from left to right.

// Today, she is learning about palindromes. A palindrome is a string that is the same written forwards and backwards. For example, ANNA, RACECAR, AAA and X are all palindromes, while AB, FROG and YOYO are not.

// Bob wants to test how well Anna understands palindromes, and will ask her Q questions. The i-th question is: can Anna use all of the blocks numbered from Li to Ri, inclusive, rearranging them if necessary, to form a palindrome? After each question, Anna puts the blocks back in their original positions.

// Please help Anna by finding out how many of Bob's questions she can answer "yes" to.

// Input

// The first line of the input gives the number of test cases, T. T test cases follow. Each test case starts with a line containing the two integers N and Q, the number of blocks and the number of questions, respectively. Then, another line follows, containing a string of N uppercase characters (A to Z). Then, Q lines follow. The i-th line contains the two integers Li to Ri, describing the i-th question.

// Output

// For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the number of questions Anna can answer "yes" to.

// Limits

// Time limit: 30 seconds per test set.
// Memory limit: 1GB.
// 1 ≤ T ≤ 100. 1 ≤ Li ≤ Ri ≤ N.

// bit mask

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

typedef unsigned int uint;

vector<uint> parity(const string& s){
    vector<uint> bits;
    bits.push_back(0);
    vector<uint> chars(26, 0);
    for(auto c : s){
        uint idx = c - 'A';
        chars[idx] += 1;
        uint t = bits.back();
        if(chars[idx] & 1){
            t |= (1 << idx);
        }else{
            t &= (numeric_limits<uint>::max() ^ (1 << idx));
        }
        bits.push_back(t);
    }
    return bits;
}

uint query(const vector<uint>& bits, const uint l, const uint r){
    auto prev = bits[l - 1];
    auto curr = bits[r];
    auto x = prev ^ curr;
    if(x == 0)
        return 1;
    uint cnt = 0;
    while(x > 0){
        if(x & 1)
            ++cnt;
        if(cnt > 1)
            return 0;
        x >>= 1;
    }
    return cnt;
}

int main(){
    int T;
    cin >> T;
    int t = 1;
    while(T--){
        int n, q;
        cin >> n >> q;
        string s;
        cin >> s;
        auto dic = parity(s);
        uint ans = 0;
        for(int i = 0; i < q; ++i){
            uint l, r;
            cin >> l >> r;
            ans += query(dic, l, r);
        }
        cout << "Case #" << t << ": " << ans << endl;
        ++t;
    }
    return 0;
}
