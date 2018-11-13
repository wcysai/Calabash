#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
#define x1 fdsijfoi
#define x2 fdsijfosd
#define y1 dcjioasfjk
#define y2 daiojf
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,k;
vector<P> eve[MAXN];
vector<int> v1;
vector<int> v2;
int x1[MAXN],x2[MAXN],y1[MAXN],y2[MAXN];
int len[MAXN];
struct segtree
{
    int sum[4*MAXN],lazy[4*MAXN],save[4*MAXN];
    void pushup(int k) {sum[k]=sum[k*2]+sum[k*2+1];}
    void pushdown(int k)
    {
        if(!lazy[k]) return;
        lazy[k*2]=lazy[k*2]^1; sum[k*2]=save[k*2]-sum[k*2];
        lazy[k*2+1]=lazy[k*2+1]^1; sum[k*2+1]=save[k*2+1]-sum[k*2+1];
        lazy[k]=0;
    }
    void build(int k,int l,int r)
    {
        lazy[k]=0;
        if(l==r) {sum[k]=len[l]; save[k]=sum[k]; return;}
        int mid=(l+r)/2;
        build(k*2,l,mid);build(k*2+1,mid+1,r);
        pushup(k);save[k]=sum[k];
    }
    void update(int k,int l,int r,int x,int y)
    {
        if(x>r||l>y) return;
        if(l>=x&&r<=y)
        {
            lazy[k]=lazy[k]^1;sum[k]=save[k]-sum[k];
            return;
        }
        pushdown(k);
        int mid=(l+r)/2;
        update(k*2,l,mid,x,y);update(k*2+1,mid+1,r,x,y);
        pushup(k);
    }
    int query(int k,int l,int r,int x,int y)
    {
        if(x>r||l>y) return 0;
        if(l>=x&&r<=y) return sum[k];
        pushdown(k);
        int mid=(l+r)/2;
        return query(k*2,l,mid,x,y)+query(k*2+1,mid+1,r,x,y);
    }
}seg;
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    v2.push_back(1);v2.push_back(m+1);
    v1.push_back(1);v1.push_back(n+1);
    for(int i=0;i<k;i++)
    {
        scanf("%d%d%d%d",&x1[i],&x2[i],&y1[i],&y2[i]);
        v1.push_back(x1[i]);v1.push_back(x2[i]+1);
        v2.push_back(y1[i]);v2.push_back(y2[i]+1);
    }
    sort(v1.begin(),v1.end());v1.erase(unique(v1.begin(),v1.end()),v1.end());
    sort(v2.begin(),v2.end());v2.erase(unique(v2.begin(),v2.end()),v2.end());
    for(int i=0;i<k;i++)
    {
        x1[i]=lower_bound(v1.begin(),v1.end(),x1[i])-v1.begin();
        x2[i]=lower_bound(v1.begin(),v1.end(),x2[i]+1)-v1.begin();
        y1[i]=lower_bound(v2.begin(),v2.end(),y1[i])-v2.begin()+1;
        y2[i]=lower_bound(v2.begin(),v2.end(),y2[i]+1)-v2.begin()+1;
        eve[x1[i]].push_back(P(y1[i],y2[i]-1));eve[x2[i]].push_back(P(y1[i],y2[i]-1));
    }
    int sz=(int)v2.size();
    for(int i=0;i<(int)sz-1;i++) len[i+1]=v2[i+1]-v2[i];
    seg.build(1,1,sz-1);
    ll ans=0;
    for(int i=0;i<(int)v1.size()-1;i++)
    {
        for(auto p:eve[i]) seg.update(1,1,sz-1,p.F,p.S);
        ans+=1LL*seg.query(1,1,sz-1,1,sz-1)*(v1[i+1]-v1[i]);
    }
    printf("%lld\n",ans);
    return 0;
}
