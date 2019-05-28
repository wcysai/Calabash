#include<bits/stdc++.h>
#define MAXN 105
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,cnt=0;
vector<int> G[MAXN];
bool used[MAXN];
void die()
{
    puts("No");
    exit(0);
}
void dfs(int v)
{
    used[v]=true;
    cnt++;
    for(auto to:G[v]) 
    {
        if(!used[to]) dfs(to);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v); G[v].push_back(u);
    }
    int cnt1=0,cnt2=0,cnt3=0;
    for(int i=1;i<=n;i++)
    {
        if((int)G[i].size()==1) cnt1++;
        if((int)G[i].size()==3) cnt3++;
        if((int)G[i].size()==2) cnt2++;
    }
    if(n!=m) die();
    if(cnt1!=1||cnt3!=1) die();
    if(cnt1+cnt2+cnt3!=n) die();
    memset(used,false,sizeof(used));
    dfs(1);
    if(cnt!=n) die();
    puts("Yes");
    return 0;
}
