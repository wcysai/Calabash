#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,k;
struct edge {int to,parity;};
vector<edge> G[MAXN];
int cycle,par[MAXN];
int color[MAXN];
bool f;
int pow_mod(int a,int i)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
void add_edge(int u,int v,int parity)
{
    G[u].push_back((edge){v,parity});
    G[v].push_back((edge){u,parity});
}
void dfs(int v,int p,int parity)
{
    color[v]=1;
    par[v]=parity;
    for(auto e:G[v])
    {
        if(e.to==p) continue;
        if(color[e.to]==0) dfs(e.to,v,parity^e.parity);
        else if(color[e.to]==1)
        {
            if(parity^e.parity^par[e.to]) f=false;
            else cycle++;
        }
        else continue;
    }
    color[v]=2;
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=0;i<k;i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        if(x%2==0&&y%2==0) z^=1;
        add_edge(x,n+y,z);
    }
    memset(color,0,sizeof(color));
    f=true;
    for(int i=1;i<=n+m;i++) if(!color[i]) dfs(i,0,0);
    if(!f) puts("0");
    else printf("%d\n",pow_mod(2,n+m-1-(k-cycle)));
    return 0;
}
