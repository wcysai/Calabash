#include<bits/stdc++.h>
#define MAXN 200005
#define MAXM 800005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int N,Q,V;
int p[MAXN],r[MAXN],c[MAXN];
vector<P> v;
vector<int> G[MAXM];
int pos[MAXN],pp[MAXN];
int id[MAXN];
vector<int> rG[MAXM];
vector<int> GG[MAXM];
vector<int> vs;
multiset<int> ans[MAXM];
bool used[MAXM];
int cnt[MAXM];
int cmp[MAXM],in[MAXM];
void add_edge(int from,int to)
{
    //printf("added %d %d\n",from,to);
    G[from].push_back(to);
    rG[to].push_back(from);
}
void dfs(int v)
{
    used[v]=true;
    for(int i=0;i<(int)G[v].size();i++)
        if(!used[G[v][i]]) dfs(G[v][i]);
    vs.push_back(v);
}
void rdfs(int v,int k)
{
    used[v]=true;
    cmp[v]=k;
    for(int i=0;i<(int)rG[v].size();i++)
        if(!used[rG[v][i]]) rdfs(rG[v][i],k);
}
int scc()
{
    memset(used,0,sizeof(used));
    vs.clear();
    for(int v=1;v<=V;v++) if(!used[v]) dfs(v);
    int k=0;
    memset(used,0,sizeof(used));
    for(int i=vs.size()-1;i>=0;i--) if(!used[vs[i]]) rdfs(vs[i],k++);
    return k;
}
void build(int k,int l,int r)
{
    if(l==r) {id[l]=k; V=max(V,k); return;}
    int mid=(l+r)/2;
    build(k*2,l,mid);build(k*2+1,mid+1,r);
    add_edge(k,k*2);add_edge(k,k*2+1);
}
void add(int k,int l,int r,int x,int y,int d)
{
    if(x>r||l>y) return;
    if(l>=x&&r<=y) {add_edge(d,k); return;}
    int mid=(l+r)/2;
    add(k*2,l,mid,x,y,d);add(k*2+1,mid+1,r,x,y,d);
}
int main()
{
    scanf("%d%d",&N,&Q);
    for(int i=1;i<=N;i++) scanf("%d%d%d",&p[i],&r[i],&c[i]);
    for(int i=1;i<=N;i++) v.push_back(P(p[i],i));
    sort(v.begin(),v.end());
    for(int i=0;i<N;i++) pp[v[i].S]=i+1;
    build(1,1,N);
    for(int i=1;i<=N;i++)
    {
        int l=lower_bound(v.begin(),v.end(),P(p[i]-r[i],0))-v.begin()+1;
        int R=upper_bound(v.begin(),v.end(),P(p[i]+r[i]+1,0))-v.begin();
        //printf("%d %d\n",l,R);
        add(1,1,N,l,R,id[pp[i]]);
    }
    //printf("V=%d\n",V);
    int p=scc();
    //printf("p=%d\n",p);
    //for(int i=1;i<=V;i++) printf("%d\n",cmp[i]);
    for(int i=1;i<=V;i++)
    {
        for(auto it:G[i])
        {
            if(cmp[i]==cmp[it]) continue;
            in[cmp[it]]++;
            GG[cmp[i]].push_back(cmp[it]);
        }
    }
    for(int i=1;i<=N;i++) cnt[cmp[id[pp[i]]]]++;
    queue<int> que;
    for(int i=0;i<p;i++) if(in[i]==0) que.push(i);
    while(que.size())
    {
        int now=que.front();que.pop();
        if(cnt[now]) continue;
        for(auto it:GG[now]) {in[it]--; if(in[it]==0) que.push(it);}
    }
    //for(int i=1;i<=N;i++) printf("%d %d %d %d\n",i,pp[i],id[pp[i]],cmp[id[pp[i]]]);
    for(int i=1;i<=N;i++) ans[cmp[id[pp[i]]]].insert(c[i]);
    ll cur=0;
    for(int i=0;i<p;i++) if(in[i]==0&&cnt[i])  cur+=*ans[i].begin();
    for(int i=0;i<Q;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(in[cmp[id[pp[x]]]]==0)
        {
            cur -= *ans[cmp[id[pp[x]]]].begin();
            ans[cmp[id[pp[x]]]].erase(ans[cmp[id[pp[x]]]].find(c[x]));
            c[x] = y;
            ans[cmp[id[pp[x]]]].insert(c[x]);
            cur += *ans[cmp[id[pp[x]]]].begin();
        }
        printf("%lld\n",cur);
    }
    return 0;
}
