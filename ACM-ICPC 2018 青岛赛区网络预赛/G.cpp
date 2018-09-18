/*************************************************************************
    > File Name: G.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-09-16 13:03:38
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define MAXM 4000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,q,tot,cnt,a[MAXN],root[MAXN],perm[MAXN];
ll lastans;
int lson[MAXM],rson[MAXM],sum[MAXM];
ll ans[MAXN];
bool used[MAXN];
struct node
{
    int l,r;
    ll inv;
    bool operator <(const node &rhs) const
    {
        if(l!=rhs.l) return l<rhs.l;
        return r<rhs.r;
    }
};
set<node> s;
multiset<ll> ms;
void ASS(bool x)
{
    if(!x) 
    {
        while(1);
    }
}
void build(int &k,int l,int r)
{
    k=++tot;sum[k]=0;
    if(l==r) return;
    int mid=(l+r)/2;
    build(lson[k],l,mid);build(rson[k],mid+1,r);
}
void insert(int &k,int last,int l,int r,int p)
{
    k=++tot;
    sum[k]=sum[last];
    if(l==r) {sum[k]++; return;}
    lson[k]=lson[last];rson[k]=rson[last];
    int mid=(l+r)/2;
    if(p<=mid) insert(lson[k],lson[last],l,mid,p);
    else insert(rson[k],rson[last],mid+1,r,p);
    sum[k]=sum[lson[k]]+sum[rson[k]];
}
int query(int &k,int l,int r,int x,int y)
{
    if(!k) return 0;
    if(l>y||r<x) return 0;
    if(l>=x&&r<=y) return sum[k];
    int mid=(l+r)/2;
    return query(lson[k],l,mid,x,y)+query(rson[k],mid+1,r,x,y);
}
int Query1(int l,int r,int x)
{
    return query(root[r],1,n,1,x-1)-query(root[l-1],1,n,1,x-1);
}
int Query2(int l,int r,int x)
{
    return query(root[r],1,n,x+1,n)-query(root[l-1],1,n,x+1,n);
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        cnt=0;tot=0;s.clear();ms.clear();
        scanf("%d",&n);
        for(int i=1;i<=n;i++) used[i]=false;
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        build(root[0],1,n);
        for(int i=1;i<=n;i++) insert(root[i],root[i-1],1,n,a[i]);
        lastans=0;
        for(int i=1;i<n;i++) lastans+=Query1(i+1,n,a[i]);
        ms.insert(lastans);
        s.insert((node){1,n,lastans});
        s.insert((node){n+1,n+1,0LL});
        for(int i=1;i<=n;i++) scanf("%d",&perm[i]);
        for(int i=1;i<=n;i++)
        {
            auto iter=ms.end();iter--;
            lastans=*iter;ans[i]=lastans;
            perm[i]^=lastans;
            ASS(perm[i]>=1&&perm[i]<=n&&!used[perm[i]]);
            used[perm[i]]=true;
            auto it=s.upper_bound((node){perm[i],n+1,0});it--;
            ll now=it->inv;
            //printf("l:%d r:%d\n",it->l,it->r);
            if(perm[i]==it->l&&perm[i]==it->r)
            {
                s.erase(it);
                ms.erase(ms.find(now));
            }
            else if(perm[i]==it->l)
            {
                ms.erase(ms.find(now));
                now-=Query1(it->l+1,it->r,a[perm[i]]);
                ms.insert(now);
                s.erase(it);s.insert((node){it->l+1,it->r,now});
            }
            else if(perm[i]==it->r)
            {
                ms.erase(ms.find(now));
                now-=Query2(it->l,it->r-1,a[perm[i]]);
                ms.insert(now);
                s.erase(it);s.insert((node){it->l,it->r-1,now});
            }
            else
            {
                int lhsl=it->l,lhsr=perm[i]-1,rhsl=perm[i]+1,rhsr=it->r;
                ms.erase(ms.find(now));s.erase(it);
                now-=Query1(rhsl,rhsr,a[perm[i]]);now-=Query2(lhsl,lhsr,a[perm[i]]);
                ll cur=0;
                if(lhsr-lhsl<rhsr-rhsl)
                {
                    for(int j=lhsl;j<=lhsr;j++) now-=Query1(rhsl,rhsr,a[j]);
                    for(int j=lhsl;j<lhsr;j++) cur+=Query1(j+1,lhsr,a[j]);
                    ms.insert(cur);ms.insert(now-cur);
                    s.insert((node){lhsl,lhsr,cur});s.insert((node){rhsl,rhsr,now-cur});
                }
                else
                {
                    for(int j=rhsl;j<=rhsr;j++) now-=Query2(lhsl,lhsr,a[j]);
                    for(int j=rhsl;j<rhsr;j++) cur+=Query1(j+1,rhsr,a[j]);
                    ms.insert(cur);ms.insert(now-cur);
                    s.insert((node){lhsl,lhsr,now-cur});s.insert((node){rhsl,rhsr,cur});
                }
            }
        }
        for(int i=1;i<=n;i++) printf("%lld%c",ans[i],i==n?'\n':' ');
    }
    return 0;
}
