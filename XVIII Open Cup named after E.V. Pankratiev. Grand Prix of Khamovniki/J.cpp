#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 100000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef long double db;
const int blocks=300;
vector<int> f;
int maxi[MAXN];
vector<int> convex_hull[MAXN];
int n,sz,a[MAXN];
ll dp[MAXN],add1[MAXN],add2[MAXN];
bool need[MAXN];
bool check(int x,int y,int z)
{
    return (db)1.0*(dp[z]-dp[y])/(f[z]-f[y])<=(db)1.0*(dp[y]-dp[x])/(f[y]-f[x]);
}
void build(int id)
{
    convex_hull[id].clear();
    int st=id*blocks,ed=min(sz,(id+1)*blocks);
    if(add1[id])
    {
        for(int i=st;i<ed;i++) dp[i]+=add1[id];
        add1[id]=0;
    }
    if(add2[id])
    {
        for(int i=st;i<ed;i++) dp[i]+=1LL*add2[id]*f[i];
        add2[id]=0;
    }
    for(int i=id*blocks;i<min(sz,(id+1)*blocks);i++)
    {
        int t=(int)convex_hull[id].size();
        while(t>=2&&check(convex_hull[id][t-2],convex_hull[id][t-1],i))
        {
            convex_hull[id].pop_back();
            t--;
        }
        convex_hull[id].push_back(i); t++;
        while(t>=2&&dp[convex_hull[id][t-2]]<=dp[convex_hull[id][t-1]])
        {
            convex_hull[id].pop_back();
            t--;
        }
    }
    need[id]=false;
}
void update(int x,ll v)
{
    int block_id=x/blocks;
    dp[x]=v-add1[block_id]-1LL*add2[block_id]*f[x];
    need[block_id]=true;
}
ll get_val(int x)
{
    int block_id=x/blocks;
    return dp[x]+add1[block_id]+1LL*add2[block_id]*f[x];
}
ll query_block(int block_id)
{
    if(need[block_id]) build(block_id);
    assert(convex_hull[block_id].size());
    int x=convex_hull[block_id].back();
    return get_val(x);
}
ll query(int l,int r)
{
    ll ret=INF;
    while(l<=r&&l%blocks!=0) {ret=min(ret,get_val(l)); l++;}
    //printf("ret=%lld\n",ret);
    while(l<=r&&r%blocks!=blocks-1) {ret=min(ret,get_val(r));  r--;}
    while(l<r) {ret=min(ret,query_block(l/blocks)); l+=blocks;}
    return ret;
}
void add(int l,int r,int v)
{
    while(l<=r&&l%blocks!=0) {dp[l]+=v; need[l/blocks]=true; l++;}
    while(l<=r&&r%blocks!=blocks-1) {dp[r]+=v; need[r/blocks]=true; r--;}
    while(l<r) {add1[l/blocks]+=v; l+=blocks;}
}
void addf(int l,int r)
{
    while(l<=r&&l%blocks!=0) {dp[l]+=f[l]; need[l/blocks]=true; l++; }
    while(l<=r&&r%blocks!=blocks-1) {dp[r]+=f[r]; need[r/blocks]=true; r--;}
    while(l<r)
    {
        int block_id=l/blocks;
        if(need[block_id]) build(block_id);
        add2[l/blocks]++;
        int t=(int)convex_hull[block_id].size();
        while(t>=2&&get_val(convex_hull[block_id][t-2])<=get_val(convex_hull[block_id][t-1]))
        {
            convex_hull[block_id].pop_back();
            t--;
        }
        l+=blocks;
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        f.push_back(a[i]);
    }
    f.push_back(0);
    sort(f.begin(),f.end()); f.erase(unique(f.begin(),f.end()),f.end());
    for(int i=1;i<=n;i++) a[i]=lower_bound(f.begin(),f.end(),a[i])-f.begin();
    for(int i=1;i<=n;i++) maxi[i]=max(maxi[i-1],a[i]);
    sz=(int)f.size();
    for(int i=0;i<sz;i++) dp[i]=INF;
    dp[0]=0;
    for(int i=0;i<(sz-1)/blocks;i++) build(i);
    memset(need,false,sizeof(need));
    for(int i=1;i<=n;i++)
    {
        if(a[i]==maxi[i]) continue;
        ll val=query(0,a[i]);
        update(a[i],val);
        ll tmp=f[maxi[i]]-f[a[i]];
        add(0,a[i]-1,tmp);
        add(a[i]+1,sz-1,-f[a[i]]);
        addf(a[i]+1,sz-1);
    }
    ll ans=INF;
    for(int i=0;i<sz;i++) ans=min(ans,get_val(i));
    printf("%lld\n",ans);
    return 0;
}
