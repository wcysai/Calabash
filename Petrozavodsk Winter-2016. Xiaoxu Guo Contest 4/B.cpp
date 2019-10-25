#include<bits/stdc++.h>
#define MAXN 2005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef bitset<2000> bs;
int n;
bs G[MAXN];
string str;
int d[MAXN];
bs vis;
bs to;
void bfs(int u)
{
    vis.reset();
    queue<int> que;
    que.push(u); d[u]=0;
    vis.set(u);
    while(que.size())
    {
        int v=que.front(); que.pop();
        int cur=d[v];
        to=G[v]&(~vis);
        for(int i=to._Find_first();i<n;i=to._Find_next(i))
        {
            d[i]=cur+1;
            que.push(i);
            vis.set(i);
        }
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        cin>>str;
        G[i].reset();
        for(int j=0;j<n;j++) if(str[j]=='1') G[i].set(j);
    }
    ll ans=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++) d[j]=n;
        bfs(i);
        for(int j=0;j<n;j++) ans+=1LL*d[j]*d[j];
    }
    printf("%lld\n",ans);
    return 0;
}
