#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
int a[MAXN];
int cnt[MAXN],ans[MAXN];
int mini[MAXN],maxi[MAXN];
vector<int> pos[MAXN];
struct node
{
    int len,pre,suf,preans,sufans,ans;
    void merge(node &lhs,node &rhs)
    {
        if(lhs.len==-1) {*this=rhs; return;}
        else if(rhs.len==-1) {*this=lhs; return;}
        len=lhs.len+rhs.len;
        pre=lhs.pre; suf=rhs.suf;
        if(lhs.suf^rhs.pre)
        {
            ans=lhs.ans+rhs.ans-(lhs.sufans-1)/2-(rhs.preans-1)/2+(lhs.sufans+rhs.preans-1)/2;
            preans=(lhs.preans==lhs.len?lhs.preans+rhs.preans:lhs.preans);
            sufans=(rhs.sufans==rhs.len?rhs.sufans+lhs.sufans:rhs.sufans);
        }
        else
        {
            ans=lhs.ans+rhs.ans;
            preans=lhs.preans;
            sufans=rhs.sufans;
        }
    }
};
node nullnode;
struct segtree
{
    node res[4*MAXN];
    void pushup(int k)
    {
        res[k].merge(res[k*2],res[k*2+1]);
    }
    void build(int k,int l,int r)
    {
        if(l==r)
        {
            res[k].len=1;
            res[k].pre=res[k].suf=res[k].ans=0;
            res[k].preans=res[k].sufans=1;
            return;
        }
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
        pushup(k);
    }
    void update(int k,int l,int r,int p)
    {
        if(l==r)
        {
            res[k].pre=res[k].suf=1;
            return;
        }
        int mid=(l+r)/2;
        if(p<=mid) update(k*2,l,mid,p); else update(k*2+1,mid+1,r,p);
        pushup(k);
    }
    node query(int k,int l,int r,int x,int y)
    {
        if(l>y||x>r||x>y) return nullnode;
        if(l>=x&&r<=y) return res[k];
        int mid=(l+r)/2;
        node ret;
        node lhs=query(k*2,l,mid,x,y),rhs=query(k*2+1,mid+1,r,x,y);
        ret.merge(lhs,rhs);
        return ret;
    }
}seg;
int main()
{
    nullnode.len=-1;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        cnt[a[i]]++;
        pos[a[i]].push_back(i);
    }
    for(int i=1;i<=n;i++)
    {
        int x=a[i],y=(i==n?a[1]:a[i+1]);
        if(x>y) swap(x,y);
        if(x!=y)
        {
            ans[x+1]++; ans[y]--;
        }
    }
    for(int i=1;i<=m;i++) ans[i]+=ans[i-1];
    for(int i=1;i<=m;i++)
    {
        if(!cnt[i]) ans[i]=-1;
        else ans[i]=ans[i]+(n-cnt[i]);
    }
    seg.build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        if(!cnt[i]) continue;
        int sz=(int)pos[i].size();
        for(int j=1;j<sz;j++)
        {
            int len=pos[i][j]-pos[i][j-1]-1;
            if(len==0) continue;
            node ret=seg.query(1,1,n,pos[i][j-1]+1,pos[i][j]-1);
            ans[i]-=ret.ans;
        }
        int len=n-pos[i][sz-1]+(pos[i][0]-1);
        if(len!=0)
        {
            node ret1=seg.query(1,1,n,1,pos[i][0]-1),ret2=seg.query(1,1,n,pos[i][sz-1]+1,n);
            node ret;
            ret.merge(ret2,ret1);
            ans[i]-=ret.ans;
        }
        for(auto p:pos[i]) seg.update(1,1,n,p);
    }
    for(int i=1;i<=m;i++) printf("%d ",ans[i]);
    return 0;
}
