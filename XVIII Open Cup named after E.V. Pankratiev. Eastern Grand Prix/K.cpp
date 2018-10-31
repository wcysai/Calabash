#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 50005
#define MAXM 300005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
void mx(ll &a,ll b) {a=max(a,b);}
int n,m,D;
vector<int> rating[MAXN];
ll ans[MAXM];
ll dp[MAXN][50];
struct query{ int l,r,id;};
void solve(int l,int r,vector<query> &v)
{
    if(!v.size()) return;
    if(l==r)
    {
        ll cur=-1;
        for(int i=0;i<3;i++) if(rating[l][i]%D==0) cur=max(cur,(ll)rating[l][i]);
        for(int i=0;i<(int)v.size();i++) ans[v[i].id]=cur;
        return;
    }
    vector<query> lq,rq,now;lq.clear();rq.clear();now.clear();
    int mid=(l+r)/2;
    for(int i=0;i<(int)v.size();i++)
    {
        if(v[i].r<mid) lq.push_back(v[i]);
        else if(v[i].l>mid) rq.push_back(v[i]);
        else now.push_back(v[i]);
    }
    solve(l,mid,lq);solve(mid+1,r,rq);
    if(!now.size()) return;
    for(int i=0;i<=D-1;i++) dp[mid][i]=-1;
    for(int i=0;i<3;i++) mx(dp[mid][rating[mid][i]%D],rating[mid][i]/D);
    for(int i=mid-1;i>=l;i--)
    {
        for(int j=0;j<=D-1;j++) dp[i][j]=-1;
        for(int j=0;j<3;j++)
            for(int k=0;k<=D-1;k++)
            {
                int last=(k-rating[i][j]%D+D)%D;
                if(dp[i+1][last]==-1) continue;
                mx(dp[i][k],dp[i+1][last]+rating[i][j]/D+(k<last?1:0));
            }
    }
    for(int i=0;i<=D-1;i++) dp[mid+1][i]=-1;
    for(int i=0;i<3;i++) mx(dp[mid+1][rating[mid+1][i]%D],rating[mid+1][i]/D);
    for(int i=mid+2;i<=r;i++)
    {
        for(int j=0;j<=D-1;j++) dp[i][j]=-1;
        for(int j=0;j<3;j++)
            for(int k=0;k<=D-1;k++)
            {
                int last=(k-rating[i][j]%D+D)%D;
                if(dp[i-1][last]==-1) continue;
                mx(dp[i][k],dp[i-1][last]+rating[i][j]/D+(k<last?1LL:0LL));
            }
    }
    for(auto q:now)
    {
        ll cur=-1;
        if(q.r==mid)
        {
            if(dp[q.l][0]==-1) ans[q.id]=-1; else ans[q.id]=dp[q.l][0]*D;
            continue;
        }
        for(int j=0;j<=D-1;j++)
        {
            int need=(D-j)%D;
            if(dp[q.l][j]==-1||dp[q.r][need]==-1) continue;
            mx(cur,dp[q.l][j]+dp[q.r][need]+(j>0?1LL:0LL));
        }
        if(cur==-1) ans[q.id]=-1; else ans[q.id]=cur*D;
    }
}
int main()
{
    scanf("%d%d",&n,&D);
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<3;j++)
        {
            int x;scanf("%d",&x);
            rating[i].push_back(x);
        }
    }
    vector<query> q;
    scanf("%d",&m);
    for(int i=0;i<m;i++)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        if(l==r)
        {
            ll cur=-1;
            for(int i=0;i<3;i++) if(rating[l][i]%D==0) cur=max(cur,(ll)rating[l][i]);
            ans[i+1]=cur;
            continue;
        }
        q.push_back((query){l,r,i+1});
    }
    solve(1,n,q);
    for(int i=1;i<=m;i++) printf("%lld\n",ans[i]);
    return 0;
}
