// Mural

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int maxBeauty(const vector<int>& arr, int n){
    int m = n / 2;
    if(n & 1)
        ++m;
    int curr = 0;
    int ans = 0;
    for(int i = 0; i <= n; ++i){
        if(i >= m){
            ans = max(ans, curr);
            curr -= arr[i - m];
        }
        if(i < n)
            curr += arr[i];
    }
    return ans;
}

int main(){
    int T;
    cin >> T;
    int t = 1;
    while(T--){
        int n;
        cin >> n;
        vector<int> arr;
        string s;
        cin >> s;
        for(int i = 0; i < n; ++i){
            arr.push_back(stoi(s.substr(i, 1)));
        }
        cout << "Case #" << t << ": " << maxBeauty(arr, n) << endl;
        ++t;
    }
    return 0;
}
