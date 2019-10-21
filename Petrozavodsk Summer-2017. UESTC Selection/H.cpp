#include<bits/stdc++.h>
#define MAXN 10005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,q,t;
int prime[MAXN];
bool is_prime[MAXN];
vector<int> fact;
vector<int> pr;
vector<int> aa;

int extgcd(int a,int b,int &x,int &y)
{
    int d=a;
    if(b!=0)
    {
        d=extgcd(b,a%b,y,x);
        y-=(a/b)*x;
    }
    else
    {
        x=1;
        y=0;
    }
    return d;
}
int mod_inverse(int a,int m)
{
    int x,y;
    extgcd(a,m,x,y);
    return (m+x%m)%m;
}
int sieve(int n)
{
    memset(is_prime,true,sizeof(is_prime));
    is_prime[0]=is_prime[1]=false;
    int p=0;
    for(int i=2;i<=n;i++)
    {
        if(is_prime[i]) prime[p++]=i;
        for(int j=0;j<p;j++)
        {
            if(prime[j]*i>n) break;
            is_prime[prime[j]*i]=false;
            if(i%prime[j]==0) break;
        }
    }
    return p;
}
int pow_mod(int a,int i,int p)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%p;
        a=1LL*a*a%p;
        i>>=1;
    }
    return s;
}
bool g_test(int g,int p)
{
    for(int i=0;i<(int)aa.size();i++)
        if(pow_mod(g,(p-1)/aa[i],p)==1) return 0;
    return 1;
}
int primitive_root(int p)
{
    int tmp=p-1;
    aa.clear();
    for(int i=2;i*i<=tmp;i++)
    {
        if(tmp%i==0)
        {
            aa.push_back(i);
            while(tmp%i==0) tmp/=i;
        }
    }
    if(tmp!=1) aa.push_back(tmp);
    int g=1;
    while(true)
    {
        if(g_test(g,p)) return g;
        ++g;
    }
}
unordered_map<int,int> mp[10];
void construct(int id)
{
    int p=fact[id],g=pr[id];
    int now=1;
    mp[id][now]=0;
    int x=pow_mod(g,10000000,p);
    for(int i=1;i<=t;i++)
    {
        now=1LL*now*g%p;
        if(!mp[id].count(now)) mp[id][now]=i; else break;
    }
}
int find_order(int id,int x)
{
    int p=fact[id],g=pr[id];
    int tt=pow_mod(g,t,p); tt=pow_mod(tt,p-2,p);
    int now=x;
    for(int i=0;i<=40;i++)
    {
        if(mp[id].count(now))
        {
            int ans=(1LL*i*t+mp[id][now])%p;
            return ans;
        }
        now=1LL*now*tt%p;
    }
    return -1;
}
int get_ans(int x,int y,int id)
{
    int p=fact[id],g=pr[id];
    int xx=x%p,yy=y%p;
    if(xx==0)
    {
        if(yy==0) return 1;
        else if(yy==1) return 0;
        else return -1;
    }
    if(yy==0) return -1;
    int a=find_order(id,xx),b=find_order(id,yy);
    if(b==0) return 0;
    if(a==0) return -1;
    int pp=p-1;
    int gg=__gcd(a,pp); if(b%gg) return -1;
    a/=gg; b/=gg; pp/=gg;
    return 1LL*b*mod_inverse(a,pp)%pp;
}
int main()
{
    int p=sieve(10000);
    scanf("%d%d",&n,&q);
    t=3000000;
    for(int i=0;i<p;i++)
    {
        if(n%prime[i]==0)
        {
            fact.push_back(prime[i]);
            while(n%prime[i]==0) n/=prime[i];
        }
    }
    if(n>1) fact.push_back(n);
    for(int i=0;i<(int)fact.size();i++)
    {
        pr.push_back(primitive_root(fact[i]));
        construct(i);
    }
    for(int i=0;i<q;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        int ans=-1;
        for(int j=0;j<(int)fact.size();j++)
        {
            int res=get_ans(x,y,j);
            if(ans==-1) ans=res;
            else if(res!=-1) ans=min(ans,res);
        }
        printf("%d\n",ans);
    }
    return 0;
}
