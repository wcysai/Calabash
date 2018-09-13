//
// Created by sy-chen on 18-6-7.
//
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
ll n;
ll a[MAXN];
int main()
{
    scanf("%lld",&n);
    ll s=0;
    for(ll i=0;i<n;i++) {
        scanf("%lld", &a[i]);
        s += a[i];
    }
    sort(a,a+n);
    reverse(a,a+n);
    if(n<=3)
    {
        printf("%lld\n",s-n*(n-1)/2);
        return 0;
    }
    if(n==4)
    {
        ll ans=0;
        if(a[0]==2) ans=4;
        else ans=a[0]+max(a[1]-1,0LL)+max(a[2]-2,0LL)+max(a[3]-3,0LL);
        printf("%lld\n",ans);
    }
    if(n==5)
    {
        ll ans=0;
        if(a[0]==2) ans=4;
        else if(a[0]>=4)
        {
            if(a[1]>=4) ans=a[0]+max(a[1]-1,0LL)+max(a[2]-2,0LL)+max(a[3]-3,0LL)+max(a[4]-4,0LL);
            else if(a[1]==3)
            {
                if(a[2]==2) ans=6;
                else if(a[3]==2) ans=7;
                else if(a[4]==2) ans=7;
                else ans=8;
                ans=ans+a[0]-4;
            }
            else ans=a[0]+1;
        }
        else
        {
            if(a[1]==2) ans=5;
            else if(a[2]==2) ans=5;
            else if(a[3]==2) ans=6;
            else if(a[4]==2) ans=6;
            else ans=7;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
