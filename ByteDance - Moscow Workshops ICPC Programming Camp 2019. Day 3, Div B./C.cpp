#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
typedef vector<ll> VI;
typedef vector<VI> VVI;
ll n,m;
pair<ll,VI> GetMinCut(VVI &weights)
{
    ll N=weights.size();
    VI used(N),cut,best_cut;
    ll best_weight=-1;
    for(ll phase=N-1;phase>=0;phase--)
    {
        VI w=weights[0];
        VI added=used;
        ll prev,last=0;
        for(ll i=0;i<phase;i++)
        {
            prev=last;
            last=-1;
            for(ll j=1;j<N;j++) if(!added[j]&&(last==-1||w[j]>w[last])) last=j;
            if(i==phase-1)
            {
                for(ll j=0;j<N;j++) weights[prev][j]+=weights[last][j];
                for(ll j=0;j<N;j++) weights[j][prev]=weights[prev][j];
                used[last]=true;
                cut.push_back(last);
                if(best_weight==-1||w[last]<best_weight)
                {
                    best_cut=cut;
                    best_weight=w[last];
                }
            }
            else
            {
                for(ll j=0;j<N;j++) w[j]+=weights[last][j];
                added[last]=true;
            }
        }
    }
    return make_pair(best_weight,best_cut);
}
VVI G;
int main()
{
    scanf("%lld%lld",&n,&m);
    G.resize(n);
    for(int i=0;i<n;i++) G[i].resize(n);
    for(ll i=0;i<n;i++)
        for(ll j=0;j<n;j++)
            G[i][j]=0;
    for(ll i=0;i<m;i++)
    {
        ll u,v,c;
        scanf("%lld%lld%lld",&u,&v,&c);
        u--;v--;
        if(G[u][v]==0)
        {
            G[u][v]=G[v][u]=c;
        }
        else
        {
            G[u][v]+=c;
            G[v][u]+=c;
        }
    }
    printf("%lld\n",GetMinCut(G).F);
    return 0;
}
