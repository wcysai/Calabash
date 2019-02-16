#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,p[MAXN],a[MAXN],dep[MAXN],deg[MAXN];
vector<int> G[MAXN];
void add_edge(int u,int v)
{
    G[u].push_back(v);
    G[v].push_back(u);
}
int main()
{
    scanf("%d",&n);
    for(int i=2;i<=n;i++)
    {
        scanf("%d",&p[i]);
        p[i]++;add_edge(i,p[i]);
        deg[i]++;deg[p[i]]++;
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        a[i]++;
    }
    return 0;
}

