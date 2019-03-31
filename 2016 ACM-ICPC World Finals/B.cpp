#include<bits/stdc++.h>
#define MAXN 5005
#define MAXM 50005
#define INF 1000000000000000000LL
#define INF2 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
struct edge{int to,cost;};
vector<edge> G[MAXN];
vector<edge> rG[MAXN];
int n,b,s,r;
int d1[MAXN],d2[MAXN];
ll sum[MAXN],dp[MAXN][MAXN];
void add_edge(int u,int v,int cost)
{
    G[u].push_back((edge){v,cost});
    rG[v].push_back((edge){u,cost});
}
void dijkstra(int s,bool flag)//flag 0:edge 1:reversed edge
{
    priority_queue<P,vector<P>,greater<P> > que;
    if(flag) fill(d2+1,d2+n+1,INF2); else fill(d1+1,d1+n+1,INF2);
    if(flag) d2[s]=0; else d1[s]=0;
    que.push(P(0,s));
    while(!que.empty())
    {
        P p=que.top();que.pop();
        int v=p.second;
        if((flag?d2[v]:d1[v])<p.F) continue;
        for(int i=0;i<(int)(flag?rG[v].size():G[v].size());i++)
        {
            edge e=(flag?rG[v][i]:G[v][i]);
            if((flag?d2[e.to]:d1[e.to])>(flag?d2[v]:d1[v])+e.cost)
            {
                (flag?d2[e.to]:d1[e.to])=(flag?d2[v]:d1[v])+e.cost;
                que.push(P(flag?d2[e.to]:d1[e.to],e.to));
            }
        }
    }
}
vector<int> v;
void solve(int layer,int l,int r,int optl,int optr)
{
    if(l>r) return;
    int mid=(l+r)/2,opt=-1;
    dp[layer][mid]=INF;
    for(int i=optl;i<=min(mid-1,optr);i++)
    {
        if(dp[layer][mid]>dp[layer-1][i]+(sum[mid]-sum[i])*(mid-i-1))
        {
            dp[layer][mid]=dp[layer-1][i]+(sum[mid]-sum[i])*(mid-i-1);
            opt=i;
        }
    }
    solve(layer,l,mid-1,optl,opt); solve(layer,mid+1,r,opt,optr);
}

int main()
{
    scanf("%d%d%d%d",&n,&b,&s,&r);
    for(int i=0;i<r;i++)
    {
        int u,v,cost;
        scanf("%d%d%d",&u,&v,&cost);
        add_edge(u,v,cost);
    }
    dijkstra(b+1,false); dijkstra(b+1,true);
    for(int i=1;i<=n;i++) d1[i]+=d2[i];
    for(int i=1;i<=b;i++) v.push_back(d1[i]);
    v.push_back(0);
    sort(v.begin(),v.end());
    for(int i=1;i<=b;i++) sum[i]=sum[i-1]+v[i];
    for(int i=1;i<=b;i++) dp[0][i]=INF;
    for(int i=1;i<=s;i++) solve(i,1,b,0,b-1);
    printf("%lld\n",dp[s][b]);
    return 0;
}
