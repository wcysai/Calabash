#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 500005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,t,a[MAXN],ans[MAXN];
vector<P> query[MAXN];
vector<int> st[MAXN];
struct segtree
{
    int maxi[4*MAXN];
    void pushup(int k)
    {
        maxi[k]=max(maxi[k*2],maxi[k*2+1]);
    }
    void update(int k,int l,int r,int p,int v)
    {
        if(l==r)
        {
            maxi[k]=v;
            return;
        }
        int mid=(l+r)/2;
        if(p<=mid) update(k*2,l,mid,p,v); else update(k*2+1,mid+1,r,p,v);
        pushup(k);
    }
    int query(int k,int l,int r,int x,int y)
    {
        if(l>y||x>r) return 0;
        if(l>=x&&r<=y) return maxi[k];
        int mid=(l+r)/2;
        return max(query(k*2,l,mid,x,y),query(k*2+1,mid+1,r,x,y));
    }
}seg[2];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    t=0;
    for(int i=1;i<=m;i++)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        query[r].push_back(P(l,i));
    }
    for(int i=1;i<=n;i++)
    {
        while(t>0&&a[st[t-1][0]]<a[i])
        {
            for(int j=0;j<(int)st[t-1].size();j++) seg[0].update(1,1,n,st[t-1][j],st[t-1].back()-st[t-1][j]);
            t--;
        }
        if(t>0&&a[st[t-1][0]]==a[i])
        {
            st[t-1].push_back(i);
            seg[1].update(1,1,n,st[t-1][0],i-st[t-1][0]);
        }
        else
        {
            st[t].clear();
            st[t++].push_back(i);
        }
        for(auto p:query[i])
        {
            int x=p.F,id=p.S;
            ans[id]=seg[0].query(1,1,n,x,i);
            int l=-1,r=t;
            while(r-l>1)
            {
                int mid=(l+r)/2;
                if(st[mid][0]>=x) r=mid; else l=mid;
            }
            if(r!=t) ans[id]=max(ans[id],seg[1].query(1,1,n,st[r][0],n));
            if(r!=0)
            {
                int lb=-1,rb=(int)st[r-1].size();
                while(rb-lb>1)
                {
                    int mid=(lb+rb)/2;
                    if(st[r-1][mid]>=x) rb=mid; else lb=mid;
                }
                if(rb!=(int)st[r-1].size()) ans[id]=max(ans[id],st[r-1].back()-st[r-1][rb]);
            }
        }
    }
    for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
    return 0;
}
