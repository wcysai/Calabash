/*************************************************************************
    > File Name: E.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-09-15 14:11:30
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef unsigned long long ll;
typedef pair<int,int> P;
int tot,q,n,k;
int pa[MAXN],dep[MAXN],sz[MAXN],wson[MAXN],top[MAXN],spos[MAXN];
//form:ax+b
const unsigned long long hulu=0ULL-1;
struct segtree
{
    ll val[4*MAXN],lzy1[4*MAXN],lzy2[4*MAXN];//lzy1: multiply tag, lzy2: add tag
    void Lazy(int k,int l,int r)
    {
        int mid=(l+r)/2;
        for(int i=k*2;i<=k*2+1;i++)
        {
            int len;
            if(i==k*2) len=mid-l+1; else len=r-mid;
            lzy1[i]*=lzy1[k];val[i]*=lzy1[k];lzy2[i]*=lzy1[k];
            lzy2[i]+=lzy2[k];val[i]+=(len)*lzy2[k];
        }
        lzy1[k]=1;lzy2[k]=0;
    }
    void build(int k,int l,int r)
    {
        val[k]=0;lzy1[k]=1;lzy2[k]=0;
        if(l==r) return;
        int mid=(l+r)/2;
        build(k*2,l,mid);build(k*2+1,mid+1,r);
    }      
    void update1(int k,int l,int r,int x,int y,ll v) //add
    {
        if(l>y||x>r) return;
        if(l>=x&&r<=y) 
        {
            lzy2[k]+=v;val[k]+=v*(r-l+1);
            return;
        }
        Lazy(k,l,r);
        int mid=(l+r)/2;
        update1(k*2,l,mid,x,y,v);update1(k*2+1,mid+1,r,x,y,v);
        val[k]=val[k*2]+val[k*2+1];
    }
    void update2(int k,int l,int r,int x,int y,ll v) //multiply
    {
        if(l>y||x>r) return;
        if(l>=x&&r<=y) 
        {
            lzy1[k]*=v;lzy2[k]*=v;val[k]*=v;
            return;
        }
        Lazy(k,l,r);
        int mid=(l+r)/2;
        update2(k*2,l,mid,x,y,v);update2(k*2+1,mid+1,r,x,y,v);
        val[k]=val[k*2]+val[k*2+1];
    }
    void update3(int k,int l,int r,int x,int y) //negate
    {  
        //printf("update3 %d %d\n",l,r);
        if(l>y||x>r) return;
        if(l>=x&&r<=y) 
        {
            lzy1[k]*=hulu;lzy2[k]*=hulu;lzy2[k]-=1ULL;
            val[k]*=hulu; val[k]-=1ULL*(r-l+1);
            return;
        }
        Lazy(k,l,r);
        int mid=(l+r)/2;
        update3(k*2,l,mid,x,y);update3(k*2+1,mid+1,r,x,y);
        val[k]=val[k*2]+val[k*2+1];
    }
    ll query(int k,int l,int r,int x,int y) //query sum
    {
        if(l>y||x>r) return 0;
        if(l>=x&&r<=y) return val[k];
        Lazy(k,l,r);
        int mid=(l+r)/2;
        //printf("query %d %d %llu\n",l,r,query(k*2,l,mid,x,y)+query(k*2+1,mid+1,r,x,y));
        return query(k*2,l,mid,x,y)+query(k*2+1,mid+1,r,x,y);
    }
}tree;
vector<int> G[MAXN];
void dfs1(int v,int p,int d)
{
    dep[v]=d;pa[v]=p;sz[v]=1;
    for(int i=0;i<(int)G[v].size();i++)
    {
        int to=G[v][i];
        if(to==p) continue;
        dfs1(to,v,d+1);
        if(sz[to]>sz[wson[v]]) wson[v]=to;
        sz[v]+=sz[to];
    }
}
void dfs2(int v,int p,int num)
{
    top[v]=num;
    spos[v]=++tot;
    if(wson[v]) dfs2(wson[v],v,num);
    for(int i=0;i<(int)G[v].size();i++)
    {
        int to=G[v][i];
        if(to==p||to==wson[v]) continue;
        dfs2(to,v,to);
    }
}
void init()
{
    tot=0;dfs1(1,1,1);
    dfs2(1,0,1);
    tree.build(1,1,n);
}
void update1(int u,int v,int x)
{
    while(top[u]!=top[v])
    {
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        tree.update1(1,1,n,spos[top[u]],spos[u],x);
        u=pa[top[u]];
    }
    if(dep[u]<dep[v]) swap(u,v);
    tree.update1(1,1,n,spos[v],spos[u],x);
}
void update2(int u,int v,int x)
{
    while(top[u]!=top[v])
    {
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        tree.update2(1,1,n,spos[top[u]],spos[u],x);
        u=pa[top[u]];
    }
    if(dep[u]<dep[v]) swap(u,v);
    tree.update2(1,1,n,spos[v],spos[u],x);
}
void update3(int u,int v)
{
    while(top[u]!=top[v])
    {
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        tree.update3(1,1,n,spos[top[u]],spos[u]);
        u=pa[top[u]];
    }
    if(dep[u]<dep[v]) swap(u,v);
    tree.update3(1,1,n,spos[v],spos[u]);
}
ll query(int u,int v)
{
    ll ans=0;
    while(top[u]!=top[v])
    {
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        ans+=tree.query(1,1,n,spos[top[u]],spos[u]);
        u=pa[top[u]];
    }
    if(dep[u]<dep[v]) swap(u,v);
    ans+=tree.query(1,1,n,spos[v],spos[u]);
    return ans;
}
int main()
{
    while(scanf("%d",&n)==1)
    {
        memset(wson,0,sizeof(wson));
        for(int i=1;i<=n-1;i++)
        {
            int v;
            scanf("%d",&v);
            G[i+1].push_back(v);G[v].push_back(i+1);
        }
        init();
        scanf("%d",&q);
        while(q--)
        {
            int type,u,v,x;
            scanf("%d%d%d",&type,&u,&v);
            if(type==1) {scanf("%d",&x); update2(u,v,x);}
            else if(type==2) {scanf("%d",&x); update1(u,v,x);}
            else if(type==3) update3(u,v);
            else printf("%llu\n",query(u,v));
            //printf("%llu %llu %llu %llu %llu %llu\n",tree.lzy1[1],tree.lzy2[1],tree.lzy1[2],tree.lzy2[2],tree.lzy1[3],tree.lzy2[3]);
        }
        for(int i=1;i<=n;i++) {G[i].clear(); G[i].shrink_to_fit();}
    }
}
