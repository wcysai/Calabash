/*************************************************************************
    > File Name: D.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-09-19 08:17:47
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 400005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,c[MAXN],a[MAXN],rk[MAXN],pp[MAXN],ans[MAXN];
int gcnt;
int g[MAXN];
vector<int> pos[MAXN];
struct segtree
{
    int val[4*MAXN];
    void build(int k,int l,int r)
    {
        val[k]=0;
        if(l==r) return;
        int mid=(l+r)/2;
        build(k*2,l,mid);build(k*2+1,mid+1,r);
    }
    void update(int k,int l,int r,int p)
    {
        if(l==r) {val[k]++; return;}
        int mid=(l+r)/2;
        if(p<=mid) update(k*2,l,mid,p); else update(k*2+1,mid+1,r,p);
        val[k]=val[k*2]+val[k*2+1];
    }
    int query(int k,int l,int r,int now)
    {
        if(l==r) return l;
        int mid=(l+r)/2;
        if(val[k*2+1]<=now) return query(k*2,l,mid,now-val[k*2+1]);
        else return query(k*2+1,mid+1,r,now);
    }
    int query2(int k,int l,int r,int x,int y)
    {
        if(l>y||x>r) return 0;
        if(l>=x&&r<=y) return val[k];
        int mid=(l+r)/2;
        return query2(k*2,l,mid,x,y)+query2(k*2+1,mid+1,r,x,y);
    }
    int query3(int k,int l,int r,int x)
    {
        if(l==r) return l;
        int mid=(l+r)/2;
        if(mid-l+1-val[k*2]>=x) return query3(k*2,l,mid,x);
        else return query3(k*2+1,mid+1,r,x-(mid-l+1-val[k*2]));
    }
}seg;
int main()
{
    scanf("%d",&n);gcnt=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&c[i],&a[i]);
        if(gcnt==0)
        {
            gcnt++;
            seg.update(1,1,n,gcnt);
            pos[c[i]].push_back(gcnt);
            rk[i]=1;
            continue;
        }
        int x=min(a[i],i-1);
        int p=seg.query(1,1,n,x);
        //printf("%d\n",p);
        auto it=lower_bound(pos[c[i]].begin(),pos[c[i]].end(),p);
        if(it==pos[c[i]].end())
        {
            gcnt++;
            seg.update(1,1,n,gcnt);
            pos[c[i]].push_back(gcnt);
            rk[i]=i;
            continue;
        }
        if(*it==p) rk[i]=i-x; else rk[i]=i-seg.query2(1,1,n,*it,n);
        seg.update(1,1,n,*it);
    }
    seg.build(1,1,n);
    for(int i=n;i>=1;i--)
    {
        pp[i]=seg.query3(1,1,n,rk[i]);
        seg.update(1,1,n,pp[i]);
    }
    for(int i=1;i<=n;i++) ans[pp[i]]=i;
    for(int i=1;i<=n;i++) printf("%d%c",ans[i],i==n?'\n':' ');
    return 0;
}

