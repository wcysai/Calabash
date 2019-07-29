#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 500005
#define MAXM 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,t;
ll X,Y,Z;
ll p[MAXN];
struct edge
{
    int u,v,c;
}st[MAXN];
map<int,int> mp[MAXN];
vector<P> res[2];
int find(int a,int b)
{
    if(mp[a].find(b)!=mp[a].end()) return mp[a][b];
    if((1LL*min(a,b)*X+1LL*max(a,b)*Y)%Z<p[a]+p[b]) return 0;
    return 1;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        mp[a][b]=mp[b][a]=c;
    }
    scanf("%lld%lld%lld",&X,&Y,&Z);
    for(int i=1;i<=n;i++) scanf("%lld",&p[i]);
    int v=1;
    st[t++]={n,1,find(n,1)};
    for(int i=2;i<=n-1;i++)
    {
        int c=find(v,i);
        while(t>0&&c!=st[t-1].c)
        {
            res[c].push_back(P(v,i));
            res[1-c].push_back(P(st[t-1].u,v));
            v=st[t-1].u;
            c=find(v,i);
            t--;
        }
        st[t++]={v,i,c};
        v=i;
    }
    int col=st[t-1].c;
    for(int i=0;i<t;i++) printf("%d %d\n",st[i].u,st[i].v);
    for(auto p:res[col]) printf("%d %d\n",p.F,p.S);
    return 0;
}

