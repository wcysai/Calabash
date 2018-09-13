/*************************************************************************
    > File Name: G.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-08-13 14:05:39
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 205
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,q,mp[MAXN*MAXN];
int fa[MAXN*MAXN];
struct segtree
{
    int L[4*MAXN][MAXN],R[4*MAXN][MAXN],w[4*MAXN],b[4*MAXN];
    int find(int x)
    {
        if(fa[x]==x) return x;
        return fa[x]=find(fa[x]);
    }
    void merge(int k,int l,int r)
    {
        int mid=(l+r)/2;
        w[k]=w[k*2]+w[k*2+1];
        b[k]=b[k*2]+b[k*2+1];
        for(int i=1;i<=n;i++) fa[L[k*2][i]]=L[k*2][i],fa[R[k*2][i]]=R[k*2][i];
        for(int i=1;i<=n;i++) fa[L[k*2+1][i]]=L[k*2+1][i],fa[R[k*2+1][i]]=R[k*2+1][i];
        for(int i=1;i<=n;i++)
        {
            if(mp[(i-1)*n+mid]==mp[(i-1)*n+mid+1])
            {
                int x=find(R[k*2][i]),y=find(L[k*2+1][i]);
                if(x!=y)
                {
                    if(mp[(i-1)*n+mid]) b[k]--; else w[k]--;
                    fa[y]=x;
                }
            }
        }
        for(int i=1;i<=n;i++) L[k][i]=find(L[k*2][i]),R[k][i]=find(R[k*2+1][i]);
    }
    void build(int k,int l,int r)
    {
        if(l==r)
        {
            b[k]=w[k]=0;
            for(int i=1;i<=n;i++) L[k][i]=R[k][i]=(i-1)*n+l;
            for(int i=1;i<=n;i++) 
            {
                if(i!=1&&mp[(i-1)*n+l]==mp[(i-2)*n+l]) L[k][i]=R[k][i]=L[k][i-1];
                else {if(mp[(i-1)*n+l]) b[k]++; else w[k]++;}
            }
            return;
        }
        int mid=(l+r)/2;
        build(k*2,l,mid);build(k*2+1,mid+1,r);
        merge(k,l,r);
    }
    void update1(int k,int l,int r,int x,int y)
    {
        if(l==r)
        {
            mp[(x-1)*n+l]=1-mp[(x-1)*n+l];
            b[k]=w[k]=0;
            for(int i=1;i<=n;i++) L[k][i]=R[k][i]=(i-1)*n+l;
            for(int i=1;i<=n;i++) 
            {
                if(i!=1&&mp[(i-1)*n+l]==mp[(i-2)*n+l]) L[k][i]=R[k][i]=L[k][i-1];
                else {if(mp[(i-1)*n+l]) b[k]++; else w[k]++;}
            }
            return;
        }
        int mid=(l+r)/2;
        if(y<=mid) update1(k*2,l,mid,x,y); else update1(k*2+1,mid+1,r,x,y);
        merge(k,l,r);
    }
    void update2(int k,int l,int r,int y)
    {
        if(l==r)
        {
            for(int i=1;i<=n;i++)
                mp[(i-1)*n+l]=1-mp[(i-1)*n+l];
            b[k]=w[k]=0;
            for(int i=1;i<=n;i++) L[k][i]=R[k][i]=(i-1)*n+l;
            for(int i=1;i<=n;i++) 
            {
                if(i!=1&&mp[(i-1)*n+l]==mp[(i-2)*n+l]) L[k][i]=R[k][i]=L[k][i-1];
                else {if(mp[(i-1)*n+l]) b[k]++; else w[k]++;}
            }
            return;
        }
        int mid=(l+r)/2;
        if(y<=mid) update2(k*2,l,mid,y); else update2(k*2+1,mid+1,r,y);
        merge(k,l,r);
    }
    void query()
    {
        int ans1=w[1],ans2=b[1];
        for(int i=1;i<=n;i++) fa[L[1][i]]=L[1][i],fa[R[1][i]]=R[1][i];
        for(int i=1;i<=n;i++)
        {
            if(mp[(i-1)*n+1]==mp[(i-1)*n+n])
            {
                //printf("same %d\n",i);
                int x=find(L[1][i]),y=find(R[1][i]);
                if(x!=y)
                {
                    if(mp[(i-1)*n+1]) ans2--; else ans1--;
                    fa[y]=x;
                    //printf("checked %d\n",i);
                }
            }
        }
        printf("%d %d\n",ans1,ans2);
    }
}seg;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) scanf("%d",&mp[(i-1)*n+j]);
        seg.build(1,1,n);
        scanf("%d",&q);
        for(int i=0;i<q;i++)
        {
            int t,x,y;
            scanf("%d",&t);
            if(t==1)
            {
                scanf("%d",&y);
                seg.update2(1,1,n,y);
            }
            else
            {
                scanf("%d%d",&x,&y);
                seg.update1(1,1,n,x,y);
            }
            seg.query();
        }
    }
    return 0;
}
