#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,x,y;
char str[2];
vector<P> edges[4*MAXN];
int p[MAXN],rk[MAXN],sz[MAXN];
int ans[MAXN];
int num;
struct update
{
    int x,y;
    bool addrk;
};
update st[MAXN];
int t;
void init(int n)
{
    for(int i=1;i<=n;i++)
    {
        p[i]=i;
        rk[i]=0;
    }
}
int find(int x)
{
   while(p[x]!=x) x=p[x];
   return x;
}
bool unite(int x,int y)
{
    x=find(x);
    y=find(y);
    if(x==y) return false;
    if(rk[x]<rk[y])
    {
        p[x]=y;
        st[t++]=(update){x,y,false};
    }
    else
    {
        p[y]=x;
        st[t++]=(update){y,x,rk[x]==rk[y]};
        if(rk[x]==rk[y]) rk[x]++;
    }
    return true;
}
void undo()
{
    assert(t);
    int x=st[t-1].x,y=st[t-1].y;
    //printf("undo %d %d %d\n",x,y,st[t-1].addrk);
    p[x]=x;p[y]=y;
    if(st[t-1].addrk) rk[y]--;
    t--;
}
bool same(int x,int y)
{
    return find(x)==find(y);
}
void add_edge(int k,int l,int r,int x,int y,int u,int v)
{
    if(x>r||l>y) return;
    if(l>=x&&r<=y)
    {
        edges[k].push_back(P(u,v));
        return;
    }
    int mid=(l+r)/2;
    add_edge(k*2,l,mid,x,y,u,v);add_edge(k*2+1,mid+1,r,x,y,u,v);
}
void solve(int k,int l,int r)
{
    if(l>r) return;
    int cnt=0;
    for(auto e:edges[k]) if(unite(e.F,e.S)) cnt++;
    if(l==r)
    {
        ans[l]=(find(1)==find(n)?1:0);
        for(int i=0;i<cnt;i++) undo();
        return;
    }
    int mid=(l+r)/2;
    solve(k*2,l,mid);solve(k*2+1,mid+1,r);
    //printf("cnt %d %d %d\n",l,r,cnt);
    for(int i=0;i<cnt;i++) undo();
}
int u[MAXN],v[MAXN],l[MAXN],r[MAXN];
vector<int> dis;
int main()
{
    scanf("%d%d",&n,&m);init(n);
    for(int i=0;i<m;i++)
    {
        scanf("%d%d%d%d",&u[i],&v[i],&l[i],&r[i]);
        r[i]++;
        dis.push_back(l[i]); dis.push_back(r[i]);
    }
    sort(dis.begin(),dis.end());
    dis.erase(unique(dis.begin(),dis.end()),dis.end());
    int sz=(int)dis.size();
    for(int i=0;i<m;i++)
    {
        l[i]=lower_bound(dis.begin(),dis.end(),l[i])-dis.begin()+1;
        r[i]=lower_bound(dis.begin(),dis.end(),r[i])-dis.begin()+1;
        add_edge(1,1,sz,l[i],r[i]-1,u[i],v[i]);
    }
    solve(1,1,sz);
    int ret=0;
    for(int i=1;i<=sz;i++)
        if(ans[i])
        {
            assert(i!=sz);
            ret+=dis[i]-dis[i-1];
        }
    printf("%d\n",ret);
    return 0;
}
