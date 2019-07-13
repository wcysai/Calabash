#include<bits/stdc++.h>
#define MAXN 105
#define MAXM 65
#define INF 1000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,sz;
ll p;
ll dp[MAXM][MAXN][2][2];
vector<int> v;
void add(ll &a,ll b) {a+=b; if(a>INF) a=INF;}
ll solve(int cur,int cnt,int last,int less)
{
    if(cnt<0) return 0;
    if(cur==sz) return (cnt==0);
    if(dp[cur][cnt][last][less]!=-1) return dp[cur][cnt][last][less];
    ll &res=dp[cur][cnt][last][less];
    res=0;
    int limit=less?1:v[cur];
    for(int i=0;i<=limit;i++) add(res,solve(cur+1,cnt-(i!=last),i,less||(i<limit)));
    return res;
}
bool check(ll x)
{
    ll tmp=x;
    v.clear();
    while(x)
    {
        v.push_back(x&1);
        x>>=1;
    }
    reverse(v.begin(),v.end());
    memset(dp,-1,sizeof(dp));
    sz=(int)v.size();
    return solve(0,n,0,0)>=p;
}
int main()
{
    scanf("%d%lld",&n,&p);
    ll l=0,r=(1LL<<62)+1;
    while(r-l>1)
    {
        ll mid=(l+r)/2;
        if(check(mid)) r=mid; else l=mid;
    }
    printf("%lld\n",r);
    return 0;
}
