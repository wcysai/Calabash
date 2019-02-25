#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef pair<int,int> P;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
typedef __gnu_pbds::priority_queue<int,greater<int>,pairing_heap_tag> pq;
int n;
string str[MAXN];
namespace ZL
{
	const int N=505,M=100010,inf=1e9; 
	struct edge
    {
	    int u,v,w,use,id;
	}b[M],a[20001000];
	int n,m,ans,pre[N],id[N],vis[N],root,In[N],h[N],len,way[M];
	void init(int _n,int _root)
    {
		n=_n; m=0; b[0].w=inf; root=_root; ans=0;
	}
	void add(int u,int v,int w)
    {
		b[++m]=(edge){u,v,w,0,m};
		a[m]=b[m];
	}
	int work()
    {
		len=m;
	    for (;;)
        {
	        for (int i=1;i<=n;i++){pre[i]=0; In[i]=inf; id[i]=0; vis[i]=0; h[i]=0;}
	        for (int i=1;i<=m;i++)
	            if (b[i].u!=b[i].v&&b[i].w<In[b[i].v])
                {
	                pre[b[i].v]=b[i].u; In[b[i].v]=b[i].w; h[b[i].v]=b[i].id;
	            }
	        for (int i=1;i<=n;i++) if (pre[i]==0&&i!=root) return 0;
	        int cnt=0; In[root]=0;
	        for (int i=1;i<=n;i++)
            {
	            if (i!=root) a[h[i]].use++; 
	            int now=i; ans+=In[i];
	            while (vis[now]==0&&now!=root)
                {
	                vis[now]=i; now=pre[now];
	            }
	            if (now!=root&&vis[now]==i)
                {
	                cnt++; int kk=now;
	                while (1)
                    {
	                    id[now]=cnt; now=pre[now];
	                    if (now==kk) break;
	                }
	            }
	        }
	        if (cnt==0) return 1;
	        for (int i=1;i<=n;i++) if (id[i]==0) id[i]=++cnt;
	        for (int i=1;i<=m;i++)
            {
	            int k1=In[b[i].v]; int k2=b[i].v;
	            b[i].u=id[b[i].u]; b[i].v=id[b[i].v];       
	            if (b[i].u!=b[i].v)
                {
	                b[i].w-=k1; a[++len].u=b[i].id; a[len].v=h[k2];
	                b[i].id=len;
	            }
	        }
	        n=cnt;
	        root=id[root];
	    }
	    return 1;
	}
	void getway()
    {
		for (int i=1;i<=m;i++) way[i]=0;
		for (int i=len;i>m;i--)
        {
			a[a[i].u].use+=a[i].use; a[a[i].v].use-=a[i].use;
		}
		for (int i=1;i<=m;i++) way[i]=a[i].use;
	}
}
struct edge
{
    int to,cost;
};
vector<edge> G[MAXN];
int tot=0;
int id[MAXN];
void dfs(int v,int p,int w)
{
    if(w) id[v]=++tot; else id[v]=id[p];
    if(v==1) puts("0");
    else if(w) printf("%d %c\n",id[p],str[v-1].back());
    for(auto e:G[v])
    {
        if(e.to==p) continue;
        dfs(e.to,v,e.cost);
    }
}
int main()
{
    scanf("%d",&n);
    vector<string> vv;
    for(int i=1;i<=n;i++) 
    {
        string ss;
        cin>>ss;
        for(int j=1;j<=(int)ss.size();j++) vv.push_back(ss.substr(0,j));
    }
    n=(int)vv.size();
    for(int i=1;i<=n;i++) str[i]=vv[i-1];
    ZL::init(n+1,1);
    for(int i=1;i<=n;i++) 
    {
        if(str[i].size()==1) ZL::add(1,i+1,1);
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            if(i==j) continue;
            int sz1=(int)str[i].size(),sz2=(int)str[j].size();
            if(sz2==sz1+1&&str[j].substr(0,sz1)==str[i].substr(0,sz1)) ZL::add(i+1,j+1,1);
            if(sz1>=sz2&&str[i].substr(sz1-sz2,sz2)==str[j]) ZL::add(i+1,j+1,0);
        }
    assert(ZL::work());ZL::getway();
    printf("%d\n",ZL::ans+1);
    for(int i=1;i<=ZL::m;i++) 
    {
        if(ZL::way[i]) 
        {
            int u=ZL::a[i].u,v=ZL::a[i].v,w=ZL::a[i].w;
            G[u].push_back((edge){v,w});
            G[v].push_back((edge){u,w});
        }
    }
    dfs(1,0,1);
    return 0;
}

