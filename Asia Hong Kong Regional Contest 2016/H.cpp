#include<bits/stdc++.h>
#define MAXN 14005
#define MAXM 30015
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
int tot,r[MAXN],p[MAXN],sz[MAXN],st[MAXN],val[MAXM];
vector<int> save[MAXN];
int ans[MAXM];
typedef bitset<14000> bs;
bs ret[MAXM];
vector<bs> sta;
void rollback()
{
    sta.pop_back();
}
struct segtree
{
    vector<int> res[4*MAXM];
    void add(int k,int l,int r,int x,int y,int sz)
    {
        //if(l==1&&r==m+10) printf("add %d %d %d\n",x,y,sz);
        if(l>y||x>r) return;
        if(l>=x&&r<=y)
        {
            res[k].push_back(sz);
            return;
        }
        int mid=(l+r)/2;
        add(k*2,l,mid,x,y,sz); add(k*2+1,mid+1,r,x,y,sz);
    }
    void solve(int k,int l,int r)
    {
        //printf("solve %d %d %d\n",k,l,r);
        if(l>tot) return;
        for(auto x:res[k]) 
        {
            bs tmp=sta.back(); 
            tmp|=(tmp<<x);
            sta.push_back(tmp);
        }
        if(l==r)
        {
            bs tmp=sta.back();
            int pos=tmp._Find_next((n-1)/2);
            ans[l]=n-pos;
            for(int i=0;i<(int)res[k].size();i++) rollback();
            return;
        }
        int mid=(l+r)/2;
        solve(k*2,l,mid); solve(k*2+1,mid+1,r);
        for(int i=0;i<(int)res[k].size();i++) rollback();
    }
} seg;
struct edge
{
    int u,v,cost;
};
bool cmp(edge x,edge y)
{
    return x.cost>y.cost;
}
void init(int n)
{
    for(int i=0;i<n;i++)
    {
        p[i]=i;
        r[i]=0;
        sz[i]=1;
        st[i]=1;
    }
}
int find(int x)
{
    while(p[x]!=x) x=p[x];
    return x;
}
bool unite(int x,int y)
{
    x=find(x); y=find(y);
    if(x==y) return false;
    if(r[x]<r[y]) 
    {
        p[x]=y;
        sz[y]+=sz[x];
        st[y]=tot;
    }
    else
    {
        p[y]=x;
        sz[x]+=sz[y];
        if(r[x]==r[y]) r[x]++;
        st[x]=tot;
    }
    return true;
}
bool same(int x,int y)
{
    return find(x)==find(y);
}
vector<edge> v;
bool vis[MAXM];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        v.push_back((edge){x,y,z});
    }
    sort(v.begin(),v.end(),cmp);
    init(n);
    for(int i=0;i<n;i++) save[1].push_back(i);
    int now=0;
    val[1]=v[0].cost;
    tot=2;
    while(now<(int)v.size())
    {
        int cur=now;
        while(cur<(int)v.size()&&v[cur].cost==v[now].cost)
        {
            if(same(v[cur].u,v[cur].v)) {cur++; continue;}
            else
            {
                int x=find(v[cur].u),y=find(v[cur].v);
                seg.add(1,1,m+10,st[x],tot-1,sz[x]);
                seg.add(1,1,m+10,st[y],tot-1,sz[y]);
                unite(x,y);
            }
        }
        now=cur;
        if(now<(int)v.size()) val[tot]=v[now].cost; else break;
        tot++;
    }
    memset(vis,false,sizeof(vis));
    for(int i=0;i<n;i++)
    {
        int x=find(i);
        if(!vis[x])
        {
            seg.add(1,1,m+10,st[x],tot-1,sz[x]);
            vis[x]=true;
        }
    }
    bs tmp; tmp.reset(); tmp.set(0);
    sta.push_back(tmp);
    seg.solve(1,1,m+10);
    double fans=INF;
    for(int i=1;i<tot;i++) 
    {
        if(ans[i]==0) continue;
        //printf("%d %d %d\n",i,val[i],ans[i]);
        fans=min(fans,(double)val[i]/ans[i]);
    }
    printf("%.10f\n",fans);
    return 0;
}
