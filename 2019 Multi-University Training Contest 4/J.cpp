#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int prime[MAXN];
bool is_prime[MAXN];
int sieve(int n)
{
    int p=0;
    for(int i=0;i<=n;i++) is_prime[i]=true;
    is_prime[0]=is_prime[1]=false;
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
int T;
ll n;
int main()
{
    int p=sieve(4000);
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld",&n);
        int ans=INF;
        for(int i=0;i<p;i++)
        {
            if(n%prime[i]==0)
            {
                int cnt=0;
                while(n%prime[i]==0) n/=prime[i],cnt++;
                ans=min(ans,cnt);
            }
        }
        if(n==1) {printf("%d\n",ans); continue;}
        bool f=false;
        ll d=(ll)pow(n,0.25);
        for(ll i=max(1LL,d-10);i<=d+10;i++)
            if(i*i*i*i==n)
            {
                ans=min(ans,4);
                f=true;
                break;
            }
        if(f) {printf("%d\n",ans); continue;}
        d=(ll)pow(n,1.0/3);
        for(ll i=max(1LL,d-10);i<=d+10;i++)
            if(i*i*i==n)
            {
                ans=min(ans,3);
                f=true;
                break;
            }
        if(f) {printf("%d\n",ans); continue;}
        d=(ll)pow(n,1.0/2);
        for(ll i=max(1LL,d-10);i<=d+10;i++)
            if(i*i==n)
            {
                ans=min(ans,2);
                f=true;
                break;
            }
        if(f) {printf("%d\n",ans); continue;}
        puts("1");
    }
    return 0;
}
