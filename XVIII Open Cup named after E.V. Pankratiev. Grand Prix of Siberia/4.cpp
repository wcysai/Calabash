#include<bits/stdc++.h>
#define MAXN 505
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
#define x1 fdkaod
#define y1 dkoadk
#define x2 dskaodas
#define y2 fdapldsd
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,x[MAXN],y[MAXN];
int dp[MAXN][MAXN],opt[MAXN][MAXN];
struct node
{
    int x1,y1,x2,y2;
};
vector<node> ans,calabash_gay;
void solve(int l,int r)
{
    if(l>r) return;
    if(opt[l][r]==l-1)
    {
        ans.push_back((node){x[l],y[l],x[l],y[r+1]});
        solve(l+1,r);
        return;
    }
    else if(opt[l][r]==r)
    {
        ans.push_back((node){x[r],y[r],x[l-1],y[r]});
        solve(l,r-1);
        return;
    }
    else
    {
        int v=opt[l][r];
        assert(v>=l&&v<=r);
        ans.push_back((node){x[v],y[v],x[l-1],y[v]});
        ans.push_back((node){x[v+1],y[v+1],x[v+1],y[r+1]});
        solve(l,v-1); solve(v+2,r);
        return;
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",&x[i],&y[i]);
    if(n==1)
    {
        printf("%d %d\n",2,x[1]+y[1]);
        printf("%d %d %d %d\n",x[1],y[1],0,y[1]);
        printf("%d %d %d %d\n",0,y[1],0,0);
        return 0;
    }
    ans.push_back((node){x[1],y[1],x[1],0});
    ans.push_back((node){x[n],y[n],x[1],y[n]});
    ans.push_back((node){x[1],0,0,0});
    int res=y[1]+x[n];
    for(int len=1;len<=n;len++)
    {
        for(int i=1;i+len-1<=n;i++)
        {
            int j=i+len-1;
            dp[i][j]=INF;
            if(dp[i+1][j]+y[i]-y[j+1]<dp[i][j])
            {
                opt[i][j]=i-1;
                dp[i][j]=dp[i+1][j]+y[i]-y[j+1];
            }
            if(dp[i][j-1]+x[j]-x[i-1]<dp[i][j])
            {
                opt[i][j]=j;
                dp[i][j]=dp[i][j-1]+x[j]-x[i-1];
            }
            for(int k=i;k<=j-1;k++)
            {
                int ldp=(k-1>=i?dp[i][k-1]:0);
                int rdp=(k+2<=j?dp[k+2][j]:0);
                if(ldp+rdp+(x[k]-x[i-1])+(y[k+1]-y[j+1])<dp[i][j])
                {
                    opt[i][j]=k;
                    dp[i][j]=ldp+rdp+(x[k]-x[i-1])+(y[k+1]-y[j+1]);
                }
            }
        }
    }
    solve(2,n-1);
    for(auto p:ans) if(p.x1!=p.x2||p.y1!=p.y2) calabash_gay.push_back(p);
    printf("%d %d\n",(int)calabash_gay.size(),dp[2][n-1]+res);
    for(auto p:calabash_gay) printf("%d %d %d %d\n",p.x1,p.y1,p.x2,p.y2);
    return 0;
}
