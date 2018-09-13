//
// Created by calabash_boy on 18-5-24.
//
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,k,inv[MAXN];
int pow_mod(int a,int i)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
int main()
{
    scanf("%d",&T);
    for(int i=1;i<=100000;i++)
        inv[i]=pow_mod(i,MOD-2);
    int kase=0;
    while(T--)
    {
        kase++;
        scanf("%d%d",&n,&k);
        int ans=pow_mod(2,n);
        int now=1;
        for(int i=0;i<=k-1;i++)
        {
            ans=(ans-now+MOD)%MOD;
            now=1LL*now*inv[i+1]%MOD;
            now=1LL*now*(n-i)%MOD;
        }
        printf("Case #%d: %d\n",kase,ans);
    }
    return 0;
}
