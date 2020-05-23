// Bundling

// Problem

// Pip has N strings. Each string consists only of letters from A to Z. Pip would like to bundle their strings into groups of size K. Each string must belong to exactly one group.

// The score of a group is equal to the length of the longest prefix shared by all the strings in that group. For example:

//    The group {RAINBOW, RANK, RANDOM, RANK} has a score of 2 (the longest prefix is 'RA').
//    The group {FIRE, FIREBALL, FIREFIGHTER} has a score of 4 (the longest prefix is 'FIRE').
//    The group {ALLOCATION, PLATE, WORKOUT, BUNDLING} has a score of 0 (the longest prefix is '').

// Please help Pip bundle their strings into groups of size K, such that the sum of scores of the groups is maximized.

// Input

// The first line of the input gives the number of test cases, T. T test cases follow. Each test case begins with a line containing the two integers N and K. Then, N lines follow, each containing one of Pip's strings.

// Output

// For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the maximum sum of scores possible.

// Limits

// Time limit: 20 seconds per test set.
// Memory limit: 1GB.
// 1 ≤ T ≤ 100.
// 2 ≤ N ≤ 105.
// 2 ≤ K ≤ N.
// K divides N.
// Each of Pip's strings contain at least one character.
// Each string consists only of letters from A to Z.

// Use Trie: count the total number of prefixes and then divide by K.

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class TrieNode{
public:
    vector<TrieNode*> arr;
    unsigned int cnt;
    TrieNode():cnt(0){
        for(int i = 0; i < 26; ++i){
            arr.push_back(nullptr);
        }
    }
    int score(unsigned int k){
        int ans = 0;
        for(auto pt : arr){
            if(pt != nullptr){
                ans += pt -> cnt / k;
                ans += pt -> score(k);
            }
        }
        return ans;
    }
};

class Trie{
    TrieNode* root;
public:
    Trie(){
        root = new TrieNode;
    }
    void insert(string s){
        auto node = root;
        for(auto it = s.begin(); it != s.end(); ++it){
            if(node -> arr[*it - 'A'] == nullptr){
                node -> arr[*it - 'A'] = new TrieNode;
            }
            node = node -> arr[*it - 'A'];
            ++node -> cnt;
        }
    }
    int score(unsigned int k){
        return root -> score(k);
    }
};

int main(){
    int T;
    cin >> T;
    int t = 1;
    while(T--){
        int n, b;
        cin >> n >> b;
        string s;
        Trie* trie = new Trie;
        for(int i = 0; i < n; ++i){
            cin >> s;
            trie -> insert(s);
        }
        cout << "Case #" << t << ": " << trie -> score(b) << endl;
        ++t;
    }
    return 0;
}

// 2
// 2 2
// KICK
// START
// Case #1: 0
// 8 2
// G
// G
// GO
// GO
// GOO
// GOO
// GOOO
// GOOO
// Case #2: 10

// 1
// 6 3
// RAINBOW
// FIREWALL
// RANK
// RANDOM
// FIREWALL
// FIREFIGHTER
// Case #1: 6
