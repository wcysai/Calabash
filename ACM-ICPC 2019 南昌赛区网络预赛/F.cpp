#include<bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 100;
typedef long long ll;
const ll mod = 998244353;
ll powmod(ll x,ll y){
    ll res = 1;
    while (y){
        if (y&1){
            res = res * x % mod;
        }
        x = x * x % mod;
        y>>= 1;
    }
    return res;
}
ll ans;
const ll inv26 = powmod(26,mod-2);
ll powinv[maxn];
char s[maxn];int n,m,k,l;
// length = i value.
ll value[maxn];
struct Suffix_Automaton{
    //basic
    int nxt[maxn*2][26],fa[maxn*2],l[maxn*2];
    int last,cnt;
    Suffix_Automaton(){ clear(); }
    void clear(){
        last =cnt=1;
        fa[1]=l[1]=0;
        memset(nxt[1],0,sizeof nxt[1]);
    }
    void init(char *s){
        while (*s){
            add(*s-'a');s++;
        }
    }
    void add(int c){
        int p = last;
        int np = ++cnt;
        memset(nxt[cnt],0,sizeof nxt[cnt]);
        l[np] = l[p]+1;last = np;
        while (p&&!nxt[p][c])nxt[p][c] = np,p = fa[p];
        if (!p)fa[np]=1;
        else{
            int q = nxt[p][c];
            if (l[q]==l[p]+1)fa[np] =q;
            else{
                int nq = ++ cnt;
                l[nq] = l[p]+1;
                memcpy(nxt[nq],nxt[q],sizeof (nxt[q]));
                fa[nq] =fa[q];fa[np] = fa[q] =nq;
                while (nxt[p][c]==q)nxt[p][c] =nq,p = fa[p];
            }
        }
        int L,R;

        tie(L,R) =  make_pair(l[fa[last]] + 1,l[last]);
       // cerr<<L<<" "<<R<<endl;
        (ans += (value[R] - value[L-1] + mod)%mod ) %= mod;
    }
}sam;
ll a[maxn];
inline ll calc(ll x){
    ll res = 0;
    ll xpow = 1;
    for (int i=0;i<=k;i++){
        (res += xpow * a[i] % mod) %= mod;
        xpow = xpow * x % mod;
    }
    return res;
}
void solve(){
    sam.clear();
    scanf("%d%d%d%d",&l,&k,&n,&m);
    ans = 0;
    scanf("%s",s+1);
    for (int i=0;i<=k;i++){
        scanf("%lld",a+i);
    }
    for (int i=1;i<= l + m;i ++){
        value[i] = calc(i);
        int cnt = max(0,n - i + 1);
        value[i] = cnt * powinv[i] % mod * value[i] % mod;
      //  cerr<<"value "<<i<<" : "<<value[i]<<endl;
        value[i] = (value[i-1] + value[i]) % mod;
    }

    for (int i=1;i<=l;i++){
        sam.add(s[i] - 'a');
    }
    printf("%lld\n",ans);
    while (m--){
        static char temp[5];
        scanf("%s",temp);
        int ch = temp[0] - 'a';
        sam.add(ch);
        printf("%lld\n",ans);
    }

}
int main(){
    powinv[0] = 1;
    for (int i=1;i<maxn;i++){
        powinv[i] = powinv[i-1] * inv26 % mod;
    }
    int T;
    scanf("%d",&T);
    while (T--){
        solve();
    }

    return 0;
}
