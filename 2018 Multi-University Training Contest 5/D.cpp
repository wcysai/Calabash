/*************************************************************************
    > File Name: D.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-08-09 01:30:00
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXLOGN 22
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,N,K,Q;
vector<int> G[MAXN];
bool centroid[MAXN];
int st[MAXLOGN][2*MAXN],pa[MAXLOGN][MAXN];
int sz[MAXN],fa[MAXN];
int root,ans,tot;
int vs[MAXN*2-1];
int depth[MAXN*2-1];
int id[MAXN];
vector<int> dist1[MAXN],dist2[MAXN];
namespace fastIO {  
    #define BUF_SIZE 100000  
    //fread -> read  
    bool IOerror = 0;  
    inline char nc() {  
        static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = buf + BUF_SIZE;  
        if(p1 == pend) {  
            p1 = buf;  
            pend = buf + fread(buf, 1, BUF_SIZE, stdin);  
            if(pend == p1) {  
                IOerror = 1;  
                return -1;  
            }  
        }  
        return *p1++;  
    }  
    inline bool blank(char ch) {  
        return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';  
    }  
    inline void read(int &x) {  
        char ch;  
        while(blank(ch = nc()));  
        if(IOerror)  
            return;  
        for(x = ch - '0'; (ch = nc()) >= '0' && ch <= '9'; x = x * 10 + ch - '0');  
    }  
    #undef BUF_SIZE  
};  
using namespace fastIO;
void dfs(int v,int p,int d,int &k)
{
    id[v]=k;
    vs[k]=v;
    depth[k++]=d;
    pa[0][v]=p;
    for(int i=0;i<(int)G[v].size();i++)
    {
        if(G[v][i]!=p)
        {
            dfs(G[v][i],v,d+1,k);
            vs[k]=v;
            depth[k++]=d;
        }
    }
}
int getMin(int x, int y)
{
    return depth[x]<depth[y]?x:y;
}

void rmq_init(int n)
{
    for(int i=1;i<=n;++i) st[0][i]=i;
    for(int i=1;1<<i<n;++i)
        for(int j=1;j+(1<<i)-1<=n;++j)
            st[i][j]=getMin(st[i-1][j],st[i-1][j+(1<<(i-1))]);
}
void init(int V)
{
    int k=0;
    dfs(1,0,0,k);
    rmq_init(V*2-1);
}
void init2(int V)
{
    for(int k=0;k+1<MAXLOGN;k++)
    {
        for(int v=1;v<=V;v++)
        {
            if(pa[k][v]<=0) pa[k+1][v]=0;
            else pa[k+1][v]=pa[k][pa[k][v]];
        }
    }
}
int query(int l, int r)
{
    int k=31-__builtin_clz(r-l+1);
    return getMin(st[k][l],st[k][r-(1<<k)+1]);
}
int lca(int u,int v)
{
    if(u==v) return u;
    return vs[query(min(id[u],id[v]),max(id[u],id[v]))];
}
int dis(int u,int v)
{
    return depth[id[u]]+depth[id[v]]-2*depth[id[lca(u,v)]];
}
P getroot(int v,int p,int t)//search_centroid
{
    P res=P(INT_MAX,-1);
    int m=0;
    sz[v]=1;
    for(int i=0;i<(int)G[v].size();i++)
    {
        int to=G[v][i];
        if(to==p||centroid[to]) continue;
        res=min(res,getroot(to,v,t));
        m=max(m,sz[to]);
        sz[v]+=sz[to];
    }
    m=max(m,t-sz[v]);
    res=min(res,P(m,v));
    return res;
}
void getdeep(int v,int p,int rt1,int rt2)//enumerate path
{
    int x1=dis(v,rt1),x2=dis(v,rt2);
    if(x1>=(int)dist1[rt1].size()) dist1[rt1].resize(x1+1);
    dist1[rt1][x1]++;
    if(rt2)
    {
        if(x2>=(int)dist2[rt1].size()) dist2[rt1].resize(x2+1);
        dist2[rt1][x2]++;
    }
    for(int i=0;i<(int)G[v].size();i++)
    {
        int to=G[v][i];
        if(to==p||centroid[to]) continue;
        getdeep(to,v,rt1,rt2);
    }
}
void solve(int v,int p)
{
    centroid[v]=true;fa[v]=p;
    getdeep(v,0,v,p);
    for(int i=1;i<(int)dist1[v].size();i++) dist1[v][i]+=dist1[v][i-1];
    for(int i=1;i<(int)dist2[v].size();i++) dist2[v][i]+=dist2[v][i-1];
    for(int i=0;i<(int)G[v].size();i++)
    {
        int to=G[v][i];
        if(centroid[to]) continue;
        root=getroot(to,v,sz[to]).S;
        solve(root,v);
    }
    root=v;
}
void pre()
{
    init(N);
    init2(N);
    root=getroot(1,0,N).S;
    solve(root,0);
}
int Query(int v,int k)
{
    if(k<0) return 0;
    int ans=0;
    if(k<(int)dist1[v].size()) ans=dist1[v][k]; else ans=dist1[v].back();
    int t=v;
    while(fa[v])
    {
        int rem=k-dis(fa[v],t);
        if(rem>=0)
        {
            int cnt1,cnt2;
            if(rem<(int)dist1[fa[v]].size()) cnt1=dist1[fa[v]][rem]; else cnt1=dist1[fa[v]].back();
            if(rem<(int)dist2[v].size()) cnt2=dist2[v][rem]; else cnt2=dist2[v].back();
            ans+=cnt1-cnt2;
        }
        v=fa[v];
    }
    return ans;
}
int main()
{
    read(T);
    while(T--)
    {
        read(N);read(Q);tot=N;
        for(int i=1;i<=2*N;i++)
            G[i].clear(),dist1[i].clear(),dist2[i].clear();
        for(int i=0;i<N-1;i++)
        {
            int u,v;
            read(u);read(v);
            tot++;
            G[tot].push_back(v);G[v].push_back(tot);
            G[tot].push_back(u);G[u].push_back(tot);
        }
        swap(N,tot);
        for(int i=1;i<=N;i++) centroid[i]=false;
        pre();
        int lastans=0;
        for(int i=0;i<Q;i++)
        {
            int u,v,w;
            read(u);read(v);read(w);
            u=(u+lastans)%tot+1,v=(v+lastans)%tot+1,w=(w+lastans)%tot;
            int k=lca(u,v),dd=dis(u,v)/2,node;
            if(dis(u,k)>=dd) node=u; else node=v;
            int needed=dd;
            for(int p=0;p<MAXLOGN;p++)
                if(needed>>p&1) node=pa[p][node];
            //printf("%d %d\n",node,2*w-dis(u,v)/2);
            //printf("%d %d %d\n",Query(u,2*w),Query(v,2*w),Query(node,2*w-dis(u,v)/2));
            lastans=(Query(v,2*w)+1)/2+(Query(u,2*w)+1)/2-(Query(node,2*w-dis(u,v)/2)+1)/2;
            printf("%d\n",lastans);
        }
    }
    return 0;
}
