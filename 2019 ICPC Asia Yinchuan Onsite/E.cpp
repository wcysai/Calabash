#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> P;
int n,k,a[MAXN],len[MAXN],son[MAXN];
int st[MAXN],ed[MAXN];
int cnt[MAXN][4],save[MAXN][4];
ull ans[MAXN];
int curi,curj;
ull res;
vector<int> G[MAXN];
void dfs(int v,int p)
{
    for(auto to:G[v])
    {
        if(to==p) continue;
        dfs(to,v);
        if(len[to]>len[son[v]]) son[v]=to;
    }
    len[v]=len[son[v]]+1;
}
void dfs2(int v,int p)
{
    if(son[v])
    {
        st[son[v]]=st[v]+1;
        dfs2(son[v],v);
        ed[v]=ed[son[v]];
        for(int i=0;i<4;i++)
        {
            cnt[v][i]=cnt[son[v]][i];
            save[st[v]][i]=0;
        }
    }
    else
    {
        ed[v]=st[v];
        for(int i=0;i<4;i++)
        {
            cnt[v][i]=0;
            save[st[v]][i]=0;
        }
    }
    int x=(((a[v]>>curi)&1)<<1)+((a[v]>>curj)&1);
    save[st[v]][x]=1;
    cnt[v][x]++;
    while(ed[v]-st[v]>k)
    {
        for(int i=0;i<4;i++) cnt[v][i]-=save[ed[v]][i];
        ed[v]--;
    }
    for(auto to:G[v])
    {
        if(to==p||to==son[v]) continue;
        st[to]=ed[v]+1;
        dfs2(to,v);
        for(int i=st[to];i<=ed[to]&&i-st[to]<=k;i++)
            for(int j=0;j<4;j++)
            {
                save[i-st[to]+1+st[v]][j]+=save[i][j];
                cnt[v][j]+=save[i][j];
            }
    }
    ans[v]+=res*cnt[v][0]*cnt[v][3];
    ans[v]+=res*cnt[v][1]*cnt[v][2];
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=2;i<=n;i++)
    {
        int f;
        scanf("%d",&f);
        G[f].push_back(i);
        G[i].push_back(f);
    }
    dfs(1,0);
    for(curi=0;curi<30;curi++)
        for(curj=0;curj<=curi;curj++)
        {
            if(curi==curj) res=1ULL<<(curi+curj); else res=1ULL<<(curi+curj+1);
            st[1]=1;
            dfs2(1,0);
        }
    for(int i=1;i<=n;i++) printf("%llu\n",ans[i]);
    return 0;
}


