#include<bits/stdc++.h>
#define MAXN 500005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,c,r;
int s[MAXN],need[MAXN];
vector<int> dis;
ll ans;
struct mat
{
    ll a[2][2];
};
int type[MAXN];
mat id;
mat f,g,fg,mustdel;
mat mul(mat x,mat y)
{
    mat z;
    z.a[0][0]=min(x.a[0][0]+y.a[0][0],x.a[0][1]+y.a[1][0]);
    z.a[0][1]=min(x.a[0][0]+y.a[0][1],x.a[0][1]+y.a[1][1]);
    z.a[1][0]=min(x.a[1][0]+y.a[0][0],x.a[1][1]+y.a[1][0]);
    z.a[1][1]=min(x.a[1][1]+y.a[1][1],x.a[1][0]+y.a[0][1]);
    return z;
}
struct segtree
{
    mat res[4*MAXN];
    void pushup(int k)
    {
        res[k]=mul(res[k*2+1],res[k*2]);
    }
    void build(int k,int l,int r)
    {
        if(l==r)
        {
            res[k]=(type[l]==0?f:(type[l]==1?g:(type[l]==2?fg:mustdel)));
            return;
        }
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
        pushup(k);
    }
    void update(int k,int l,int r,int pos)
    {
        if(l==r)
        {
            res[k]=fg;
            return;
        }
        int mid=(l+r)/2;
        if(pos<=mid) update(k*2,l,mid,pos); else update(k*2+1,mid+1,r,pos);
        pushup(k);
    }
    ll query()
    {
        mat m=res[1];
        return min(min(m.a[0][0],m.a[0][1]),min(m.a[1][0],m.a[1][1]));
    }
}seg;
vector<int> pos[MAXN];
int main()
{
    id.a[0][0]=id.a[1][1]=0;
    id.a[0][1]=id.a[1][0]=INF;
    f.a[0][0]=1; f.a[0][1]=INF;
    f.a[1][0]=0; f.a[1][1]=1;
    g.a[0][0]=1; g.a[0][1]=0;
    g.a[1][0]=INF; g.a[1][1]=1;
    fg.a[0][0]=fg.a[1][1]=1;
    fg.a[0][1]=fg.a[1][0]=0;
    mustdel.a[0][0]=1; mustdel.a[0][1]=INF;
    mustdel.a[1][0]=INF; mustdel.a[1][1]=1;
    scanf("%d%d%d",&n,&c,&r);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&s[i]);
        if(s[i]>0)
        {
            type[i]=0; need[i]=s[i]+1;
        }
        else if(s[i]<0)
        {
            type[i]=1; need[i]=-s[i]+1;
        }
        else
        {
            type[i]=3; need[i]=1;
        }
        dis.push_back(need[i]);
    }
    sort(dis.begin(),dis.end());
    dis.erase(unique(dis.begin(),dis.end()),dis.end());
    seg.build(1,1,n);
    for(int i=1;i<=n;i++)
    {
        int id=lower_bound(dis.begin(),dis.end(),need[i])-dis.begin();
        pos[id].push_back(i);
    }
    ans=INF;
    ll cur=0;
    int changed=0;
    ans=min(ans,1LL*r*seg.query());
    for(int i=0;i<(int)dis.size();i++)
    {
        cur+=1LL*c*(dis[i]-changed);
        for(auto x:pos[i]) seg.update(1,1,n,x);
        changed=dis[i];
        ans=min(ans,cur+1LL*r*seg.query());
    }
    printf("%lld\n",ans);
    return 0;
}
