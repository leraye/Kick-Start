// Robot Path Decoding

// Problem

//  Your country's space agency has just landed a rover on a new planet, which can be thought of as a grid of squares containing 109 columns (numbered starting from 1 from west to east) and 109 rows (numbered starting from 1 from north to south). Let (w, h) denote the square in the w-th column and the h-th row. The rover begins on the square (1, 1).

// The rover can be maneuvered around on the surface of the planet by sending it a program, which is a string of characters representing movements in the four cardinal directions. The robot executes each character of the string in order:

//    N: Move one unit north.
//    S: Move one unit south.
//    E: Move one unit east.
//    W: Move one unit west.

// There is also a special instruction X(Y), where X is a number between 2 and 9 inclusive and Y is a non-empty subprogram. This denotes that the robot should repeat the subprogram Y a total of X times. For example:

//    2(NWE) is equivalent to NWENWE.
//    3(S2(E)) is equivalent to SEESEESEE.
//    EEEE4(N)2(SS) is equivalent to EEEENNNNSSSS.

// Since the planet is a torus, the first and last columns are adjacent, so moving east from column 109 will move the rover to column 1 and moving south from row 109 will move the rover to row 1. Similarly, moving west from column 1 will move the rover to column 109 and moving north from row 1 will move the rover to row 109. Given a program that the robot will execute, determine the final position of the robot after it has finished all its movements. 

// Input

// The first line of the input gives the number of test cases, T. T lines follow. Each line contains a single string: the program sent to the rover.

// Output

// For each test case, output one line containing Case #x: w h, where x is the test case number (starting from 1) and w h is the final square (w, h) the rover finishes in.

// Limits

// Time limit: 10 seconds per test set.
// Memory limit: 1GB.
// 1 ≤ T ≤ 100.
// The string represents a valid program.
// The length of each program is between 1 and 2000 characters inclusive.

// 没有必要把string完整地decode出来，只需算出N, S, E, W各有几个就行
// 为避免overflow，需要每步mod

#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;

#define NUM 1000000000LL

vector<ll> parse(string s){
    vector<ll> arr(4, 0);
    unsigned int i = 0;
    int balance = 0;
    while(i < s.size()){
        if(isdigit(s[i])){
            unsigned int j = i + 2;
            balance += 1;
            while(j < s.size() && balance != 0){
                if(s[j] == ')'){
                    balance -= 1;
                }else if(s[j] == '('){
                    balance += 1;
                }
                ++j;
            }
            auto v = parse(s.substr(i + 2, j - i - 3));
            auto times = (ll)stoi(s.substr(i, 1));
            for(unsigned int t = 0; t < 4; ++t){
                ll dt = times * v[t] % NUM;
                arr[t] = (arr[t] + dt) % NUM;
            }
            i = j;
        }else{
            switch(s[i]){
                case 'N': arr[0] = (arr[0] + 1) % NUM; break;
                case 'S': arr[1] = (arr[1] + 1) % NUM; break;
                case 'E': arr[2] = (arr[2] + 1) % NUM; break;
                case 'W': arr[3] = (arr[3] + 1) % NUM; break;
            }
            ++i;
        }
    }
    return arr;
}

pair<ll, ll> move(string& s){
    auto parsed = parse(s);
    ll r = (NUM - parsed[0] + parsed[1]) % NUM;
    ll c = (NUM - parsed[3] + parsed[2]) % NUM;
    return make_pair(c, r);
}

int main(){
    int T;
    cin >> T;
    int t = 1;
    string s;
    while(T--){
        cin >> s;
        auto p = move(s);
        cout << "Case #" << t << ": " << p.first + 1 << " " << p.second + 1 << endl;
        ++t;
    }
    return 0;
}

// 4
// SSSEEE
// Case #1: 4 4
// N
// Case #2: 1 1000000000
// N3(S)N2(E)N
// Case #3: 3 1
// 2(3(NW)2(W2(EE)W))
// Case #4: 3 999999995
