#include<bits/stdc++.h>
#define MAXN 2005
#define INF 1000000000000000005LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T;
int n;
struct node
{
    ll lmax,rmax,sum,maxi;
    void update(node &lnode,node &rnode)
    {
        sum=lnode.sum+rnode.sum;
        lmax=max(lnode.lmax,lnode.sum+rnode.lmax);
        rmax=max(rnode.rmax,rnode.sum+lnode.rmax);
        maxi=max(max(lnode.maxi,rnode.maxi),lnode.rmax+rnode.lmax);
    }
    void init(int x)
    {
        sum=x;
        lmax=rmax=maxi=max(x,0);
    }
    void add(int x)
    {
        sum+=x;
        lmax=rmax=maxi=max(sum,0LL);
    }
};
struct segtree
{
    node val[4*MAXN];
    void pushup(int k)
    {
        val[k].update(val[k*2],val[k*2+1]);
    }
    void build(int k,int l,int r)
    {
        val[k].init(0);
        if(l==r) return;
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
    }
    void update(int k,int l,int r,int p,int v)
    {
        if(l==r)
        {
            val[k].add(v);
            return;
        }
        int mid=(l+r)/2;
        if(p<=mid) update(k*2,l,mid,p,v); else update(k*2+1,mid+1,r,p,v);
        pushup(k);
    }
    ll query()
    {
        return val[1].maxi;
    }
}seg;
int x[MAXN],y[MAXN],w[MAXN];
vector<int> disx,disy;
vector<P> upd[MAXN];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d%d%d",&x[i],&y[i],&w[i]);
        disx.clear(); disy.clear();
        for(int i=1;i<=n;i++) disx.push_back(x[i]),disy.push_back(y[i]);
        sort(disx.begin(),disx.end()); disx.erase(unique(disx.begin(),disx.end()),disx.end());
        sort(disy.begin(),disy.end()); disy.erase(unique(disy.begin(),disy.end()),disy.end());
        int szx=(int)disx.size(),szy=(int)disy.size();
        for(int i=1;i<=szx;i++) upd[i].clear();
        for(int i=1;i<=n;i++)
        {
            x[i]=lower_bound(disx.begin(),disx.end(),x[i])-disx.begin()+1;
            y[i]=lower_bound(disy.begin(),disy.end(),y[i])-disy.begin()+1;
            upd[x[i]].push_back(P(y[i],w[i]));
        }
        ll ans=0;
        for(int i=1;i<=szx;i++)
        {
            seg.build(1,1,szy);
            for(int j=i;j<=szx;j++)
            {
                for(auto p:upd[j]) seg.update(1,1,szy,p.F,p.S);
                ans=max(ans,seg.query());
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
