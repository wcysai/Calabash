#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,d;
vector<P> G[MAXN];
int deg[MAXN],need[MAXN];
bool rem[MAXN];
int main()
{
    scanf("%d%d%d",&n,&m,&d);
    for(int i=0;i<m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(P(v,i));G[v].push_back(P(u,i));
        deg[u]++;deg[v]++;
    }
    memset(rem,true,sizeof(rem));
    int mind=INF;
    for(int i=1;i<=n;i++) mind=min(mind,deg[i]);
    if(mind<d-1)
    {
        puts("NO");
        return 0;
    }
    if(mind==d-1)
    {
        
    }
    return 0;
}

