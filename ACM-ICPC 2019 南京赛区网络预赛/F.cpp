#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T;
int n,k,a[MAXN],pos[MAXN],nxt[MAXN];
int len[MAXN];
struct segtree
{
    int maxi[4*MAXN];
    void pushup(int k)
    {
        maxi[k]=max(maxi[k*2],maxi[k*2+1]);
    }
    void build(int k,int l,int r)
    {
        maxi[k]=0;
        if(l==r) return;
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
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
}seg;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&k);
        seg.build(1,1,n+k);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        for(int i=1;i<=n;i++) pos[a[i]]=i;
        for(int i=1;i<=n;i++)
        {
            nxt[i]=seg.query(1,1,n+k,max(1,pos[i]-k),pos[i]+k);
            seg.update(1,1,n+k,pos[i],i);
        }
        for(int i=1;i<=n;i++)
        {
            if(!nxt[i]) len[i]=1;
            else len[i]=len[nxt[i]]+1;
        }
        for(int i=1;i<=n;i++) printf("%d%c",len[i],i==n?'\n':' ');
    }
    return 0;
}
