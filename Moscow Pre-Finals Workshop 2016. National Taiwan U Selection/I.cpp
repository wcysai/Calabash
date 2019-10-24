#include<bits/stdc++.h>
#define MAXN 100005
#define MAXLOGN 21
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int m,T;
ll dp[MAXLOGN][10][2][3];
//0 equal
//1 decreasing
//2 increasing
vector<int> v;
ll pre[3][MAXLOGN][10],sum[3][MAXLOGN][10];
ll norestrict[3][MAXLOGN];
ll solve(int now,int last,int lead,int type)
{
    if(now==(int)v.size()) return lead?0:1;
    if(dp[now][last][lead][type]!=-1) return dp[now][last][lead][type];
    ll &res=dp[now][last][lead][type];
    res=0;
    int x=v[now];
    if(lead||(type==0&&last==x)||(type==1&&last>=x)||(type==2&&last<=x)) res+=solve(now+1,x,lead&&(x==0),type);
    int l=0,r=9;
    if(type!=1&&!lead) l=last;
    if(type!=2&&!lead) r=last;
    r=min(r,x-1);
    //assert(r<=0);
    if(l<=r)
    {
        int rem=(int)v.size()-now;
        if(lead&&l==0)
        {
            l++;
            res+=norestrict[type][rem-1];
        }
        if(l==0) res+=sum[type][rem-1][r];
        else
        {
            res+=sum[type][rem-1][r];
            res-=sum[type][rem-1][l-1];
        }
    }
    return res;
}
ll get_ans(ll x)
{
    if(x==0) return 0;
    memset(dp,-1,sizeof(dp));
    v.clear();
    while(x)
    {
        v.push_back(x%10);
        x/=10;
    }
    reverse(v.begin(),v.end());
    ll ans=0;
    int sz=(int)v.size();
    ans+=solve(0,0,1,1);
    ans+=solve(0,0,1,2);
    ans-=solve(0,0,1,0);
    //ans-=sum[0][sz-1][v[0]-1]+solve(1,v[0],0,0);
    return ans;
}
int main()
{
    for(int i=0;i<10;i++) pre[0][0][i]=pre[1][0][i]=pre[2][0][i]=1;
    for(int i=1;i<=20;i++)
        for(int j=0;j<10;j++)
        {
            pre[0][i][j]=pre[0][i-1][j];
            for(int k=0;k<=j;k++) pre[1][i][j]+=pre[1][i-1][k];
            for(int k=j;k<=9;k++) pre[2][i][j]+=pre[2][i-1][k];
        }
    for(int type=0;type<3;type++)
    {
        norestrict[type][0]=0;
        for(int i=1;i<=20;i++)
        {
            norestrict[type][i]+=norestrict[type][i-1];
            for(int j=1;j<=9;j++) norestrict[type][i]+=pre[type][i-1][j];
        }
    }
    for(int type=0;type<3;type++)
        for(int i=0;i<=20;i++)
        {
            sum[type][i][0]=pre[type][i][0];
            for(int j=1;j<=9;j++) sum[type][i][j]=sum[type][i][j-1]+pre[type][i][j];
        }
    scanf("%d",&T);
    while(T--)
    {
        ll x,y;
        scanf("%lld%lld",&x,&y);
        ll ans=get_ans(y)-get_ans(x-1);
        printf("%lld\n",ans);
    }
    return 0;
}
