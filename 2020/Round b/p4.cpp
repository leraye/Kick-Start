// Wandering Robot

// Problem

// Jemma is competing in a robotics competition. The challenge for today is to build a robot that can navigate around a hole in the arena.

// The arena is a grid of squares containing W columns (numbered 1 to W from left to right) and H rows (numbered 1 to H from top to bottom). The square in the x-th column and y-th row is denoted (x, y). The robot begins in the top left square (1,1) and must navigate to the bottom right square (W, H).

// A rectangular subgrid of squares has been cut out of the grid. More specifically, all the squares that are in the rectangle with top-left square (L, U) and bottom-right square (R, D) have been removed.

// Jemma did not have much time to program her robot, so it follows a very simple algorithm:

//    If the robot is in the rightmost column, it will always move to the square directly below it. Otherwise,
//    If the robot is in the bottommost row, it will always move to the square directly right of it. Otherwise,
//    The robot will randomly choose to either move to the square directly to the right, or to the square directly below it with equal probability.

// Jemma passes the challenge if her robot avoids falling into the hole and makes it to the square (W, H). What is the probability she passes the challenge?

// Input

// The first line of the input gives the number of test cases, T. T test cases follow. Each test case consists of a single line containing W, H, L, U, R and D.

// Output

// For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is a real number between 0 and 1 inclusive, the probability that Jemma passes the challenge.

// y will be considered correct if it is within an absolute or relative error of 10-5 of the correct answer. See the FAQ for an explanation of what that means, and what formats of real numbers we accept.

// Limits

// Time limit: 15 seconds per test set.
// Memory limit: 1GB.
// 1 ≤ T ≤ 100.
// 1 ≤ U ≤ D ≤ H.
// 1 ≤ L ≤ R ≤ W.
// Neither the top-left nor bottom-right squares will be missing.

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

double prob(int W, int H, int L, int U, int R, int D){
    vector<double> logfrac(W + H + 1, 0.0);
    for(int i = 1; i <= W + H; ++i){
        logfrac[i] = logfrac[i - 1] + log(i);
    }
    double p = 0.0;
    int r = R + 1;
    int u = U - 1;
    while(r <= W && u >= 1){
        if(r < W){
            p += exp(logfrac[r + u - 2] - logfrac[r - 1] - logfrac[u - 1] - (r + u - 2) * log(2.0));
        }else{
            p += exp((W - 1) * log(0.5));
            for(int c = 1; c <= u - 1; ++c){
                double lp = logfrac[W - 2 + c] - logfrac[c] - logfrac[W - 2] - (W - 2 + c) * log(2.0);
                lp += log(0.5);
                p += exp(lp);
            }
        }
        ++r;
        --u;
    }
    int l = L - 1;
    int d = D + 1;
    while(l >= 1 && d <= H){
        if(d < H){
            p += exp(logfrac[l + d - 2] - logfrac[l - 1] - logfrac[d - 1] - (l + d - 2) * log(2.0));
        }else{
            p += exp((H - 1) * log(0.5));
            for(int c = 1; c <= l - 1; ++c){
                double lp = logfrac[H - 2 + c] - logfrac[c] - logfrac[H - 2] - (H - 2 + c) * log(2.0);
                lp += log(0.5);
                p += exp(lp);
            }
        }
        --l;
        ++d;
    }
    return p;
}

int main(){
    int T;
    cin >> T;
    int t = 1;
    while(T--){
        int W, H, L, U, R, D;
        cin >> W >> H >> L >> U >> R >> D;
        cout << "Case #" << t << ": " << prob(W, H, L, U, R, D) << endl;
        ++t;
    }
    return 0;
}

// 4
// 3 3 2 2 2 2
// Case #1: 0.5
// 5 3 1 2 4 2
// Case #2: 0.0625
// 1 10 1 3 1 5
// Case #3: 0.0
// 6 4 1 3 3 4
// Case #4: 0.3125
