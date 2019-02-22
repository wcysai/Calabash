#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 20
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll n,m;
ll t[MAXN];
ll a[MAXN][MAXN];
ll b[MAXN][MAXN];
vector<int> mask;
int main()
{
    scanf("%lld%lld",&n,&m);
    for(ll i=0;i<n;i++) scanf("%lld",&t[i]);
    for(ll i=0;i<n;i++)
        for(ll j=0;j<m;j++)
            scanf("%lld",&a[i][j]);
    for(ll i=0;i<n;i++)
        for(ll j=0;j<m;j++)
            scanf("%lld",&b[i][j]);
    for(ll i=1;i<(1<<m);i++)
    {
        bool f=true;
        ll cnt=0;
        for(ll j=0;j<n;j++)
        {
            if(!t[j]) continue;
            if(!f) break;
            ll save=0;
            for(ll k=m-1;k>=0;k--)
            {
                if(!(i&(1<<k))) continue;
                if(a[j][k]>save)
                {
                    f=false;
                    break;
                }
                save-=a[j][k];
                save+=b[j][k];
            }
            cnt+=save;
        }
        for(ll j=0;j<n;j++)
        {
            if(t[j]) continue;
            if(!f) break;
            ll save=0;
            for(ll k=m-1;k>=0;k--)
            {
                if(!(i&(1<<k))) continue;
                if(a[j][k]>cnt)
                {
                    f=false;
                    break;
                }
                cnt-=a[j][k];
                save+=b[j][k];
            }
            cnt+=save;
        }
        if(f) mask.push_back(i);
    }
    ll ans=0;
    for(ll i=0;i<n;i++)
        for(ll j=0;j<m;j++)
        {
            bool flag=true;
            for(auto mm:mask)
            {
                if(mm&(1<<j))
                {
                    flag=false;
                    break;
                }
            }
            if(flag) ans+=a[i][j];
        }
    printf("%lld\n",ans);
    return 0;
}

