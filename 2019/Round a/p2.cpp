// Parcels

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <queue>
#include <utility>
#include <cstdlib>

using namespace std;

typedef pair<int, int> COORD;

void bfs(vector<string>& map, vector<vector<int>>& dist, int m, int n){
    queue<COORD> q;
    vector<vector<bool>> visited;
    for(int i = 0; i < m; ++i){
        vector<bool> row(n, false);
        for(int j = 0; j < n; ++j){
            if(map[i][j] == '1'){
                q.push(make_pair(i, j));
                row[j] = true;
                dist[i][j] = 0;
            }
        }
        visited.push_back(row);
    }
    vector<COORD> dirs = {make_pair(0, 1), make_pair(0, -1), make_pair(1, 0), make_pair(-1, 0)};
    while(!q.empty()){
        auto p = q.front();
        q.pop();
        for(auto dt : dirs){
            int i = p.first + dt.first;
            int j = p.second + dt.second;
            if(i >= 0 && i < m && j >= 0 && j < n && !visited[i][j]){
                dist[i][j] = dist[p.first][p.second] + 1;
                q.push(make_pair(i, j));
                visited[i][j] = true;
            }
        }
    }
}

bool distance(const vector<vector<int>>& dist, const int MAX_ADD, const int MIN_ADD, const int MAX_DIFF, const int MIN_DIFF, const int m, const int n, const int K){
    int d;
    for(int i = 0; i < m; ++i){
        for(int j = 0; j < n; ++j){
            if(dist[i][j] > 0){
                d = max(abs(MAX_ADD - (i + j)), abs(MIN_ADD - (i + j)));
                d = max(d, max(abs(MAX_DIFF - (i - j)), abs(MIN_DIFF - (i - j))));
                if(d <= K){
                    return true;
                }
            }
        }
    }
    return false;
}

int binarySearch(const vector<vector<int>>& dist, int m, int n){
    int l = 0;
    int r = m + n;
    
    int ans = INT_MAX;
    int MAX_ADD = INT_MIN;
    int MIN_ADD = INT_MAX;
    int MAX_DIFF = INT_MIN;
    int MIN_DIFF = INT_MAX;
    while(l <= r){
        int mid = l + (r - l) / 2;
        bool found = false;
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                if(dist[i][j] > mid){
                    MAX_ADD = max(MAX_ADD, i + j);
                    MIN_ADD = min(MIN_ADD, i + j);
                    MAX_DIFF = max(MAX_DIFF, i - j);
                    MIN_DIFF = min(MIN_DIFF, i - j);
                    found = true;
                }
            }
        }
        if(!found || distance(dist, MAX_ADD, MIN_ADD, MAX_DIFF, MIN_DIFF, m, n, mid)){
            ans = min(ans, mid);
            r = mid - 1;
        }else{
            l = mid + 1;
        }
        MAX_ADD = INT_MIN;
        MIN_ADD = INT_MAX;
        MAX_DIFF = INT_MIN;
        MIN_DIFF = INT_MAX;
    }
    return ans;
}


int minDistance(vector<string>& map, int m, int n){
    vector<vector<int>> dist;
    for(int i = 0; i < m; ++i){
        vector<int> row(n, INT_MAX);
        dist.push_back(row);
    }
    bfs(map, dist, m, n);
    return binarySearch(dist, m, n);
}

int main(){
    int T;
    cin >> T;
    int t = 1;
    while(T--){
        int m, n;
        cin >> m >> n;
        vector<string> map;
        for(int i = 0; i < m; ++i){
            string s;
            cin >> s;
            map.push_back(s);
        }
        cout << "Case #" << t << ": " << minDistance(map, m, n) << endl;
        ++t;
    }
    return 0;
}
