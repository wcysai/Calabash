include<bits/stdc++.h>
#define MAXN 100005
#define MAXM 25
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
ll t,tot;
ll k;
vector<P> v;
ll cnt[MAXM];
ll fact[25];
int main()
{
    fact[0]=1;
    for(int i=1;i<=20;i++) fact[i]=fact[i-1]*i;
    scanf("%lld",&t);
    while(t--)
    {
        memset(cnt,0,sizeof(cnt));
        tot=2;
        scanf("%lld",&k);
        while(k)
        {
            cnt[k%tot]++;
            k/=tot;
            tot++;
        }
        ll ans=1;
        int res=cnt[0];
        ll divi=1;
        for(int i=0;i<=tot-2;i++) divi*=fact[cnt[i]];
        for(int i=1;i<=tot-2;i++)
        {
            res+=cnt[i];
            ans=ans*res;
            res--;
        }
        ans/=divi;
        if(cnt[0])
        {
            ll tmp=cnt[0];
            cnt[0]--;
            res=cnt[0];
            for(int i=1;i<=tot-3;i++)
            {
                res+=cnt[i];
                tmp=tmp*res;
                res--;
            }
            ans-=tmp/divi;
        }
        printf("%lld\n",ans-1);
    }
    return 0;
}
