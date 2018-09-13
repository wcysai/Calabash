#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
int n,s;
int a[MAXN],cnt[MAXN][10];
int t,t1,t2;
int st[MAXN],ult[MAXN];
bool cmp(int x,int y) {return x>y;}
int dp[50][1024];
int solve(int cur,int mask)
{
    if(cur>t) return 0;
    if(dp[cur][mask]!=-1) return dp[cur][mask];
    int ultc=0;
    for(int i=0;i<2*n;i++) if((mask>>i)&1) ultc++;
    int stc=cur-1-ultc;
    if(a[cur]<=n)
    {
        int ret=-INF;
        int hasult=(mask>>(a[cur]-1))&1;
        int hasst=s-(cnt[cur-1][a[cur]]-hasult);
        if(hasst) ret=max(ret,st[stc+1]+solve(cur+1,mask));
        if(!hasult) ret=max(ret,ult[ultc+1]+solve(cur+1,mask|(1<<(a[cur]-1))));
        //printf("%d %d %d\n",cur,mask,ret);
        return dp[cur][mask]=ret;
    }
    else
    {
        int ret=INF;
        int hasult=(mask>>(a[cur]-1))&1;
        int hasst=s-(cnt[cur-1][a[cur]]-hasult);
        if(hasst) ret=min(ret,-st[stc+1]+solve(cur+1,mask));
        if(!hasult) ret=min(ret,-ult[ultc+1]+solve(cur+1,mask|(1<<(a[cur]-1))));
        //printf("%d %d %d\n",cur,mask,ret);
        return dp[cur][mask]=ret;
    }
}
int main()
{
    scanf("%d%d",&n,&s);
    t=2*n*(s+1);
    for(int i=1;i<=t;i++)
    {
        scanf("%d",&a[i]);
        for(int j=1;j<=2*n;j++) cnt[i][j]=cnt[i-1][j];
        cnt[i][a[i]]++;
    }
    scanf("%d",&t1); for(int i=1;i<=t1;i++) scanf("%d",&st[i]); sort(st+1,st+t1+1,cmp);
    scanf("%d",&t2); for(int i=1;i<=t2;i++) scanf("%d",&ult[i]); sort(ult+1,ult+t2+1,cmp);
    memset(dp,-1,sizeof(dp));
    printf("%d\n",solve(1,0));
}
