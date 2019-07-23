#include<bits/stdc++.h>
#define MAXN 25
#define MAXP 1000005
#define INF 1000000000000000000LL
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll p,N;
ll a[MAXN];
ll ans;
ll pow_mod(ll a,ll i,ll m)
{
    ll s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%m;
        a=1LL*a*a%m;
        i>>=1;
    }
    return s;
}
int main()
{
    scanf("%lld%lld",&p,&N);
    for(ll i=N;i>=0;i--) scanf("%lld",&a[i]);
    ans=INF;
    for(ll i=0;i<p;i++)
    {
        ll rem=0;
        __int128 rem2=0;
        ll cur=1;
        __int128 cur2=1;
        for(ll j=0;j<=N;j++)
        {
            rem=(rem+1LL*cur*a[j])%p;
            if(rem<0) rem+=p;
            rem2=(rem2+cur2*a[j])%(1LL*p*p);
            if(rem2<0) rem2+=1LL*p*p;
            cur=1LL*cur*i%p;
            cur2=cur2*i%(1LL*p*p);
        }
        if(rem!=0) continue;
        rem2/=p;
        if(rem2==0)
        {
            ans=min(ans,1LL*i);
            continue;
        }
        ll rem3=0;
        cur=1;
        for(ll j=1;j<=N;j++)
        {
            rem3=(rem3+1LL*cur*a[j]%p*j)%p;
            if(rem3<0) rem3+=p;
            cur=1LL*cur*i%p;
        }
        if(rem3==0) continue;
        ll need=1LL*(p-(int)rem2)*pow_mod(rem3,p-2,p)%p;
        ans=min(ans,1LL*need*p+i);
    }
    if(ans==INF) puts("-1"); else printf("%lld\n",ans);
    return 0;
}
