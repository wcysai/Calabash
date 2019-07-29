#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 10000005
#define MAXM 100005
#define MAXK 105
#define INF 1000000000
#define MOD 1000000007
#define INV 250000002
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
bool is_prime[MAXN];
int cnt,mmiu[MAXN],prime[MAXN];
int T;
ll n,m;
int k,f[MAXM],g[MAXM];
int miuf[MAXN],miug[MAXM];
int pf[MAXM];
unordered_map<ll,int> mp;
unordered_map<ll,int> mp2;
vector<int>poly;
int dif[MAXM];
int inv[MAXM];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}

int p[MAXM];
int pow_mod(int a,int i)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
void getpoly()
{
    for(int i=0;i<=k;i++) dif[i]=pow_mod(i,k);
    poly.push_back(dif[0]);
    for(int i=1;i<=k;i++)
    {
        for(int j=0;j<=k-i;j++)
        {
            dif[j]=dif[j+1]-dif[j];
            if(dif[j]<0) dif[j]+=MOD;
        }
        poly.push_back(dif[0]);
    }
}
int getsum(ll x)
{
    if(x+1>=MOD) return 0;
    int res=x+1,ans=0;
    for(int i=0;i<=k;i++)
    {
        add(ans,1LL*res*poly[i]%MOD);
        if(i>=x+1) break;
        res=1LL*res*(x-i)%MOD;
        res=1LL*res*inv[i+2]%MOD;
    }
    return ans;
}
void genf(ll n)
{
    ll i,j=0;
    for(i=1;i<=m;i++) f[i]=getsum(n/i),dec(f[i],1);
    for(i=2;i<=m;i++) g[i]=getsum(i),dec(g[i],1);
    for(i=2;i<=m;i++)
    {
        if(g[i]==g[i-1]) continue;
        for(j=1;j<=min(m-1,n/i/i);++j)
        {
            if(i*j<m) dec(f[j],1LL*p[i]*(f[i*j]-g[i-1])%MOD),add(f[j],0);
            else dec(f[j],p[i]*(g[n/i/j]-g[i-1])),add(f[j],0);
        }
        for(j=m;j>=i*i;j--) dec(g[j],1LL*p[i]*(g[j/i]-g[i-1])),add(g[j],0);
    }
}
int getpr(ll x)
{
    if(x<=m) return g[x];
    return f[n/x];
}
void genmiu(int n)
{
    int p=0;
    for(int i=0;i<=n;i++) is_prime[i]=true;
    is_prime[0]=is_prime[1]=false;
    mmiu[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(is_prime[i]) {prime[p++]=i; mmiu[i]=MOD-1LL*i*i%MOD;}
        for(int j=0;j<p;j++)
        {
            if(prime[j]*i>n) break;
            is_prime[prime[j]*i]=false;
            mmiu[i*prime[j]]=i%prime[j]?(MOD-1LL*mmiu[i]*prime[j]%MOD*prime[j]%MOD):0;
            if(i%prime[j]==0) break;
        }
    }
    for(int i=1;i<=n;i++) miuf[i]=miuf[i-1],add(miuf[i],mmiu[i]);
}
int getsum3(ll x)
{
    ll res1=x,res2=x+1,res3=2*x+1;
    if(res1%2==0) res1/=2; else if(res2%2==0) res2/=2; else res3/=2;
    if(res1%3==0) res1/=3; else if(res2%3==0) res2/=3; else res3/=3;
    return 1LL*(res1%MOD)*(res2%MOD)%MOD*(res3%MOD)%MOD;
}
int calc(ll x)
{
	if(x<=10000000) return miuf[x];
	if(mp.find(x)!=mp.end()) return mp[x];
	int ans=1;
	for(ll i=2,r;i<=x;i=r+1)
	{
		r=x/(x/i);
		dec(ans,1LL*calc(x/i)*(getsum3(r)-getsum3(i-1))%MOD);
	}
	return mp[x]=ans;
}
int getff(ll x)
{
    if(mp2.find(x)!=mp2.end()) return mp2[x];
    int ans=0;
    for(ll i=1,r;i<=x;i=r+1)
    {
        r=x/(x/i);
        int res=calc(r);
        dec(res,calc(i-1));
        int tmp=(x/i)%MOD;
        res=1LL*res*tmp%MOD*tmp%MOD;
        res=1LL*res*(tmp+1)%MOD*(tmp+1)%MOD;
        res=1LL*res*INV%MOD;
        add(ans,res);
    }
    return ans%MOD;
}
int main()
{
	genmiu(10000000);
	for(int i=1;i<=100002;i++) inv[i]=pow_mod(i,MOD-2);
	scanf("%d",&T);
	while(T--)
    {
        scanf("%lld%d",&n,&k);
        for(m=1;1LL*m*m<=n;m++);
        k++;
        p[0]=1;
        for(int i=1;i<=m;i++)
        {
            p[i]=1;
            for(int j=1;j<=k;j++) p[i]=1LL*p[i]*i%MOD;
        }
        poly.clear();
        getpoly();
        genf(n);
        int ans=0;
        for(ll i=1,r;i<=n;i=r+1)
        {
            r=n/(n/i);
            int res=getpr(r);
            dec(res,getpr(i-1));
            res=1LL*res*getff(n/i)%MOD;
            add(ans,res);
        }
        printf("%d\n",ans);
    }
	return 0;
}
