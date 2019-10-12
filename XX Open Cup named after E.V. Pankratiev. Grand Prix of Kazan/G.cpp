#include <bits/stdc++.h>
using namespace std;
#define int ll
typedef long long ll;
const ll mod = 998244353;
const int maxn = 3e5 + 100;
char s[maxn];
int inv[maxn];
int fac[maxn];
int n;
int powmod(ll x,ll y){
    int res = 1;
    while (y){
        if (y & 1) res = res * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return res;
}
int C(int x,int y){
    if (y > x) return 0;
    return 1ll * fac[x] * inv[y] % mod * inv[x-y] % mod;
}

int gao(int l, int r) {
    int ans = 0;
    for (int x = l;x <= r;x ++){
        int L = x + ( n - r - 1);
        int R = x + (n - x - 1);
        ans = (ans + C(R + 1,x + 1) - C(L ,x+1) + mod)% mod;
    }

    return ans;
}

ll gao2(int l, int r) {
    ll ans = C(l + n-r, l)*(r-l)%mod;
    if (l) for (int i = l+1; i<r; i++) ans += C((l-1)+(n-i), l-1)*(i-l)%mod; // pref
    if (r<n) for (int i=l+1; i<r; i++) ans += C((n-r-1)+i, n-r-1)*(r-i)%mod; // suf
    return ans;
}

signed main(){
    scanf("%s",s);
    n = strlen(s);
    fac[0] = 1;
    for (int i=1;i<maxn;i++)fac[i] = fac[i-1] * i % mod;
    inv[maxn-1] = powmod(fac[maxn-1],mod-2);
    for (int i = maxn-2; i >=0;i--)inv[i] = inv[i+1] * (i+1) % mod;
    assert(inv[1] == 1);
    ll ans = powmod(2, n) - 1;
    int ptr = 0, rptr = 0;
    while (ptr < n) {
        while (s[rptr] == s[ptr]) rptr++;

        int len = rptr - ptr;
        if (len > 1){
            ans = (ans - gao(ptr,rptr-1) + mod ) % mod;
            ans = (ans + gao2(ptr, rptr)) % mod;
        }
        ptr = rptr;
    }
    cout<<ans<<endl;

    return 0;
}

