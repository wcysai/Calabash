/*************************************************************************
    > File Name: G.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-07-25 12:29:20
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
int n,q,b[MAXN];
const int K=400;
struct seg
{
    int minval[4*MAXN],minpos[4*MAXN],ans[4*MAXN],lazy[4*MAXN];
    void Lazy(int k)
    {
        for(int i=k*2;i<=k*2+1;i++)
        {
            minval[i]+=lazy[k];
            lazy[i]+=lazy[k];
        }
        lazy[k]=0;
    }
    void merge(int k)
    {
        if(minval[k*2]<=minval[k*2+1])
        {
            minval[k]=minval[k*2];
            minpos[k]=minpos[k*2];
        }
        else
        {
            minval[k]=minval[k*2+1];
            minpos[k]=minpos[k*2+1];
        }
    }
    void build(int k,int l,int r)
    {
        ans[k]=0;lazy[k]=0;
        if(l==r) 
        {
            lazy[k]=0;
            minval[k]=b[l];minpos[k]=l;return;
        }
        int mid=(l+r)/2;
        build(k*2,l,mid);build(k*2+1,mid+1,r);
        merge(k);
    }
    void modify(int k,int l,int r,int x,int y,int v)
    {
        if(x>r||y<l) return;
        if(l>=x&&r<=y)
        {
            minval[k]+=v;
            lazy[k]+=v;return;
        }
        Lazy(k);
        int mid=(l+r)/2;
        modify(k*2,l,mid,x,y,v);modify(k*2+1,mid+1,r,x,y,v);
        merge(k);
    }
    void modify2(int k,int l,int r,int x)
    {
        if(x<l||x>r) return;
        if(x==l&&x==r) {ans[k]++; return;}
        int mid=(l+r)/2;
        Lazy(k);
        modify2(k*2,l,mid,x);modify2(k*2+1,mid+1,r,x);
        ans[k]=ans[k*2]+ans[k*2+1];
    }
    void update()
    {
        while(minval[1]==0) 
        {
            //printf("%d %d",minpos[1],minval[1]);
            modify2(1,1,n,minpos[1]);
            modify(1,1,n,minpos[1],minpos[1],b[minpos[1]]);
            //printf("%d %d \n",minpos[1],minval[1]);
        }
    }
    int query(int k,int l,int r,int x,int y)
    {
        if(x>r||y<l) return 0;
        if(l>=x&&r<=y) return ans[k];
        Lazy(k);
        int mid=(l+r)/2;
        return query(k*2,l,mid,x,y)+query(k*2+1,mid+1,r,x,y);
    }
}segtree;
string str;
int main()
{
    while(scanf("%d%d",&n,&q)==2)
    {
        for(int i=1;i<=n;i++) scanf("%d",&b[i]);
        segtree.build(1,1,n);
        int l,r;
        for(int i=0;i<q;i++)
        {
            cin>>str;scanf("%d%d",&l,&r);
            if(str[0]=='a') 
            {
                segtree.modify(1,1,n,l,r,-1);
                segtree.update();
            }
            else
            {
                printf("%d\n",segtree.query(1,1,n,l,r));
            }
        }
    }
    return 0;
}
