#include<bits/stdc++.h>
#define MAXN 60005
#define INF 2000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll K;
int d1,d2,d3,d4;
ll d[MAXN];
ll solve(vector<int> weights,ll target)
{
    if(target<0) return 0;
    sort(weights.begin(),weights.end());
    fill(d,d+60001,INF);
    d[0]=0;
    queue<P> que; que.push(P(0,0));
    while(que.size())
    {
        P p=que.front(); que.pop();
        int v=p.F,dis=p.S;
        if(d[v]<dis) continue;
        for(int i=1;i<(int)weights.size();i++)
        {
            int to=(v+weights[i])%weights[0];
            if(d[to]>d[v]+weights[i])
            {
                d[to]=d[v]+weights[i];
                que.push(P(to,d[to]));
            }
        }
    }
    ll ans=INF;
    for(int i=0;i<weights[0];i++)
    {
        if(d[i]!=INF) 
        {
            if(d[i]>=target) ans=min(ans,d[i]);
            else ans=min(ans,1LL*((target-i+weights[0]-1)/weights[0])*weights[0]+i);
        }
    }
    return ans;
}
int main()
{
    scanf("%lld%d%d%d%d",&K,&d1,&d2,&d3,&d4);
    int sum=d1+d2+d3+d4;
    ll ans=INF;
    ans=min(ans,solve(vector<int>{2*d1,2*d2,2*d3,2*d4},K-d1-d2-d3-d4)+d1+d2+d3+d4);
    ans=min(ans,solve(vector<int>{2*d1,2*d2,2*d3,2*d4},K-2*d1-2*d2-2*d3-2*d4)+2*d1+2*d2+2*d3+2*d4);
    ans=min(ans,solve(vector<int>{2*d1,2*d2,2*d3},K-2*d1-2*d2-2*d3)+2*d1+2*d2+2*d3);
    ans=min(ans,solve(vector<int>{2*d1,2*d3,2*d4},K-2*d1-2*d3-2*d4)+2*d1+2*d3+2*d4);
    ans=min(ans,solve(vector<int>{2*d2,2*d3},K-2*d2-2*d3)+2*d2+2*d3);
    ans=min(ans,solve(vector<int>{2*d1,2*d4},K-2*d1-2*d4)+2*d1+2*d4);
    ans=min(ans,solve(vector<int>{2*d1,2*d2},K-2*d1-2*d2)+2*d1+2*d2);
    ans=min(ans,solve(vector<int>{2*d1},K-2*d1)+2*d1);
    ans=min(ans,solve(vector<int>{2*d2},K-2*d2)+2*d2);
    printf("%lld\n",ans);
    return 0;
}
