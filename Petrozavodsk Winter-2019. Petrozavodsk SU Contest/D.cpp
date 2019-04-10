#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
ll k;
bool check(int x)
{
    return k>=1LL*x*(x-1)/2&&k<=1LL*x*(x-1)/2+1LL*x*(n-x);
}
ll getans(int x)
{
    return 1LL*x*(x-1)/2+1LL*(n-x)*(n-x-1)/2;
}
int main()
{
    scanf("%d%lld",&n,&k);
    if(k>1LL*n*(n-1)/2) {puts("-1"); return 0;}
    ll ans=-INF;
    int l=-1,r=n;
    while(r-l>1)
    {
        int mid=(l+r)/2;
        if(1LL*mid*(mid-1)/2+1LL*mid*(n-mid)>=k) r=mid; else l=mid;
    } 
    if(check(r)) ans=max(ans,getans(r));
    l=0,r=n+1;
    while(r-l>1)
    {
        int mid=(l+r)/2;
        if(1LL*mid*(mid-1)/2<=k) l=mid; else r=mid;
    }
    if(check(l)) ans=max(ans,getans(l));
    printf("%lld\n",ans);
    return 0;
}
