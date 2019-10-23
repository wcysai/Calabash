#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 998244353
#define INV2 499122177
#define INV6 166374059
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
int getsum(ll x)
{
    x%=MOD;
    return 1LL*(x+1)*x%MOD*INV2%MOD;
}
int getsum(ll l,ll r)
{
    int res=getsum(r);
    dec(res,getsum(l-1));
    return res;
}
int getsum2(ll x)
{
    x%=MOD;
    return 1LL*x*(x+1)%MOD*(2*x+1)%MOD*INV6%MOD;
}
int getsum2(ll l,ll r)
{
    int res=getsum2(r);
    dec(res,getsum2(l-1));
    return res;
}
ll n;
int main()
{
    scanf("%lld",&n);
    int ans=0,a,b;
    for(a=2;1LL*a*a-1<=n;a++) add(ans,1LL*a*((1LL*a*a-a)%MOD)%MOD);
    add(ans,1LL*((n+1)%MOD)*getsum(a,n)%MOD);
    dec(ans,getsum2(a,n));
    for(int i=2;i<=40;i++)
    {
        for(int a=2;;a++)
        {
            ll s=1;
            for(int k=1;k<=i;k++) s*=a;
            if(s>n) break;
            add(ans,1LL*a*i%MOD*((min(n,s*a-1)-s+1)%MOD)%MOD);
        }
    }
    printf("%d\n",ans);
    return 0;
}
}
