#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n;
int p[MAXN];
int sons[MAXN],len[MAXN];
vector<int> G[MAXN];
void dfs(int v,int d)
{
    if(sons[v]>=2) d=0;
    len[v]=d;
    for(auto to:G[v]) dfs(to,d+1);
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) p[i]=sons[i]=0,G[i].clear();
        for(int i=2;i<=n;i++)
        {
            scanf("%d",&p[i]);
            sons[p[i]]++;
            G[p[i]].push_back(i);
        }
        dfs(1,1);
        bool f=false;
        for(int i=1;i<=n;i++) if(!sons[i]&&(len[i]&1)) f=true;
        if(f) puts("Takeru"); else puts("Meiya");
    }
    return 0;
}
