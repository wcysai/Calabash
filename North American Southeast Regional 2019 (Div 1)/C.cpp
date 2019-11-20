#include<bits/stdc++.h>
#define MAXN 100005
#define MAXM 300010
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
int cnt[MAXM],k;
ll ans;
vector<int> pos[MAXM];
vector<int> divisors[MAXM];
void add(int p)
{
    for(auto d:divisors[p]) pos[d].push_back(p);
}
void update(int p)
{
    if(!cnt[p]) return;
    ans+=cnt[p];
    if(p+1<=300006&&!cnt[p+1]) add(p+1);
    cnt[p+1]+=cnt[p];
    cnt[p]=0;
}
void update_all(int k)
{
    for(auto p:pos[k]) update(p);
    pos[k].clear();
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=2;i<=300006;i++)
        for(int j=i;j<=300006;j+=i)
            divisors[j].push_back(i);
    for(int i=1;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        cnt[x]++;
    }
    for(int i=2;i<=300000;i++) if(cnt[i]) add(i);
    ans=0;
    for(int i=0;i<m;i++)
    {
        int k;
        scanf("%d",&k);
        update_all(k);
    }
    printf("%lld\n",ans);
    return 0;
}
