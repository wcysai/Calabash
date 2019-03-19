#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T;
ll p,q,n;
ll cal(ll a,ll b,ll c,ll n)
{
    if(!a) return 0;
    if(a>=c||b>=c)
    {
        ll x=cal(a%c,b%c,c,n);
        return (a/c*n*(n+1)/2+b/c*(n+1)+x);
    }
    ll m=(a*n+b)/c;
    ll x=cal(c,c-b-1,a,m-1);
    return n*m-x;
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld%lld%lld",&p,&q,&n);
        printf("%lld\n",p*n*(n+1)/2-q*cal(p,0,q,n));
    }
    return 0;
}
