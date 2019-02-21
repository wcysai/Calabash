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
int n,m,deg[MAXN],a[MAXN],cnt[MAXN],r[MAXN];
int tri[MAXN],rect[MAXN];
ll ans[MAXN];
ll walk3[MAXN];
ll dp[MAXN][5];
vector<int> G[MAXN];
vector<int> gr[MAXN];
vector<int> save[MAXN];
bool cmp(int x,int y)
{
    return deg[x]<deg[y];
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) a[i]=i;
    for(int i=0;i<m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v);G[v].push_back(u);
        deg[v]++;deg[u]++;
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++) r[a[i]]=i;
    for(int i=1;i<=n;i++)
        for(auto to:G[i])
            if(r[to]>r[i]) gr[i].push_back(to);
    for(int i=1;i<=n;i++)
    {
        for(auto u:gr[i]) cnt[u]++;
        for(auto u:gr[i])
            for(auto to:gr[u])
            {
                if(cnt[to])
                {
                    tri[i]++;
                    tri[u]++;
                    tri[to]++;
                }
            }
        for(auto u:gr[i]) cnt[u]--;
    }
    for(int i=1;i<=n;i++)
    {
        for(auto u:G[i])
        {
            for(auto to:gr[u])
            {
                if(r[to]>r[i])
                {
                    rect[i]+=cnt[to];
                    rect[to]+=cnt[to];
                    cnt[to]++;save[to].push_back(u);
                }
            }
        }
        for(auto u:G[i])
        {
            for(auto to:gr[u])
            {
                if(r[to]>r[i]) 
                {
                    cnt[to]--;
                    if(save[to].size())
                    {
                        for(auto v:save[to])
                        {
                            rect[v]+=(int)save[to].size()-1;
                        }
                        save[to].clear();
                    }
                }
            }
        }
    }
    for(int i=1;i<=n;i++) dp[i][0]=1;
    for(int i=1;i<=4;i++)
    {
        for(int v=1;v<=n;v++)
            for(auto to:G[v])
                dp[v][i]+=dp[to][i-1];
    }
    for(int i=1;i<=n;i++) ans[i]=dp[i][4];
    for(int i=1;i<=n;i++) walk3[i]=dp[i][3];
    for(int i=1;i<=n;i++)
    {
        int sz=(int)G[i].size();
        ans[i]-=sz;walk3[i]-=sz;
    }
    for(int i=1;i<=n;i++) ans[i]-=2*rect[i];
    for(int i=1;i<=n;i++) ans[i]-=6*tri[i];
    for(int i=1;i<=n;i++)
    {
        for(auto to:G[i])
        {
            int sz=(int)G[to].size()-1;
            ans[i]-=3*sz;
            walk3[i]-=sz;
        }
    }
    for(int i=1;i<=n;i++)
    {
        int sz=(int)G[i].size();
        ans[i]-=1LL*sz*(sz-1);
        walk3[i]-=1LL*sz*(sz-1);
    }
    for(int i=1;i<=n;i++) walk3[i]-=2*tri[i];
    for(int i=1;i<=n;i++) ans[i]-=walk3[i];
    for(int i=1;i<=n;i++) 
    {
        int sz1=(int)G[i].size()-1;
        for(auto to:G[i])
        {
            int sz2=(int)G[to].size()-1;
            ans[i]-=1LL*sz1*sz2;
        }
        ans[i]+=2*tri[i];
    }
    for(int i=1;i<=n;i++)
    {
        for(auto to:G[i])
        {
            int sz=(int)G[to].size()-1;
            ans[i]-=1LL*sz*(sz-1);
        }
    }  
    for(int i=1;i<=n;i++)
    {
        for(auto to:G[i]) ans[i]-=2*tri[to];
        ans[i]+=4*tri[i];
    }
    for(int i=1;i<=n;i++)
    {
        int sz=(int)G[i].size();
        if(sz>=3) ans[i]-=2LL*tri[i]*(sz-2);
    }
    for(int i=1;i<=n;i++) printf("%lld\n",ans[i]);
    return 0;
}

