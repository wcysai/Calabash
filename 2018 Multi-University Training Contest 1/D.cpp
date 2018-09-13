/*************************************************************************
    > File Name: D.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-07-23 12:15:24
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
int t,n,m,st[MAXN],cnt[MAXN];
P a[MAXN];
vector<int> eve[MAXN];
struct segtree
{
    int val[4*MAXN];
    void clear(int k,int l,int r)
    {
        val[k]=0;
        if(l==r) return;
        int mid=(l+r)/2;
        clear(k*2,l,mid);clear(k*2+1,mid+1,r);
    }
    void update(int k,int l,int r,int pos,int v)
    {
        if(l==r) {val[k]=v; return;}
        int mid=(l+r)/2;
        if(pos<=mid) update(k*2,l,mid,pos,v); else update(k*2+1,mid+1,r,pos,v);
        val[k]=val[k*2]+val[k*2+1];
    }
    int query(int k,int l,int r)
    {
        if(l==r) return l;
        int mid=(l+r)/2;
        int llen=mid-l+1;
        if(val[k*2]<llen) return query(k*2,l,mid); else return query(k*2+1,mid+1,r);
    }
    void Add(int x) {update(1,1,n,x,1);}
    void Del(int x) {update(1,1,n,x,0);}
    int Query()  {return query(1,1,n);}
    void Clear() {clear(1,1,n);}
}seg;
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) cnt[i]=0;
        for(int i=1;i<=n;i++) eve[i].clear();
        seg.Clear();
        for(int i=0;i<m;i++)
        {
            int l,r;
            scanf("%d%d",&l,&r);
            cnt[l]++;
            eve[r+1].push_back(l);
        }
        int now=1;
        for(int i=1;i<=n;i++)
        {
            for(int j=0;j<(int)eve[i].size();j++)
                cnt[eve[i][j]]--;
            while(now<i&&cnt[now]==0) {seg.Del(st[now]); now++; }
            st[i]=seg.Query();
            if(i!=n) printf("%d ",st[i]); else printf("%d\n",st[i]);
            seg.Add(st[i]);
        }
    }
    return 0;
}
