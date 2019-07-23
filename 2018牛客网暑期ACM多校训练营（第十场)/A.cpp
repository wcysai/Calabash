/*************************************************************************
    > File Name: A.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com
    > Created Time: 2018-08-19 12:08:54
 ************************************************************************/
 
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,m,a[MAXN],sum[MAXN];
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
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        for(int i=1;i<=n;i++)
        {
            sum[i]=sum[i-1]+a[i];
            if(sum[i]>=MOD) sum[i]-=MOD;
        }
        int t,l,r;
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d%d",&t,&l,&r);if(t==1) continue;
            int ans=sum[r]-sum[l-1];
            if(ans<0) ans+=MOD;
            ans=1LL*ans*pow_mod(2,1LL*n*m%(MOD-1))%MOD;
            printf("%d\n",ans);
        }
    }
    return 0;
}
