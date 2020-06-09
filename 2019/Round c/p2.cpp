// Circuit Board

// Problem

/*
 Arsh recently found an old rectangular circuit board that he would like to recycle. The circuit board has R rows and C columns of squares.

Each square of the circuit board has a thickness, measured in millimetres. The square in the r-th row and c-th column has thickness Vr,c. A circuit board is good if in each row, the difference between the thickest square and the least thick square is no greater than K.

Since the original circuit board might not be good, Arsh would like to find a good subcircuit board. A subcircuit board can be obtained by choosing an axis-aligned subrectangle from the original board and taking the squares in that subrectangle. Arsh would like your help in finding the number of squares in the largest good subrectangle of his original board. 
*/

// Input

/*
 The first line of the input gives the number of test cases, T. T test cases follow. Each test case begins with one line containing three integers R, C and K, the number of rows, the number of columns, and the maximum difference in thickness allowed in each row.

Then, there are R more lines containing C integers each. The c-th integer on the r-th line is Vr, c, the thickness of the square in the r-th row and c-th column. 
*/

// Output

/*
For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the maximum number of squares in a good subrectangle. 
*/

// Limits

/*
1 ≤ T ≤ 50.
1 ≤ R ≤ 300.
1 ≤ C ≤ 300.
0 ≤ Vi, j ≤ 103 for all i, j.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <deque>
#include <stack>

using namespace std;

int largestRectangleArea(vector<int>& heights, const int m){
    heights.push_back(numeric_limits<int>::min());
    stack<int> stk;
    stk.push(-1);
    int area = numeric_limits<int>::min();
    for(int i = 0; i <= m; ++i){
        int h = heights[i];
        while(stk.top() >= 0 && h < heights[stk.top()]){
            int prev = heights[stk.top()];
            stk.pop();
            area = max(area, prev * (i - stk.top() - 1));
        }
        stk.push(i);
    }
    return area;
}

vector<int> RMQ(const vector<int>& arr, const int n, const int k){
    deque<int> max_vector;
    deque<int> min_vector;
    vector<int> ret(n, 0);
    int prev = -1;
    for(int j = 0; j < n; ++j){
        while(!max_vector.empty() && arr[j] > arr[max_vector.back()]){
            max_vector.pop_back();
        }
        max_vector.push_back(j);
        while(!min_vector.empty() && arr[j] < arr[min_vector.back()]){
            min_vector.pop_back();
        }
        min_vector.push_back(j);
        while(arr[max_vector.front()] - arr[min_vector.front()] > k){
            if(max_vector.front() > min_vector.front()){
                prev = min_vector.front();
                min_vector.pop_front();
            }else{
                prev = max_vector.front();
                max_vector.pop_front();
            }
        }
        ret[j] = j - prev;
    }
    return ret;
}

int area(vector<vector<int>>& arr, const int m, const int n, const int k){
    vector<vector<int>> table;
    for(int i = 0; i < m; ++i){
        auto row = RMQ(arr[i], n, k);
        table.push_back(row);
    }
    
    int area = numeric_limits<int>::min();
    for(int j = 0; j < n; ++j){
        vector<int> heights;
        for(int i = 0; i < m; ++i){
            heights.push_back(table[i][j]);
        }
        area = max(area, largestRectangleArea(heights, m));
    }
    return area;
}

int main(){
    int T;
    cin >> T;
    int t = 1;
    while(T--){
        int r, c, k;
        cin >> r >> c >> k;
        vector<vector<int>> arr;
        for(int i = 0; i < r; ++i){
            vector<int> row(c);
            for(int j = 0; j < c; ++j)
                cin >> row[j];
            arr.push_back(row);
        }
        cout << "Case #" << t << ": " << area(arr, r, c, k) << endl;
        ++t;
    }
    return 0;
}

// Test Cases

/*
3
1 4 2
3 1 3 3
Case #1: 4
3 3 2
0 5 0
8 12 3
7 10 1
Case #2: 3
4 4 8
20 10 20 10
10 4 5 20
20 5 4 10
10 20 10 20
Case #3: 4
*/
