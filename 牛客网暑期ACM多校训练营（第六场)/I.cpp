/*************************************************************************
    > File Name: I.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com
    > Created Time: 2018-08-04 13:49:22
 ************************************************************************/
 
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000005
#define MOD 998244353
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,m,tot;
vector<P> v[MAXN];
vector<int> xx;
P a[MAXN];
int tt[MAXN];
struct segtree
{
    int val[4*MAXN];
    void build(int k,int l,int r)
    {
        val[k]=-INF;
        if(l==r) return;
        int mid=(l+r)/2;
        build(k*2,l,mid);build(k*2+1,mid+1,r);
    }
    void update(int k,int l,int r,int pos,int num)
    {
        if(l==r) {val[k]=num; return;}
        int mid=(l+r)/2;
        if(pos<=mid) update(k*2,l,mid,pos,num);
        else update(k*2+1,mid+1,r,pos,num);
        val[k]=max(val[k*2],val[k*2+1]);
    }
    int query(int k,int l,int r,int num)
    {
        if(l==r) return l;
        int mid=(l+r)/2;
        if(val[k*2]>=num) return query(k*2,l,mid,num); else return query(k*2+1,mid+1,r,num);
    }
}seg;
int main()
{
    tot=0;
    scanf("%d",&T);
    while(T--)
    {
        memset(tt,0,sizeof(tt));
        tot++;
        scanf("%d%d",&n,&m);
        xx.clear();
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d",&a[i].x,&a[i].y);
            xx.push_back(a[i].x);
        }
        sort(xx.begin(),xx.end());
        xx.erase(unique(xx.begin(),xx.end()),xx.end());
        int sz=(int)xx.size();
        seg.build(1,1,sz+1);
        for(int i=1;i<=sz;i++) v[i].clear();
        for(int i=1;i<=n;i++)
        {
            int pos=lower_bound(xx.begin(),xx.end(),a[i].x)-xx.begin();pos++;
            v[pos].push_back(P(a[i].y,i));
        }
        for(int i=1;i<=sz;i++) sort(v[i].begin(),v[i].end());
        for(int i=1;i<=sz;i++) if(v[i].size()) seg.update(1,1,sz+1,i,v[i].back().x);
        int ans=0,res=0;
        //printf("sz=%d\n",sz);
        printf("Case #%d:\n",tot);
        for(int i=1;i<=m;i++)
        {
            int p;
            scanf("%d",&p);
            p=p^res;ans=0;res=1;
            //for(int i=1;i<=7;i++) printf("%d ",seg.val[i]);
            //puts("");
            int pos=seg.query(1,1,sz+1,p);
            //printf("%d %d %d\n",i,p,pos);
            while(pos<=sz&&xx[pos-1]<=p)
            {
                ans++;
                int id=v[pos].back().y;
                res=1LL*res*id%MOD;
                tt[id]=i;
                v[pos].pop_back();
                if(v[pos].size()) seg.update(1,1,sz+1,pos,v[pos].back().x); else seg.update(1,1,sz+1,pos,-INF);
                pos=seg.query(1,1,sz+1,p);
            }
            printf("%d\n",ans);
            if(ans==0) res=0;
        }
        for(int i=1;i<=n;i++) printf("%d%c",tt[i],(i==n?'\n':' '));
    }
    return 0;
}
