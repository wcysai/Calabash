#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll t;
ll n;
ll C(ll x)
{
    ll sum=0;
    ll t=1;
    while(t*2<=x) t=t*2;
    ll s=t*2-1;
    ll cur=t,last;
    for(ll now=1;t>0;now=last+1)
    {
        last=x/t;
        ll res=(now+last)*(last-now+1)/2;
        if((n-sum)/res<s) return n+1;
        sum+=s*res;
        t=t/2;s=s/2;
    }
    return sum;
}
ll calc(ll x)
{
    ll t=1,ans=0,cnt=1;
    while(t*2<=x) t=t*2,cnt++;
    ll cur=t,last=x/t;
    for(ll now=1;t>0;now=last+1)
    {
        last=x/t;
        ans+=cnt*(last-now+1);
        t=t/2;cnt--;
    }
    return ans;
}
int main()
{
    scanf("%lld",&t);
    while(t--)
    {
        scanf("%lld",&n);
        ll l=1,r=INF;
        while(r-l>1)
        {
            ll mid=(l+r)/2;
            if(C(mid)<=n) l=mid; else r=mid;
        }
        printf("%lld\n",calc(l)+(n-C(l))/(l+1));
    }
    return 0;
}
