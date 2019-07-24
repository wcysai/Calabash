#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e6 + 3;
const int maxn = mod + 5;
int fac[maxn];
int main(){
    fac[0] = 1;
    for (int i=1;i<mod;i++){
        fac[i] = 1ll * fac[i-1] * i % mod;
    }
    int n;
    while (cin>>n){
        if (n >= mod){
            cout<<0<<endl;
        }else{
            cout<<fac[n]<<endl;
        }
    }
    return 0;
}
