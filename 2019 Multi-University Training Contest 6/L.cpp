#include<bits/stdc++.h>
#define MAXN 400005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,h[MAXN];
bool valid[MAXN];
priority_queue<P> pq;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&h[i]);
        for(int i=1;i<=2*n+1;i++) valid[i]=false;
        for(int i=1;i<=n;i++) valid[i]=true;
        for(int i=1;i<=n;i++) if(!valid[2*i]&&!valid[2*i+1]) pq.push(P(h[i],i));
        ll ans1=0,ans2=0;
        int turn=0;
        while(pq.size())
        {
            P p=pq.top(); pq.pop();
            if(turn&1) ans2+=p.F; else ans1+=p.F;
            turn^=1;
            valid[p.S]=false;
            if(valid[p.S/2]&&!valid[p.S]&&!valid[p.S^1]) pq.push(P(h[p.S/2],p.S/2));
        }
        printf("%lld %lld\n",ans1,ans2);
    }
    return 0;
}
