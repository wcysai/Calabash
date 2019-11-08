#include<bits/stdc++.h>
#define MAXN 505
#define MAXM 250005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
typedef pair<double,ll> PP;
const double eps=1e-2;
ll n,m,d[MAXN][MAXN],save[MAXN][MAXN],pre[MAXN];
double d2[MAXN];
ll u[MAXM],v[MAXM],w[MAXM];
bool used[MAXN];
vector<P> dist[MAXN];
vector<P> MDST;
void floyd_warshall()
{
    for(ll k=1;k<=n;k++)
        for(ll i=1;i<=n;i++)
            for(ll j=1;j<=n;j++)
                d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
}
pair<P,double> absolute_center()
{
    ll ans=INF;
    ll uu=-1,vv=-1;
    double res=0.0;
    for(ll i=1;i<=n;i++)
    {
        int sz=(int)dist[i].size();
        if(dist[i][sz-1].F+dist[i][sz-2].F<ans)
        {
            ans=dist[i][sz-1].F+dist[i][sz-2].F;
            uu=vv=i; res=0.0;
        }
    }
    for(ll i=0;i<m;i++)
    {
        memset(used,false,sizeof(used));
        ll now=(int)dist[v[i]].size()-1;
        for(ll j=0;j<(int)dist[u[i]].size();j++)
        {
            used[dist[u[i]][j].S]=true;
            while(now>0&&used[dist[v[i]][now].S]) now--;
            double pos=(dist[u[i]][j].F+dist[v[i]][now].F+w[i])/2.0-dist[u[i]][j].F;
            if(pos<eps||pos-w[i]>eps) continue;
            if(dist[u[i]][j].F+dist[v[i]][now].F+w[i]<ans)
            {
                ans=dist[u[i]][j].F+dist[v[i]][now].F+w[i];
                uu=u[i]; vv=v[i]; res=pos;
            }
        }
    }
    printf("%lld\n",ans);
    return make_pair(P(uu,vv),res);
}
void minimum_diameter_spanning_tree()
{
    MDST.clear();
    auto p=absolute_center();
    fill(d2,d2+n+1,INF); memset(pre,-1,sizeof(pre));
    priority_queue<PP,vector<PP>,greater<PP> > que;
    d2[p.F.F]=p.S; d2[p.F.S]=d[p.F.F][p.F.S]-p.S;
    que.push(PP(d2[p.F.F],p.F.F)); if(p.F.F!=p.F.S) que.push(PP(d2[p.F.S],p.F.S));
    while(!que.empty())
    {
        PP p=que.top(); que.pop();
        ll v=p.S;
        if(d2[v]<p.F) continue;
        for(ll to=1;to<=n;to++)
        {
            if(d2[to]>d2[v]+save[v][to])
            {
                d2[to]=d2[v]+save[v][to];
                pre[to]=v;
                que.push(PP(d2[to],to));
            }
        }
    }
    if(p.F.F!=p.F.S) MDST.push_back(P(p.F.F,p.F.S));
    for(ll i=1;i<=n;i++) if(pre[i]!=-1) MDST.push_back(P(pre[i],i));
}
int main()
{
    scanf("%lld%lld",&n,&m);
    for(ll i=1;i<=n;i++)
        for(ll j=1;j<=n;j++)
            d[i][j]=save[i][j]=(i==j?0:INF);
    for(ll i=0;i<m;i++)
    {
        scanf("%lld%lld%lld",&u[i],&v[i],&w[i]);
        d[u[i]][v[i]]=d[v[i]][u[i]]=save[u[i]][v[i]]=save[v[i]][u[i]]=w[i];
    }
    floyd_warshall();
    for(ll i=1;i<=n;i++)
    {
        for(ll j=1;j<=n;j++) dist[i].push_back(P(d[i][j],j));
        sort(dist[i].begin(),dist[i].end());
    }
    minimum_diameter_spanning_tree();
    for(auto p:MDST) printf("%lld %lld\n",p.F,p.S);
    return 0;
}
