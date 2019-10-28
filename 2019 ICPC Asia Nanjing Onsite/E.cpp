#include<bits/stdc++.h>
#define MAXN 10000005
#define MAXL 1000005
#define MAXSQRTB 4000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
int T;
bool issqr[MAXN];
bool is_prime_small[MAXSQRTB];
ll save[MAXL],ans[MAXL];
ll L,R,K,P;
void segment_sieve(ll a,ll b)
{
    for(int i=0;1LL*i*i<=b;i++) is_prime_small[i]=true;
    for(int i=0;i<=b-a;i++) save[i]=a+i,ans[i]=1;
    for(int i=2;(ll)i*i<=b;i++)
    {
        if(is_prime_small[i])
        {
            for(ll j=2*i;(ll)j*j<=b;j+=i) is_prime_small[j]=false;
            for(ll j=max(2LL,(a+i-1)/i)*i;j<=b;j+=i)
            {
                ll res=1;
                while(save[j-a]%i==0)
                {
                    save[j-a]/=i;
                    if(i==2);
                    else if(i%4==1) res=res*i;
                    else res=res*i+2;
                }
                ans[j-a]*=res;
            }
        }
    }
    for(ll i=0;i<=b-a;i++)
        if(save[i]!=1)
        {
            if(save[i]==2);
            else ans[i]*=(save[i]%4==1?save[i]:save[i]+2);
        }
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld%lld%lld%lld",&L,&R,&K,&P);
        segment_sieve(L,R);
        ll res=0;
        for(int i=0;i<=R-L;i++)
        {
            res+=(6LL*ans[i])^K;
            res%=P;
        }
        printf("%lld\n",res);
    }
    return 0;
}
