#include<bits/stdc++.h>
#define MAXN 100005
#define INF 8000000000000000000LL
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
ll a,b,c,d,t;
ll mul_mod(ll a,ll b,ll p)
{
    ll s=0;
    while(b)
    {
        if(b&1) s=(s+a)%p;
        a=(a+a)%p;
        b>>=1;
    }
    return s;
}
P cal(ll a,ll b,ll c,ll d)
{
    //printf("%lld %lld %lld %lld\n",a,b,c,d);
    ll x=a/b+1;if(x*d<c) return P(x,1);
    if(!a) return P(1,d/c+1);
    if(a<=b&&c<=d)
    {
        P t=cal(d,c,b,a);
        swap(t.F,t.S); return t;
    }
    x=a/b;P t=cal(a-b*x,b,c-d*x,d);
    t.F+=t.S*x;return t;
}
int T;
ll x,p;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld%lld",&p,&x);
        b=d=p;
        a=x-1; c=x;
        P ans=cal(a,b,c,d);
        printf("%lld/%lld\n",mul_mod(x,ans.S,p),ans.S);
    }
    return 0;
}
