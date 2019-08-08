#include<bits/stdc++.h>
#define MAXN 35
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,A,B,C;
void add(ll &a,ll b) {a+=b;}
ll dp[MAXN][3][3][2][2];
vector<int> v1,v2,v3;
ll solve(int now,int state1,int state2,int eq1,int eq2)
{
    if(now==30) return ((state1==2||state2==0)?1:0);
    if(dp[now][state1][state2][eq1][eq2]!=-1) return dp[now][state1][state2][eq1][eq2];
    ll &res=dp[now][state1][state2][eq1][eq2];
    res=0;
    int limit1=(eq1?v1[now]:1);
    int limit2=(eq2?v2[now]:1);
    for(int i=0;i<=limit1;i++)
        for(int j=0;j<=limit2;j++)
        {
            int nstate1,nstate2;
            if(state1==1)
            {
                int x=i&j;
                if(x==v3[now]) nstate1=1;
                else nstate1=(x>v3[now]?2:0);
            }
            else nstate1=state1;
            if(state2==1)
            {
                int x=i^j;
                if(x==v3[now]) nstate2=1;
                else nstate2=(x>v3[now]?2:0);
            }
            else nstate2=state2;
            add(res,solve(now+1,nstate1,nstate2,eq1&&(i==limit1),eq2&&(j==limit2)));
        }
    return res;
}
void parse(int x,vector<int> &v)
{
    for(int i=0;i<30;i++)
    {
        v.push_back(x&1);
        x>>=1;
    }
    reverse(v.begin(),v.end());
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&A,&B,&C);
        v1.clear(); v2.clear(); v3.clear();
        parse(A,v1); parse(B,v2); parse(C,v3);
        memset(dp,-1,sizeof(dp));
        ll ans=solve(0,1,1,1,1);
        ans-=min(C-1,A); ans-=min(C-1,B);
        ans--;
        printf("%lld\n",ans);
    }
    return 0;
}
