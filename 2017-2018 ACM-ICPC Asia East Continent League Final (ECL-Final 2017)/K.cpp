//
// Created by calabash_boy on 18-5-24.
//
#include <bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll t,a,b,n;
ll num[MAXN],sum[MAXN];
int main()
{
    scanf("%I64d",&t);
    ll kase=0;
    while(t--)
    {
        kase++;
        scanf("%I64d%I64d%I64d",&a,&b,&n);
        for(ll i=1;i<=a;i++)
            scanf("%I64d",&num[i]);
        for(ll i=1;i<=a;i++)
            sum[i]=num[i]+sum[i-1];
        ll x=a,y=b;
        bool f=true;
        for(ll i=0;i<n;i++)
        {
            ll nx=lower_bound(sum+1,sum+a+1,x)-sum;
            ll ny=x-sum[nx-1];
            if(nx==x)
            {
                printf("Case #%I64d: %I64d-%I64d\n",kase,nx,ny);
                f=false;
                break;
            }
            x=nx;y=ny;
        }
        if(f) printf("Case #%I64d: %I64d-%I64d\n",kase,x,y);
    }
    return 0;
}
