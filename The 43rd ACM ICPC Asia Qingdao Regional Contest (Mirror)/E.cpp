#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef pair<int,int> P;
typedef long long ll;
ll T,n,m,a[MAXN],need[MAXN];
bool check(ll x)
{
    for(ll i=1;i<=n;i++) need[i]=(x+a[i]-1)/a[i];
    need[0]=0;
    int last=n+1;
    for(int i=n;i>=1;i--) if(need[i]) {last=i; break;}
    ll ans=0;
    for(ll i=0;i<=last;i++)
    {
        if(need[i]<need[i+1])
        {
            need[i+1]-=need[i]+1;
            ans+=2*need[i]+(i<last?1:0);
            if(ans>m) return false;
        }
        else
        {
            need[i+1]=0;
            ans+=2*need[i]+(i+1<last?1:0);
            if(ans>m) return false;
        }
    }
    return ans<=m;
}
int main()
{
    scanf("%lld",&T);
    while(T--)
    {
        scanf("%lld%lld",&n,&m);
        for(ll i=1;i<=n;i++) scanf("%lld",&a[i]);
        ll ans=0;
        ll l=0,r=INF+1;
        while(r-l>1)
        {
            ll mid=(l+r)/2;
            if(check(mid)) l=mid; else r=mid;
        }
        printf("%lld\n",l);
    }
    return 0;
}