// Wiggle Walk

// Problem

/*
Banny has just bought a new programmable robot. Eager to test his coding skills, he has placed the robot in a grid of squares with R rows (numbered 1 to R from north to south) and C columns (numbered 1 to C from west to east). The square in row r and column c is denoted (r, c).

Initially the robot starts in the square (SR, SC). Banny will give the robot N instructions. Each instruction is one of N, S, E or W, instructing the robot to move one square north, south, east or west respectively.

If the robot moves into a square that it has been in before, the robot will continue moving in the same direction until it reaches a square that it has not been in before. Banny will never give the robot an instruction that will cause it to move out of the grid.

Can you help Banny determine which square the robot will finish in, after following the N instructions?
*/

// Input

/*
 The first line of the input gives the number of test cases, T. T test cases follow. Each test case starts with a line containing the five integers N, R, C, SR and SC, the number of instructions, the number of rows, the number of columns, the robot's starting row and starting column, respectively.

Then, another line follows containing a single string of N characters; the i-th of these characters is the i-th instruction Banny gives the robot (one of N, S, E or W, as described above). 
*/

// Output

/*
For each test case, output one line containing Case #x: r c, where x is the test case number (starting from 1), r is the row the robot finishes in and c is the column the robot finishes in. 
*/

// Limits

/*
1 ≤ T ≤ 100.
1 ≤ R ≤ 5 × 104.
1 ≤ C ≤ 5 × 104.
1 ≤ SR ≤ R.
1 ≤ SC ≤ C.
The instructions will not cause the robot to move out of the grid.
*/

// Implicit Graph

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

typedef struct position{
    int x, y;
} pos;

string make_key(pos p){
    return to_string(p.x) + " " + to_string(p.y);
}

pos path(string& s, pos start){
    unordered_map<string, unordered_map<char, pos>> neighbors;
    string k1;
    k1 = make_key(start);
    pos e, w, nth, sth;
    for(char c : s){
        if(neighbors.find(k1) == neighbors.end()){
            e = {start.x, start.y + 1};
            w = {start.x, start.y - 1};
            nth = {start.x - 1, start.y};
            sth = {start.x + 1, start.y};
        }else{
            if(neighbors[k1].find('E') == neighbors[k1].end()){
                e = {start.x, start.y + 1};
            }else{
                e = neighbors[k1]['E'];
            }
            if(neighbors[k1].find('W') == neighbors[k1].end()){
                w = {start.x, start.y - 1};
            }else{
                w = neighbors[k1]['W'];
            }
            if(neighbors[k1].find('N') == neighbors[k1].end()){
                nth = {start.x - 1, start.y};
            }else{
                nth = neighbors[k1]['N'];
            }
            if(neighbors[k1].find('S') == neighbors[k1].end()){
                sth = {start.x + 1, start.y};
            }else{
                sth = neighbors[k1]['S'];
            }
            neighbors.erase(k1);
        }
        neighbors[make_key(e)]['W'] = w;
        neighbors[make_key(w)]['E'] = e;
        neighbors[make_key(nth)]['S'] = sth;
        neighbors[make_key(sth)]['N'] = nth;
        if(c == 'E')
            start = e;
        if(c == 'W')
            start = w;
        if(c == 'N')
            start = nth;
        if(c == 'S')
            start = sth;
        k1 = make_key(start);
    }
    return start;
}

int main(){
    int T;
    cin >> T;
    int t = 1;
    while(T--){
        int n, r, c, x, y;
        cin >> n >> r >> c >> x >> y;
        string s;
        cin >> s;
        pos start = {x, y};
        auto ans = path(s, start);
        cout << "Case #" << t << ": " << ans.x << " " << ans.y << endl;;
        ++t;
    }
    return 0;
}

// Test Cases

/*
3
5 3 6 2 3
EEWNS
Case #1: 3 2
4 3 3 1 1
SESE
Case #2: 3 3
11 5 8 3 4
NEESSWWNESE
Case #3: 3 7
*/
