/*************************************************************************
    > File Name: H.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-09-24 13:00:06
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
int T,n,q;
int p10[2*MAXN];
int _mod(int x) {return x>=MOD?x-MOD:x;}
struct segtree
{
    int ans[4*MAXN],lazy[4*MAXN],rlazy[4*MAXN],lazyl[4*MAXN],p[4*MAXN];
    void pushup(int k)
    {
        ans[k]=_mod(ans[k*2]+ans[k*2+1]);
        p[k]=_mod(p[k*2]+p[k*2+1]);
    }
    void pushdown(int k,int l,int r)
    {
        if(!lazyl[k]) return;
        int mid=(l+r)/2;
        for(int i=k*2;i<=k*2+1;i++)
        {
            lazy[i]=(1LL*p10[lazyl[k]]*lazy[i]+lazy[k])%MOD;
            rlazy[i]=(1LL*p10[lazyl[i]]*rlazy[k]+rlazy[i])%MOD;
            lazyl[i]+=lazyl[k];
            ans[i]=(1LL*p10[lazyl[k]]*ans[i]+1LL*lazy[k]*(i==k*2?(mid-l+1):(r-mid))+1LL*p10[lazyl[k]]*p[i]%MOD*rlazy[k])%MOD;
            p[i]=1LL*p[i]*p10[2*lazyl[k]]%MOD;
        }
        lazyl[k]=rlazy[k]=lazy[k]=0;
    }
    void build(int k,int l,int r)
    {
        lazy[k]=rlazy[k]=lazyl[k]=ans[k]=0;
        if(l==r)
        {
            p[k]=1;
            return;
        }
        int mid=(l+r)/2;
        build(k*2,l,mid);build(k*2+1,mid+1,r);
        pushup(k);
    }
    void update(int k,int l,int r,int x,int y,int d)
    {
        if(x>r||l>y) return;
        if(l>=x&&r<=y)
        {
            lazy[k]=(10LL*lazy[k]+d)%MOD;
            rlazy[k]=(1LL*p10[lazyl[k]]*d+rlazy[k])%MOD;
            lazyl[k]++;
            ans[k]=(10LL*ans[k]+(r-l+1)*d+10LL*p[k]*d)%MOD;
            p[k]=100LL*p[k]%MOD;
            return;
        }
        pushdown(k,l,r);
        int mid=(l+r)/2;
        update(k*2,l,mid,x,y,d);update(k*2+1,mid+1,r,x,y,d);
        pushup(k);
    }
    int query(int k,int l,int r,int x,int y)
    {
        if(x>r||l>y) return 0;
        if(l>=x&&r<=y) return ans[k];
        pushdown(k,l,r);
        int mid=(l+r)/2;
        return _mod(query(k*2,l,mid,x,y)+query(k*2+1,mid+1,r,x,y));
    }
}seg;
char str[5];
int main()
{
    p10[0]=1;
    for(int i=1;i<=200000;i++) p10[i]=10LL*p10[i-1]%MOD;
    scanf("%d",&T);
    int tot=0;
    while(T--)
    {
        tot++;
        scanf("%d%d",&n,&q);
        printf("Case %d:\n",tot);
        seg.build(1,1,n);
        int l,r,d;
        for(int i=0;i<q;i++)
        {
            scanf("%s",str);
            if(str[0]=='w')
            {
                scanf("%d%d%d",&l,&r,&d);
                seg.update(1,1,n,l,r,d);
            }
            else
            {
                scanf("%d%d",&l,&r);
                printf("%d\n",seg.query(1,1,n,l,r));
            }
        }
    }
    return 0;
}

