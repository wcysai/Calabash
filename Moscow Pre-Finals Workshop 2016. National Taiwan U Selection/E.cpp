#include<bits/stdc++.h>
#define MAXN 10000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,m;
int prime[MAXN],mu[MAXN],evensum[MAXN],oddsum[MAXN];
bool is_prime[MAXN];
int sieve(int n)
{
    int p=0;
    for(int i=0;i<=n;i++) is_prime[i]=true;
    is_prime[0]=is_prime[1]=false;
    mu[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(is_prime[i]) {prime[p++]=i; mu[i]=-1;}
        for(int j=0;j<p;j++)
        {
            if(prime[j]*i>n) break;
            is_prime[prime[j]*i]=false;
            mu[prime[j]*i]=(i%prime[j]?-mu[i]:0);
            if(i%prime[j]==0) break;
        }
    }
    for(int i=1;i<=n;i++)
    {
        oddsum[i]=oddsum[i-1];
        evensum[i]=evensum[i-1];
        if(i&1) oddsum[i]+=mu[i]; else evensum[i]+=mu[i];
    }
    return p;
}
ll get_ans(int n,int m)
{
    if(n<=0||m<=0) return 0;
    ll ans;
    int st=max(0,n-m),ed=n-1;
    ans=1LL*(ed+st)*(ed-st+1)/2;
    ed=n-1;
    st=max(ed&1,n-m*2+1);
    ans-=1LL*(st+ed)*((ed-st)/2+1)/2;
    assert(ans>=0);
    return ans;
}
ll get_ans2(int n,int m)
{
    if(n<=0||m<=0) return 0;
    return get_ans(n/2,m/2)+get_ans(n/2+1,(m+1)/2);
}
int get(int x,int y)
{
    if(y>x) return INF;
    return x/(x/y);
}
int main()
{
    sieve(10000000);
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        if(n==1&&m==1)
        {
            puts("1");
            continue;
        }
        if(n<m) swap(n,m);
        ll ans=0;
        int last=-1;
        for(int i=1;i<=max(n,m);i=last+1)
        {
            last=min(get(n,i),get(m,i));
            ans+=1LL*(evensum[last]-evensum[i-1])*get_ans(n/i,m/i);
            ans+=1LL*(oddsum[last]-oddsum[i-1])*get_ans2(n/i,m/i);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
