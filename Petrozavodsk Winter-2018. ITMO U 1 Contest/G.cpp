#include<bits/stdc++.h>
#define MAXN 1000005
#define MAXM 1000005
#define INF 1000000000000000000LL
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll n,c;
ll a[MAXN];
vector<ll> v[MAXN];
ll d[MAXN],de[MAXN];
void add_d(ll st,ll ed,ll type)
{
    if(st>ed) return;
    if(type==0)
    {
        ll num=ed-st+1;
        d[st]+=1;
        d[ed+1]-=num+1;
        d[ed+2]+=num;
    } else
    {
        ll num=ed-st+1;
        d[st]+=num;
        d[st+1]-=num+1;
        d[ed+2]+=1;
    }
}
int main()
{
    scanf("%lld%lld",&n,&c);
    for(ll i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
        v[a[i]].push_back(i);
    }
    for(ll i=1;i<=c;i++)
    {
        ll last=-1;
        for(auto it:v[i])
        {
            if(last==-1) add_d(1,it-1,1);
            else
            {
                ll mid=(it+last)/2;
                add_d(last+1,mid,0);
                add_d(mid+1,it-1,1);
            }
            last=it;
        }
        if(last!=-1) add_d(last+1,n,0);
        /*for(ll i=1;i<=n;i++) printf("%lld%c",d[i],i==n?'\n':' ');
        for(ll i=1;i<=n;i++) de[i]=de[i-1]+d[i];
        for(ll i=2;i<=n;i++) de[i]=de[i-1]+de[i];
        for(ll i=1;i<=n;i++) printf("%lld%c",de[i],i==n?'\n':' ');*/
    }
    for(ll i=1;i<=n;i++) d[i]+=d[i-1];
    for(ll i=1;i<=n;i++) d[i]+=d[i-1];
    //for(ll i=1;i<=n;i++) printf("%lld\n",d[i]);
    ll ans=INF;
    for(ll i=1;i<=n;i++) ans=min(ans,d[i]);
    ll rem=c;
    ll g=__gcd(ans,rem);ans/=g;rem/=g;
    printf("%lld/%lld\n",ans,rem);
    return 0;
}
