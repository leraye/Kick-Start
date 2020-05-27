// Training

#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;

long coachingTime(vector<long>& arr, const int n, const int k){
    sort(arr.begin(), arr.end());
    long curr = 0;
    long ans = LONG_MAX;
    int i = 0;
    while(i < k){
        curr += arr[k - 1] - arr[i];
        ++i;
    }
    while(i <= n){
        ans = min(ans, curr);
        curr -= arr[i - 1] - arr[i - k];
        if(i < n){
            curr += (k - 1) * (arr[i] - arr[i - 1]);
        }
        ++i;
    }
    return ans;
}

int main(){
    int T;
    cin >> T;
    int t = 1;
    while(T--){
        int n, k;
        cin >> n >> k;
        vector<long> arr(n);
        for(int i = 0; i < n; ++i){
            cin >> arr[i];
        }
        cout << "Case #" << t << ": " << coachingTime(arr, n, k) << endl;
        ++t;
    }
    return 0;
}
