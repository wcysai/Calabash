#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T;
ll l,r;
int k;
int small_prime[MAXN];
bool is_prime_small[MAXN];
int res[MAXN];
ll rem[MAXN];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
int sieve(int n)
{
    int p=0;
    memset(is_prime_small,true,sizeof(is_prime_small));
    is_prime_small[0]=is_prime_small[1]=false;
    for(int i=2;i<=n;i++)
    {
        if(is_prime_small[i]) small_prime[p++]=i;
        for(int j=0;j<p;j++)
        {
            if(small_prime[j]*i>n) break;
            is_prime_small[small_prime[j]*i]=false;
            if(i%small_prime[j]==0) break;
        }
    }
    return p;
}
int main()
{
    int p=sieve(1000000);
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld%lld%d",&l,&r,&k);
        for(ll i=0;i<=r-l;i++) res[i]=1;
        for(ll i=0;i<=r-l;i++) rem[i]=l+i;
        for(int i=0;i<p;i++)
        {
            int x=small_prime[i];
            if(1LL*x*x>r) break;
            for(ll j=max(1LL,(l+x-1)/x)*x;j<=r;j+=x) 
            {
                int cnt=0;
                while(rem[j-l]%x==0) rem[j-l]/=x,cnt++;
                res[j-l]=1LL*res[j-l]*(1LL*k*cnt+1)%MOD;
            }
        }
        for(int i=0;i<=r-l;i++) 
            if(rem[i]!=1) res[i]=1LL*(k+1)*res[i]%MOD;
        int ans=0;
        for(int i=0;i<=r-l;i++) add(ans,res[i]);
        printf("%d\n",ans);
    }
    return 0;
}
