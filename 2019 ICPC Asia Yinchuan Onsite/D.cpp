#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
string n;
int T,m,d,k,res[2];
int prime[MAXN],mu[MAXN];
bool is_prime[MAXN];
int p[2][MAXN];
int MOD[2]={643,93257};
void add(int &a,int b,int mod) {a+=b; if(a>=mod) a-=mod;}
void dec(int &a,int b,int mod) {a-=b; if(a<0) a+=mod;}
int sieve(int n)
{
    int p=0;
    memset(is_prime,true,sizeof(is_prime));
    memset(mu,0,sizeof(mu));
    is_prime[0]=is_prime[1]=false;
    mu[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(is_prime[i]) {prime[p++]=i; mu[i]=-1;}
        for(int j=0;j<p;j++)
        {
            if(i*prime[j]>n) break;
            is_prime[i*prime[j]]=false;
            mu[i*prime[j]]=(i%prime[j]?-mu[i]:0);
            if(i%prime[j]==0) break;
        }
    }
    return p;
}
int get_mod(string str,int mod)
{
    int res=0;
    for(int i=0;i<(int)str.size();i++) res=(10LL*res+str[i]-'0')%mod;
    return res;
}
int pow_mod(int a,int i,int mod)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%mod;
        a=1LL*a*a%mod;
        i>>=1;
    }
    return s;
}
int get_ans(int m,int k,int d,int id)
{
    int ans=0;
    for(int i=1;i<=m/d;i++)
    {
        int dd=i*d;
        int x=p[id][m/dd],y=pow_mod(dd,k,MOD[id]);
        x=1LL*x*y%MOD[id];
        x=pow_mod(x,res[id],MOD[id]);
        if(mu[i]==1) add(ans,x,MOD[id]);
        else if(mu[i]==-1) dec(ans,x,MOD[id]);
    }
    return ans;
}
int main()
{
    sieve(100000);
    scanf("%d",&T);
    while(T--)
    {
        cin>>n;
        res[0]=get_mod(n,MOD[0]-1); res[1]=get_mod(n,MOD[1]-1);
        scanf("%d%d%d",&m,&d,&k);
        for(int i=0;i<2;i++)
        {
            for(int j=0;j<=100000;j++) p[i][j]=pow_mod(j,k,MOD[i]);
            for(int j=1;j<=100000;j++) add(p[i][j],p[i][j-1],MOD[i]);
        }
        int ans1=get_ans(m,k,d,0),ans2=get_ans(m,k,d,1);
        int ans=ans1;
        while(ans%MOD[1]!=ans2) add(ans,MOD[0],MOD[0]*MOD[1]);
        printf("%d\n",ans);
    }
    return 0;
}
