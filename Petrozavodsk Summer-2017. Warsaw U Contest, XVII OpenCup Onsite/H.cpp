#pragma optimize GCC(3)
#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int prime[MAXN],cnt[MAXN];
bool is_prime[MAXN];
int q,a,b;
int sieve(int n)
{
    int p=0;
    memset(is_prime,true,sizeof(is_prime));
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
int main()
{
    int p=sieve(1000000);
    for(int i=1;i<=1000000;i++)
    {
        cnt[i]=cnt[i-1];
        if(is_prime[i]) cnt[i]++;
    }
    scanf("%d",&q);
    for(int i=0;i<q;i++)
    {
        scanf("%d%d",&a,&b);a--;
        int last;ll ans;ans=0;
        if(a==0)
        {
            for(int i=1;i<=b;i=last+1)
            {
                last=b/(b/i);
                ll num=1LL*(b/i)*(b/i-1)/2;
                ans+=1LL*num*(cnt[last]-cnt[i-1]);
                //printf("%lld %lld %lld\n",b/i,last,i-1);
            }
        }
        else
        {
            for(int i=1;i<=b;i=last+1)
            {
                if(a<i) last=b/(b/i);
                else last=min(a/(a/i),b/(b/i));
                ll num=1LL*(b/i-a/i)*(b/i-a/i-1)/2;
                ans+=1LL*num*(cnt[last]-cnt[i-1]);
            }
        }
        printf("%lld\n",ans);fflush(stdout);
    }
    return 0;
}
