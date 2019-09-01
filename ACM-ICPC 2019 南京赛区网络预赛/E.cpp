#include<bits/stdc++.h>
#define MAXN 1000005
#define MOD 1000000007
#define PHI 1000000006
#define INF 1000000000
#define INV6 166666668
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
int T,n,k1,k2,prime[MAXN],f[MAXN],g[MAXN];
bool is_prime[MAXN];
string str;
map<int,int> mp;
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
int sieve(int n)
{
    int p=0;
    for(int i=0;i<=n;i++) is_prime[i]=true;
    is_prime[0]=is_prime[1]=false;
    memset(f,0,sizeof(f));
    f[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(is_prime[i]) {prime[p++]=i; f[i]=(1LL*i*i-1)%MOD;}
        for(int j=0;j<p;j++)
        {
            if(prime[j]*i>n) break;
            is_prime[prime[j]*i]=false;
            f[i*prime[j]]=(i%prime[j]==0)?1LL*f[i]*prime[j]%MOD*prime[j]%MOD:1LL*f[i]*f[prime[j]]%MOD;
            if(i%prime[j]==0) break;
        }
    }
    for(int i=1;i<=n;i++)
    {
        g[i]=g[i-1];
        add(g[i],f[i]);
    }
    return p;
}
int get_sum(int x)
{
    return 1LL*x*(x+1)%MOD*(2*x+1)%MOD*INV6%MOD;
}
int calc(int x)
{
	if(x<=1000000) return g[x];
	if(mp.find(x)!=mp.end()) return mp[x];
	int ans=get_sum(x);
	for(ll i=2,r;i<=x;i=r+1)
	{
		r=x/(x/i);
		dec(ans,1LL*calc(x/i)*(r-i+1)%MOD);
	}
	return mp[x]=ans;
}
int main()
{
    sieve(1000000);
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        cin>>str;
        k1=0; k2=0;
        for(int i=0;i<(int)str.size();i++)
        {
            k1=(10LL*k1+(int)str[i]-'0')%PHI;
            k2=(10LL*k2+(int)str[i]-'0')%MOD;
        }
        int ans=0;
        for(int i=1,r;i<=n;i=r+1)
        {
            r=n/(n/i);
            int v=n/i;
            int res=(calc(r)-calc(i-1)+MOD)%MOD;
            if(v==1) add(ans,1LL*(k2-1+MOD)*res%MOD);
            else
            {
                add(ans,1LL*(pow_mod(v,k1+1)-v+MOD)*pow_mod(v-1,MOD-2)%MOD*res%MOD);
                dec(ans,1LL*v*res%MOD);
            }
        }
        printf("%d\n",ans);
    }
}
