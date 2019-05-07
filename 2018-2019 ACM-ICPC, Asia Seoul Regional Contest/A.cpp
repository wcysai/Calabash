#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
struct segtree
{
    int ans[4*MAXN],lazy[4*MAXN];
    void pushup(int k)
    {
        ans[k]=max(ans[k*2],ans[k*2+1]);
    }
    void add(int k,int v)
    {
        ans[k]+=v;
        lazy[k]+=v;
    }
    void pushdown(int k)
    {
        for(int i=k*2;i<=k*2+1;i++) add(i,lazy[k]);
        lazy[k]=0;
    }
    void update(int k,int l,int r,int x,int y,int v)
    {
        if(x>r||l>y) return;
        if(l>=x&&r<=y)
        {
            add(k,v);
            return;
        }
        pushdown(k);
        int mid=(l+r)/2;
        update(k*2,l,mid,x,y,v); update(k*2+1,mid+1,r,x,y,v);
        pushup(k);
    }
    int query(int k,int l,int r,int x,int y)
    {
        if(x>r||l>r) return 0;
        if(l>=x&&r<=y) return ans[k];
        pushdown(k);
        int mid=(l+r)/2;
        return max(query(k*2,l,mid,x,y),query(k*2+1,mid+1,r,x,y));
    }
}seg;
int n;
int a[MAXN],b[MAXN],c[MAXN],d[MAXN];
vector<int> v;
vector<int> line[MAXN];
int leave[MAXN];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d%d%d",&a[i],&b[i],&c[i],&d[i]);
        v.push_back(b[i]); v.push_back(d[i]);
    }
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    for(int i=1;i<=n;i++) 
    {
        b[i]=lower_bound(v.begin(),v.end(),b[i])-v.begin()+1;
        d[i]=lower_bound(v.begin(),v.end(),d[i])-v.begin()+1;
    }
    int sz=(int)v.size();
    for(int i=1;i<=n;i++)
    {
        line[d[i]].push_back(b[i]);
        leave[b[i]+1]++;
        seg.update(1,1,sz,d[i],b[i],1);
    }
    int ans=seg.query(1,1,sz,1,sz),cnt=0;
    for(int i=1;i<=sz;i++)
    {
        for(auto x:line[i])
        {
            cnt++;
            seg.update(1,1,sz,i,x,-1);
        }
        cnt-=leave[i];
        ans=max(ans,cnt+seg.query(1,1,sz,1,sz));
    }
    printf("%d\n",ans);
    return 0;
}
