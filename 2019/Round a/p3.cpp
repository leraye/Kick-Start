// Contention

// Idea came from Mahmoudian
// Code is adapted from https://www.cnblogs.com/Patt/p/11618433.html

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <climits>

using namespace std;

typedef pair<int, int> P;

bool compare_Pairs(const P& p1, const P& p2){
    if(p1.first < p2.first){
        return true;
    }else if(p1.first == p2.first){
        return p1.second > p2.second;
    }
    return false;
}

bool check(const vector<int>& v1, const vector<int>& v2, const int q, const int k){
    vector<int> copy_v1(v1.begin(), v1.end());
    for(int i = 0; i < q; ++i){
        int l = copy_v1[i];
        int r = v2[i];
        int allowed_after = r;
        int cnt = 0;
        for(int j = i + 1; j < q; ++j){
            if(v1[j] >= r)
                break;
            if(v2[j] <= r){
                if(v1[j] <= l){
                    l = max(l, v2[j]);
                }else{
                    cnt += v1[j] - l;
                    l = max(l, v2[j]);
                    if(cnt >= k){
                        allowed_after = v1[j] - (cnt - k);
                        break;
                    }
                }
            }
        }
        if(cnt < k){
            cnt += r - l;
            if(cnt < k)
                return false;
            allowed_after = r - (cnt - k);
        }
        for(int j = i + 1; j < q; ++j){
            if(v1[j] >= allowed_after)
                break;
            if(v2[j] > r){
                copy_v1[j] = max(copy_v1[j], r);
            }
        }
    }
    return true;
}

int binary_Search(const vector<int>& v1, const vector<int>& v2, const int q){
    int k = INT_MIN;
    int l = 0;
    int r = INT_MAX;
    for(int i = 0; i < q; ++i)
        r = min(r, v2[i] - v1[i]);
    while(l <= r){
        int m = l + (r - l) / 2;
        if(check(v1, v2, q, m)){
            k = max(k, m);
            l = m + 1;
        }else{
            r = m - 1;
        }
    }
    return k;
}

int main(){
    int T;
    cin >> T;
    int t = 1;
    while(T--){
        int n, q;
        cin >> n >> q;
        vector<int> xl(q);
        vector<int> xr(q);
        vector<P> intervals;
        for(int i = 0; i < q; ++i){
            cin >> xl[i] >> xr[i];
            --xl[i];
            intervals.push_back(make_pair(xl[i], xr[i]));
        }
        sort(intervals.begin(), intervals.end(), compare_Pairs);
        for(int i = 0; i < q; ++i){
            xl[i] = intervals[i].first;
            xr[i] = intervals[i].second;
        }
        cout << "Case #" << t << ": " << binary_Search(xl, xr, q) << endl;
        ++t;
    }
    return 0;
}
