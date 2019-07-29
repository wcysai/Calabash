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
int cnt,mphi[MAXN],prime[MAXN];
int T;
ll n,m;
int k,f[MAXM],g[MAXM];
int phif[MAXN];
int pf[MAXM];
unordered_map<ll,int> mp;
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
    int res=(x+1)%MOD,ans=0;
    for(int i=0;i<=k;i++)
    {
        add(ans,1LL*res*poly[i]%MOD);
        res=1LL*res*((x-i)%MOD)%MOD;
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
            if(i*j<m) dec(f[j],1LL*p[i]*(f[i*j]-g[i-1]+MOD)%MOD);
            else dec(f[j],1LL*p[i]*(g[n/i/j]-g[i-1]+MOD)%MOD);
        }
        for(j=m;j>=i*i;j--) dec(g[j],1LL*p[i]*(g[j/i]-g[i-1]+MOD)%MOD);
    }
}
int getpr(ll x)
{
    if(x<=m) return g[x];
    return f[n/x];
}
void gen(int n)
{
    int p=0;
    for(int i=0;i<=n;i++) is_prime[i]=true;
    is_prime[0]=is_prime[1]=false;
    mphi[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(is_prime[i]) {prime[p++]=i; mphi[i]=1LL*i*i%MOD*(i-1)%MOD;}
        for(int j=0;j<p;j++)
        {
            if(prime[j]*i>n) break;
            is_prime[prime[j]*i]=false;
            mphi[i*prime[j]]=i%prime[j]?(1LL*mphi[i]*mphi[prime[j]]%MOD):1LL*mphi[i]*prime[j]%MOD*prime[j]%MOD*prime[j]%MOD;
            if(i%prime[j]==0) break;
        }
    }
    for(int i=1;i<=n;i++) phif[i]=phif[i-1],add(phif[i],mphi[i]);
}
int getsum3(ll x)
{
    ll res1=x,res2=x+1,res3=2*x+1;
    if(res1%2==0) res1/=2; else if(res2%2==0) res2/=2; else res3/=2;
    if(res1%3==0) res1/=3; else if(res2%3==0) res2/=3; else res3/=3;
    return 1LL*(res1%MOD)*(res2%MOD)%MOD*(res3%MOD)%MOD;
}
int getsum4(ll x)
{
    if(x&1)
    {
        int tmp1=((x+1)/2)%MOD,tmp2=x%MOD;
        return 1LL*tmp2*tmp2%MOD*tmp1%MOD*tmp1%MOD;
    }
    else
    {
        int tmp1=(x/2)%MOD,tmp2=(x+1)%MOD;
        return 1LL*tmp2*tmp2%MOD*tmp1%MOD*tmp1%MOD;
    }
}
int calc(ll x)
{
	if(x<=10000000) return phif[x];
	if(mp.find(x)!=mp.end()) return mp[x];
	int ans=getsum4(x);
	for(ll i=2,r;i<=x;i=r+1)
	{
		r=x/(x/i);
		dec(ans,1LL*calc(x/i)*(getsum3(r)-getsum3(i-1)+MOD)%MOD);
	}
	return mp[x]=ans;
}
int main()
{
	gen(10000000);
	for(int i=1;i<=100002;i++) inv[i]=pow_mod(i,MOD-2);
	scanf("%d",&T);
	while(T--)
    {
        scanf("%lld%d",&n,&k);
        for(m=1;1LL*m*m<=n;m++);
        k++;
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
            res=1LL*res*calc(n/i)%MOD;
            add(ans,res);
        }
        printf("%d\n",ans);
    }
	return 0;
}
