#include<bits/stdc++.h>
#define MAXN 10005
#define MAXM 51
#define MAXK 51
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
ll t,now;
P st[MAXN];
void add(ll u,ll v)
{
    P p=P(u,v);
    while(t>1&&(st[t-1].F-st[t-2].F)*(p.S-st[t-1].S)>=(st[t-1].F-p.F)*(st[t-2].S-st[t-1].S)) t--;
    st[t++]=p;
}
ll query(ll x)
{
    ll l=-1,r=t-1;
    while(r-l>1)
    {
        ll mid=(l+r)/2;
        if(st[mid].F*x+st[mid].S<=st[mid+1].F*x+st[mid+1].S) l=mid;
        else r=mid;
    }
    return st[r].F*x+st[r].S;
}
int T;
int a[MAXN];
int s[MAXN];
int N,M,K;
ll dp[MAXK][MAXN];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&N,&K,&M);
        for(int i=1;i<=N;i++) scanf("%d",&a[i]);
        for(int i=1;i<=N;i++) s[i]=s[i-1]+a[i];
        ll ans=0;
        int sum=0;
        for(int i=1;i<=N;i++)
        {
            sum-=a[i];
            ans+=sum;
        }
        vector<int> v; v.clear();
        for(int i=1;i<=N;i++) v.push_back((N-i+1)*a[i]);
        sort(v.begin(),v.end(),greater<int>());
        for(int i=0;i<M;i++) ans+=v[i];
        for(int i=0;i<=N;i++) dp[0][i]=0;
        for(int i=1;i<=K+1;i++)
        {
            t=0;
            for(int j=1;j<=N;j++)
            {
                add(s[j-1],dp[i-1][j-1]-1LL*N*s[j-1]);
                dp[i][j]=query(j)+1LL*N*s[j]-1LL*j*s[j];
            }
        }
        ans+=dp[K+1][N];
        printf("%lld\n",ans);
    }
    return 0;
}
