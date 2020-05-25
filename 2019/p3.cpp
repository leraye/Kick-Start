// Kickstart Alarm

// Pay special attention to -b mod n and b ^ -1 mod n

#include <iostream>
#include <vector>
using namespace std;
#define MOD 1000000007
typedef long long ll;

ll modulo(int a, ll b, ll n){
    ll x=1, y=a; 
    while (b > 0) {
        if (b%2 == 1) {
            x = (x*y) % n; // multiplying with base
        }
        y = (y*y) % n; // squaring the base
        b /= 2;
    }
    return x % n;
}

ll powerCount(const vector<ll>& arr, int N, int K){
    ll ans = 0;
    vector<ll> powers(N + 1, 1);
    vector<ll> v;
    for(int i = 0; i < N; ++i){
        v.push_back(((N - i) * arr[i]) % MOD);
    }
    ll s = 0;
    for(auto it = v.rbegin(); it != v.rend(); ++it){
        s += *it;
        s %= MOD;
        *it = s;
    }
    powers[1] = K;
    for(int i = 2; i <= N; ++i){
        powers[i] = modulo(i, K + 1, MOD);
        powers[i] += MOD - i;
        powers[i] %= MOD;
        powers[i] *= modulo(i - 1, MOD - 2, MOD);
        powers[i] %= MOD;
    }
    
    for(int i = 1; i <= N; ++i){
        ans += (v[i - 1] * powers[i]) % MOD;
        ans %= MOD;
    }
    return ans;
}


int main(){
    int T;
    cin >> T;
    int t = 1;
    while(T--){
        int N, K;
        ll x1, y1, C, D, E1, E2, F;
        cin >> N >> K >> x1 >> y1 >> C >> D >> E1 >> E2 >> F;
        vector<ll> arr = {((x1 + y1) % F)};
        for(int i = 1; i < N; ++i){
            ll t = x1;
            x1 = (C * x1 + D * y1 + E1) % F;
            y1 = (D * t + C * y1 + E2) % F;
            arr.push_back((x1 + y1) % F);
        }
        cout << "Case #" << t << ": " << powerCount(arr, N, K) << endl;
        ++t;
    }
    return 0;
}
