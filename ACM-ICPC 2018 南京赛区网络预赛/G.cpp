/*************************************************************************
    > File Name: G.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-09-01 14:22:48
 ************************************************************************/

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
int n,m,q;
int a[MAXN],cnt;
P ans[MAXN];
struct segtree
{
    int val[4*MAXN];
    void build(int k,int l,int r)
    {
        if(l==r) {val[k]=(a[l]==0?INF:a[l]);return;}
        int mid=(l+r)/2;
        build(k*2,l,mid);build(k*2+1,mid+1,r);
        val[k]=min(val[k*2],val[k*2+1]);
    }
    int query(int k,int l,int r,int v)
    {
        if(l==r) return l;
        int mid=(l+r)/2;
        if(val[k*2]<=v) return query(k*2,l,mid,v); else return query(k*2+1,mid+1,r,v);
    }
    void update(int k,int l,int r,int p)
    {
        if(l==r) {val[k]=INF; return;}
        int mid=(l+r)/2;
        if(p<=mid) update(k*2,l,mid,p); else update(k*2+1,mid+1,r,p);
        val[k]=min(val[k*2],val[k*2+1]);
    }   
}seg;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    seg.build(1,1,n);
    int now=0;cnt=0;
    for(int i=1;i<=100000;i++)
    {
        if(cnt==n) {ans[i]=P(now,cnt); continue;}
        now+=m;
        while(now>=seg.val[1])
        {
            cnt++;
            int p=seg.query(1,1,n,now);
            now-=a[p];
            a[p]=INF;
            seg.update(1,1,n,p);
        }
        ans[i]=P(now,cnt);
    }
    scanf("%d",&q);
    for(int i=0;i<q;i++)
    {
        int x;
        scanf("%d",&x);
        printf("%d %d\n",ans[x].S,ans[x].F);
    }
    return 0;
}
