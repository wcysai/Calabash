/*************************************************************************
    > File Name: L.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-12-09 01:19:41
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define INV2 500000004
#define INV4 250000002
#define INV8 125000001
#define INV24 41666667
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
int T,n,m,ans,tri,sqr,deg[MAXN],a[MAXN],cnt[MAXN],r[MAXN];
vector<int> G[MAXN];
vector<int> gr[MAXN];
bool cmp(int x,int y)
{
    return deg[x]<deg[y];
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        memset(deg,0,sizeof(deg));
        for(int i=1;i<=n;i++) G[i].clear(),gr[i].clear();
        for(int i=1;i<=n;i++) a[i]=i;
        for(int i=0;i<m;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            G[u].push_back(v);G[v].push_back(u);
            deg[u]++;deg[v]++;
        }
        sort(a+1,a+n+1,cmp);
        for(int i=1;i<=n;i++) r[a[i]]=i;
        for(int i=1;i<=n;i++)
            for(auto to:G[i]) if(r[to]>r[i]) gr[i].push_back(to);
        ans=0;tri=0;sqr=0;
        //square
        for(int i=1;i<=n;i++)
        {
            for(auto u:G[i])
            {
                for(auto to:gr[u])
                {
                    if(r[to]>r[i])
                    {
                        add(sqr,cnt[to]);
                        cnt[to]++;
                    }
                }
            }
            for(auto u:G[i])
                for(auto to:gr[u])
                    if(r[to]>r[i]) cnt[to]--;
        }
        add(ans,sqr);
        //triangle plus an edge
        int save=0;
        for(int i=1;i<=n;i++)
        {
            for(auto u:gr[i]) cnt[u]++;
            for(auto u:gr[i])
                for(auto to:gr[u])
                {
                    if(cnt[to])
                    {

                        add(tri,1);
                        add(save,deg[i]-2);
                        add(save,deg[u]-2);
                        add(save,deg[to]-2);
                    }
                }
            for(auto u:gr[i]) cnt[u]--;
        }
        add(ans,save);
        //claw
        for(int i=1;i<=n;i++)
            if(deg[i]>=4) add(ans,1LL*deg[i]*(deg[i]-1)%MOD*(deg[i]-2)%MOD*(deg[i]-3)%MOD*INV24%MOD);
        //Y
        for(int i=1;i<=n;i++)
            for(auto u:G[i]) add(ans,1LL*(deg[u]-1)*(deg[i]-1)%MOD*(deg[i]-2)%MOD*INV2%MOD);
        dec(ans,2LL*save%MOD);
        //chain
        for(int i=1;i<=n;i++)
        {
            int sum=0;
            for(auto u:G[i]) add(sum,deg[u]-1);
            for(auto u:G[i]) add(ans,1LL*(deg[u]-1)*(sum-deg[u]+1)%MOD*INV2%MOD);
        }
        dec(ans,4LL*sqr%MOD);dec(ans,3LL*tri%MOD);dec(ans,2LL*save%MOD);
        printf("%d\n",ans);
    }
    return 0;
}

