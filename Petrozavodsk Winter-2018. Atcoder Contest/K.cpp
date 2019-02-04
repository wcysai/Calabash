#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000001
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,a[MAXN];
vector<int> G[MAXN];
vector<int> cur;
bool vis[MAXN];
int minx;
void dfs(int v)
{
    vis[v]=true;
    cur.push_back(a[v]);
    minx=min(minx,a[v]);
    for(auto to:G[v])
    {
        if(vis[to]) continue;
        dfs(to);
    }
}
multiset<int> s;
int cnt=0;
ll ans;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=0;i<m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);u++;v++;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    memset(vis,false,sizeof(vis));
    for(int i=1;i<=n;i++)
    {
        if(!vis[i])
        {
            minx=INF;cur.clear();cnt++;
            dfs(i);
            ans+=minx;
            for(auto x:cur)
            {
                if(x==minx) minx=INF;
                else s.insert(x);
            }
        }
    }
    if(n<2*(cnt-1))
    {
        puts("Impossible");
        return 0;
    }
    else if(cnt==1)
    {
        puts("0");
        return 0;
    }
    else
    {
        int need=2*(cnt-1)-cnt;
        for(auto x:s)
        {
            if(!need) break;
            ans+=x;
            need--;
        }
        printf("%lld\n",ans);
    }
    return 0;
}

