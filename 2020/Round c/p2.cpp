// Stable Wall

// Problem

// Apollo is playing a game involving polyominos. A polyomino is a shape made by joining together one or more squares edge to edge to form a single connected shape. The game involves combining N polyominos into a single rectangular shape without any holes. Each polyomino is labeled with a unique character from A to Z.

// Apollo has finished the game and created a rectangular wall containing R rows and C columns. He took a picture and sent it to his friend Selene. Selene likes pictures of walls, but she likes them even more if they are stable walls. A wall is stable if it can be created by adding polyominos one at a time to the wall so that each polyomino is always supported. A polyomino is supported if each of its squares is either on the ground, or has another square below it.

// Apollo would like to check if his wall is stable and if it is, prove that fact to Selene by telling her the order in which he added the polyominos.

// Input

// The first line of the input gives the number of test cases, T. T test cases follow. Each test case begins with a line containing the two integers R and C. Then, R lines follow, describing the wall from top to bottom. Each line contains a string of C uppercase characters from A to Z, describing that row of the wall.

// Output

// For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is a string of N uppercase characters, describing the order in which he built them. If there is more than one such order, output any of them. If the wall is not stable, output -1 instead.

// Limits

// Time limit: 20 seconds per test set.
// Memory limit: 1GB.
// 1 ≤ T ≤ 100.
// 1 ≤ R ≤ 30.
// 1 ≤ C ≤ 30.
// No two polyominos will be labeled with the same letter.
// The input is guaranteed to be valid according to the rules described in the statement.

// Topological sorting

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

typedef unordered_map<char, unordered_set<char>> graph;
typedef unordered_map<char, int> counter;

string DAG(vector<vector<char>>& arr, int m, int n){
    graph g;
    counter idg;
    for(int i = 0; i < m; ++i){
        for(int j = 0; j < n; ++j){
            if(i < m - 1 && arr[i][j] != arr[i + 1][j]){
                auto got = g.find(arr[i + 1][j]);
                if(got == g.end()){
                    g[arr[i + 1][j]] = {arr[i][j]};
                }else{
                    g[arr[i + 1][j]].insert(arr[i][j]);
                }
            }
            idg[arr[i][j]] = 0;
        }
    }
    for(auto& e : g){
        for(auto x : e.second){
            ++idg[x];
        }
    }
    unsigned int S = idg.size();
    vector<char> q;
    for(auto& e : idg){
        if(e.second == 0){
            q.push_back(e.first);
        }
    }
    string ans = "";
    while(!q.empty()){
        char c = q.back();
        q.pop_back();
        ans.append(1, c);
        for(char y : g[c]){
            --idg[y];
            if(idg[y] == 0){
                q.push_back(y);
            }
        }
    }
    if(ans.length() != S)
        return "-1";
    return ans;
}

int main(){
    int T;
    cin >> T;
    int t = 1;
    while(T--){
        int m, n;
        cin >> m >> n;
        vector<vector<char>> arr; 
        for(int i = 0; i < m; ++i){
            vector<char> row(n);
            for(int j = 0; j < n; ++j){
                cin >> row[j];
            }
            arr.push_back(row);
        }
        cout << "Case #" << t << ": " << DAG(arr, m, n) << endl;
        ++t;
    }
    return 0;
}

// 4
// 4 6
// ZOAAMM
// ZOAOMM
// ZOOOOM
// ZZZZOM
// Case #1: ZOAM/ZOMA
// 4 4
// XXOO
// XFFO
// XFXO
// XXXO
// Case #2: -1
// 5 3
// XXX
// XPX
// XXX
// XJX
// XXX
// Case #3: -1
// 3 10
// AAABBCCDDE
// AABBCCDDEE
// AABBCCDDEE
// Case #4: EDCBA
