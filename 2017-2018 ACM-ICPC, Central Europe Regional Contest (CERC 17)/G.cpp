//
// Created by calabash_boy on 18-5-22.
//

#include<bits/stdc++.h>
#define MAXN 300005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<double,int> P;
int n,m;
vector<int> G[MAXN];
double sum[MAXN],ans[MAXN];
int cnt[MAXN],deg[MAXN];
bool used[MAXN];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v);G[v].push_back(u);
        deg[u]++;deg[v]++;
    }
    memset(sum,0,sizeof(sum));
    fill(ans,ans+n+1,INF);
    set<P> s;
    ans[n]=0;
    for(int i=1;i<=n;i++)
        s.insert(P(ans[i],i));
    memset(used,false,sizeof(used));
    memset(cnt,0,sizeof(cnt));
    for(int i=1;i<=n;i++)
    {
        auto it=s.begin();
        P p=*it;
        if(p.S==1)
        {
            printf("%.10f\n",p.F);
            return 0;
        }
        //printf("%.10f %d\n",p.F,p.S);
        int v=p.S;
        used[v]=true;
        s.erase(s.begin());
        //printf("%.10f %d\n",p.F,p.S);
        for(int j=0;j<G[v].size();j++)
        {
            int to=G[v][j];
            if(used[to]) continue;
            cnt[to]++;
            sum[to]+=ans[v];
            s.erase(P(ans[to],to));
            ans[to]=(sum[to]+deg[to])/cnt[to];
            s.insert(P(ans[to],to));
        }
    }
    return 0;
}
