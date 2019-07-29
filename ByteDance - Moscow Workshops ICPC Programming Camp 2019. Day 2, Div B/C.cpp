#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 2000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m, routecnt;
struct edge{int to,cost;};
struct ee{int from,to,cost;};
vector<edge> G[MAXN],rG[MAXN];
int d1[MAXN],d2[MAXN];//d1: dist to 1 d2: dist to n
ll dp[MAXN];
vector<ee> route[MAXN];
vector<ee> vroute[MAXN];
vector<P> trans[MAXN];
vector<pair<ll,ll> > st[MAXN];
vector<P> order;
double get(P u,P v)
{
    return (v.S-u.S)/(u.F-v.F);
}
void add(ll id,ll u,ll v)
{
    pair<ll,ll> p=make_pair(u,v);
    ll t=(int)st[id].size();
    while(t>1&&(st[id][t-1].F-st[id][t-2].F)*(p.S-st[id][t-1].S)<=(st[id][t-1].F-p.F)*(st[id][t-2].S-st[id][t-1].S)) st[id].pop_back(),t--;
    st[id].push_back(p);
}
ll query(ll id,ll x)
{
    ll l=-1,r=(int)st[id].size()-1;
    while(r-l>1)
    {
        ll mid=(l+r)/2;
        if(st[id][mid].F*x+st[id][mid].S<=st[id][mid+1].F*x+st[id][mid+1].S) l=mid;
        else r=mid;
    }
    return st[id][r].F*x+st[id][r].S;
}
void add_edge(int u,int v,int w)
{
    G[u].push_back((edge){v,w});
    rG[v].push_back((edge){u,w});
}
void dijkstra(ll s)
{
    priority_queue<P,vector<P>,greater<P> > que;
    fill(d1+1,d1+n+1,INF);
    d1[s]=0;
    que.push(P(0,s));
    while(!que.empty())
    {
        P p=que.top(); que.pop();
        ll v=p.second;
        if(d1[v]<p.first) continue;
        for(ll i=0;i<(int)G[v].size();i++)
        {
            edge e=G[v][i];
            if(d1[e.to]>d1[v]+e.cost)
            {
                d1[e.to]=d1[v]+e.cost;
                que.push(P(d1[e.to],e.to));
            }
        }
    }
}
void dijkstra2(ll s)
{
    priority_queue<P,vector<P>,greater<P> > que;
    fill(d2+1,d2+n+1,INF);
    d2[s]=0;
    que.push(P(0,s));
    while(!que.empty())
    {
        P p=que.top(); que.pop();
        ll v=p.second;
        if(d2[v]<p.first) continue;
        for(ll i=0;i<(int)rG[v].size();i++)
        {
            edge e=rG[v][i];
            if(d2[e.to]>d2[v]+e.cost)
            {
                d2[e.to]=d2[v]+e.cost;
                que.push(P(d2[e.to],e.to));
            }
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
    {
        int k;scanf("%d",&k);
        int v;scanf("%d",&v);
        for(ll j=0;j<k;j++)
        {
            int to,cost;
            scanf("%d%d",&cost,&to);
            add_edge(v,to,cost);
            route[i].push_back((ee){v,to,cost});
            v=to;
        }
    }
    dijkstra(1); dijkstra2(n);
    ll dis=d1[n];
    for(ll i=1;i<=n;i++) order.push_back(P(d1[i],i));
    sort(order.begin(),order.end());
    for(ll i=0;i<m;i++)
    {
        bool f=false;
        for(auto e:route[i])
        {
            if(d1[e.from]+d2[e.to]+e.cost==dis)
            {
                if(!f) f=true;
                vroute[routecnt].push_back(e);
            }
            else
            {
                if(f)
                {
                    trans[vroute[routecnt][0].from].push_back(P(routecnt,-1));
                    for(ll j=0;j<(int)vroute[routecnt].size();j++)
                    {
                        ll u=vroute[routecnt][j].from,v=vroute[routecnt][j].to;
                        trans[v].push_back(P(routecnt,u));
                    }
                    routecnt++; f=false;
                }
            }
        }
        if(f) 
        {
            trans[vroute[routecnt][0].from].push_back(P(routecnt,-1));
            for(ll j=0;j<(int)vroute[routecnt].size();j++)
            {
                ll u=vroute[routecnt][j].from,v=vroute[routecnt][j].to;
                trans[v].push_back(P(routecnt,u));
            }
            routecnt++; f=false;
        }
    }
    memset(dp,0,sizeof(dp));
    for(ll i=0;i<n;i++)
    {
        ll v=order[i].S;
        for(auto p:trans[v]) if(p.S!=-1) dp[v]=max(dp[v],query(p.F,d1[v])+1LL*d1[v]*d1[v]);
        for(auto p:trans[v]) add(p.F,-2*d1[v],dp[v]+1LL*d1[v]*d1[v]);
    }
    printf("%d %lld\n",d1[n],dp[n]);
    return 0;
}

