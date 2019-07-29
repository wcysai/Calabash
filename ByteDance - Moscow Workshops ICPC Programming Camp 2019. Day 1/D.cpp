//
// Created by bytedance on 19-2-16.
//
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
const int maxn = 3000 + 100;
typedef long long ll;
typedef unsigned long long ULL;
ll dp[maxn][maxn];
int S[maxn];
const ll MOD = 1e9+9;
ll temp[maxn];
char s[maxn];
const ll Seed = 146527;
const ll Mod = 998244353;
ULL base[maxn];
ULL sum[maxn];

int LCP[3005][3005];

void prep(int n) {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            LCP[i][j] = -1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            if (LCP[i][j] != -1) continue;
            int k = 0;
            for (k = 0; s[i+k] == s[j+k]; k++);
            for (int kk = 0; kk <= k; kk++)
                LCP[i+kk][j+kk] = k-kk;
        }
    }
}

void init(){
    base[0] = 1;
    for (int i=1;i<maxn;i++){
        base[i] = base[i-1] * Seed % Mod;
    }
}
void init_hash(int n){
    sum[0] = 0;
    for (int i=1;i<=n;i++){
        sum[i] = sum[i-1] * Seed % Mod + s[i] - 'a' + 1;
        sum[i] %= Mod;
    }
}
inline ULL get_hash(int l,int r){
    return (sum[r] - sum[l-1] * base[r-l+1] % Mod + Mod)%Mod;
}
bool check(int st1,int st2,int len){
    ULL hash_val1 = get_hash(st1,st1+len-1);
    ULL hash_val2 = get_hash(st2,st2+len-1);
    return hash_val1 == hash_val2;
}
int lcp(int l1,int r1,int l2,int r2){
    int _lcp = LCP[l1][l2];
    return min(_lcp,r1-l1+1);
//    int r = min(r1-l1+1,r2-l2+1);
//    int l = 0;
//    while (r-l>1){
//        int mid = l + r >> 1;
//        if (check(l1,l2,mid)){
//            l = mid;
//        }else{
//            r = mid;
//        }
//    }
//    if (check(l1,l2,r))return r;
//    else return l;
}
void update(int l,int r,ll val){
    if (l>r)return;
    (temp[l] += val)%= MOD;
    (temp[r+1] -=val)%=MOD;
}
int main(){
    init();
    int Case = 1;
    while (scanf("%s",s+1)!= EOF && s[1]!= '-'){
        int n = strlen(s+1);
        prep(n);
        //init_hash(n);
        for (int i=1;i<=n;i++){
            for (int j=1;j<=n;j++){
                dp[i][j] = 0;
            }
        }
        for (int i=1;i<=n;i++){
            dp[1][i] = 1;
        }
        for (int j=1;j<n;j++){
            //memset(temp,0,sizeof temp);
            for (int i=0;i<=n;i++){
                temp[i] = 0;
            }
            for (int i=1;i<=j;i++){
                int _lcp = lcp(i,j,j+1,n);
                if (_lcp == j-i+1){
                    update(2*j-i+2,n,dp[i][j]);
                }else{
                    if (s[j+1+_lcp] > s[i+_lcp]){
                        update(j+1+_lcp,n,dp[i][j]);
                    }
                }
            }
            for (int i=1;i<=n;i++){
                temp[i] += temp[i-1];
                temp[i] = (temp[i] + MOD) % MOD;
            }
            for (int i=j+1;i<=n;i++){
                dp[j+1][i] += temp[i];
            }
        }
        ll ans = 0;
        for (int i=1;i<=n;i++){
            (ans += dp[i][n]) %= MOD;
        }
        printf("Case #%d: There are %lld ways.\n",Case++,ans);
    }
    return 0;
}
