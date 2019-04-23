#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e4+100;
const int maxm = 100+5;

typedef unsigned long long ULL;
typedef long long ll;

int ok_prefix[maxn][maxm];
int ok_suffix[maxn][maxm];
ll sum_prefix[maxn][maxm];
ll sum_suffix[maxn][maxm];

ll ans_prefix[maxn];
ll ans_suffix[maxn];

int n,m,k;

char s[maxn];
char t[maxm];
struct Hash{
    ULL base[maxn];
    ULL SEED,MOD;
    ULL sum[maxn];
    void setSeed(ULL seed){
        SEED = seed;
    }
    void setMod(ULL mod){
        MOD = mod;
    }
    void init(char *S, int n){
        base[0] = 1;
        for (int i=1;i<maxn;i++){
            base[i] = base[i-1] * SEED % MOD;
        }
        sum[0] = 0;
        for (int i=1;i<=n;i++){
           sum[i] = (sum[i-1] * SEED % MOD + S[i] ) % MOD;
        }
    }
    ULL get(int l,int r){
        return (sum[r] - sum[l-1] * base[r - l + 1] % MOD + MOD) % MOD;
    }
}hash_s,hash_t;
bool check(int l,int r,int L,int R){
    ULL s_val = hash_s.get(l,r);
    ULL t_val = hash_t.get(L,R);
    return s_val == t_val;
}
void prework(){
    const ULL seed = 146527;
    const ULL mod = 998244353;
    hash_s.setSeed(seed);
    hash_t.setSeed(seed);
    hash_s.setMod(mod);
    hash_t.setMod(mod);
    hash_s.init(s,n);
    hash_t.init(t,m);
    //prefix_work
    for (int i=1;i<=n;i++){
        int len = min(i,m);
        for (int l = 1;l <=len;l++){
            if (check(i - l + 1,i,1,l)){
                ok_prefix[i][l] = 1;
            }else{
                ok_prefix[i][l] = 0;
            }
        }
        for (int l=1;l<=m;l++){
            sum_prefix[i][l] = sum_prefix[i-1][l] + ok_prefix[i][l];
        }
        ans_prefix[i] = ans_prefix[i-1] + sum_prefix[i][m];
    }
    //suffix_work
    for (int i=n;i>=1;i--){
        int len = min(n+1 - i,m);
        for (int l = 1;l <= len; l ++){
            if (check(i,i+l - 1,m - l + 1,m)){
                ok_suffix[i][l] = 1;
            }else{
                ok_suffix[i][l] = 0;
            }
        }
        for (int l=1;l<=m;l++){
            sum_suffix[i][l] = sum_suffix[i+1][l] + ok_suffix[i][l];
        }
        ans_suffix[i] = ans_suffix[i+1] + sum_suffix[i][m];
    }
}
ll calc(int l,int r){
    ll ans = 1ll * ans_prefix[l] * (n+1-r);
    ans += 1ll * ans_suffix[r] * l;
    for (int i=1;i<m;i++){
        ans += 1ll * sum_prefix[l][i] * (sum_suffix[r][m-i]);
    }
    return ans;
}
int main(){
    scanf("%d%d%d",&n,&m,&k);
    scanf("%s",s+1);
    scanf("%s",t+1);
    prework();
    for (int i=0;i<k;i++){
        int l,r;
        scanf("%d%d",&l,&r);
        printf("%lld\n",calc(l,r));
    }
    return 0;
}
