#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
int n;
P a[MAXN];
bool cmp(P x,P y)
{
    if(x.S-x.F>0&&y.S-y.F>0) return x.F<y.F;
    if(x.S-x.F==0&&y.S-y.F==0) return x.F<y.F;
    if(x.S-x.F>=0||y.S-y.F>=0) return x.S-x.F>y.S-y.F;
    return max(x.F,x.F+y.F-x.S)<max(y.F,x.F+y.F-y.S);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lld%lld",&a[i].F,&a[i].S);
    sort(a+1,a+n+1,cmp);
    ll ans=0,cur=0;
    for(int i=1;i<=n;i++)
    {
        if(cur<a[i].F)
        {
            ans+=a[i].F-cur;
            cur=a[i].F;
        }
        cur-=a[i].F; cur+=a[i].S;
    }
    printf("%lld\n",ans);
    return 0;
}
