//
// Created by sy-chen on 18-5-20.
//
#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const int maxn = 1e6+100;
const LL BAS = 19260817;
const LL MOD = 1e9+9;
ULL bas[maxn];
ULL sum[maxn];
int n,k,p;
int a[maxn];
void init(){
    bas[0]=1;
    for (int i=1;i<maxn;i++){
        bas[i] = (bas[i-1]*BAS)%MOD;
    }
}
void input(){
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
        scanf("%d",a+i);
        sum[i] = (sum[i-1]*BAS%MOD+a[i])%MOD;
    }
}
void work(int pp){
    ULL s = (sum[n]-sum[n-pp]*bas[pp]%MOD+MOD)%MOD;
    int i=n;
    while (i-pp>=0){
        ULL ss = (sum[i]-sum[i-pp]*bas[pp]%MOD+MOD)%MOD;
        if (ss!=s)break;
        i-=pp;
    }
    int l=0,r=min(pp,i);
    while (r-l>1){
        int mid = l+r >>1;
        ULL s1 = (sum[i]-sum[i-mid]*bas[mid]%MOD+MOD)%MOD;
        ULL s2 = (sum[n]-sum[n-mid]*bas[mid]%MOD+MOD)%MOD;
        if (s1==s2){
            l = mid;
        }else{
            r = mid;
        }
    }
    ULL s1 = (sum[i]-sum[i-r]*bas[r]%MOD+MOD)%MOD;
    ULL s2 = (sum[n]-sum[n-r]*bas[r]%MOD+MOD)%MOD;
    if (s1==s2)i-=r;
    else i-=l;
    int kk =i;
    if (kk+pp<k+p){
        k = kk;
        p = pp;
    }
}
void solve(){
    k = p = maxn;
    for (int pp = 1;pp<=n;pp++){
        if (pp>=n+p)break;
        work(pp);
    }
    printf("%d %d",k,p);
}
int main(){
    init();
    input();
    solve();
    return 0;
}
