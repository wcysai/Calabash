#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll mod = 998244353;
ll power(ll x,ll y){
    ll res = 1;
    while (y){
        if (y & 1){
            res = res * x % mod;
        }
        y >>= 1;
        x = x * x % mod;
    }
    return res;
}
const int maxn = 3005;
ll ans[maxn];
int main(){
    ll n;
    ll inv_3 = power(3ll,mod-2);
    for (int i=1;i<maxn;i++){
        ans[i] = 1ll * i % mod * (i-1) % mod * inv_3 % mod;
    }
    for (int i=2;i<maxn;i++){
        ans[i] = (ans[i] +ans[i-1]) % mod;
    }
    for (int i=1;i<maxn;i++){
        ans[i] = ans[i] * power(i,mod-2) % mod;
    }
    while (cin>>n){
        cout<<ans[n]<<endl;
    }
    return 0;
}
