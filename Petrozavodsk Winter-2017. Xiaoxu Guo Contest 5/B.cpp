/*************************************************************************
    > File Name: B.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-12-06 23:30:50
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 1005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll n;
bitset<MAXN> G[MAXN];
ll common[MAXN][MAXN],deg[MAXN],cnt[10];
char str[MAXN];
int main()
{
    while(scanf("%lld",&n)==1)
    {
        for(ll i=1;i<=n;i++) G[i].reset();
        for(ll i=1;i<=n;i++)
        {
            scanf("%s",str+1);
            for(ll j=1;j<=n;j++) G[i][j]=str[j]-'0';
        }
        memset(deg,0,sizeof(deg));
        memset(cnt,0,sizeof(cnt));
        for(ll i=1;i<=n;i++) deg[i]=G[i].count();
        for(ll i=1;i<=n;i++)
            for(ll j=1;j<=n;j++)
                common[i][j]=(G[i]&G[j]).count();
        ll ans=0;
        //type 1: cycle of length 3
        for(ll i=1;i<=n;i++)
            for(ll j=i+1;j<=n;j++)
                if(G[i][j]==1) cnt[1]+=common[i][j];
        cnt[1]/=3;
        ans+=cnt[1]*24;
        //type 2:cycle of length 4
        for(ll i=1;i<=n;i++)
            for(ll j=i+1;j<=n;j++)
                cnt[2]+=common[i][j]*(common[i][j]-1)/2;
        cnt[2]/=2;
        ans+=cnt[2]*48;
        //type 3:chain of 2 vertices
        for(ll i=1;i<=n;i++)
            for(ll j=i+1;j<=n;j++)
                if(G[i][j]==1) cnt[3]++;
        ans+=cnt[3]*2;
        //type 4:chain of 3 vertices
        for(ll i=1;i<=n;i++) cnt[4]+=deg[i]*(deg[i]-1)/2;
        ans+=cnt[4]*12;
        //type 5:chain of 4 vertices
        for(ll i=1;i<=n;i++)
            for(ll j=i+1;j<=n;j++)
                if(G[i][j]==1) cnt[5]+=(deg[i]-1)*(deg[j]-1);
        cnt[5]-=3*cnt[1];
        ans+=6*cnt[5];
        //type 6:claw of 4 vertices
        for(ll i=1;i<=n;i++) cnt[6]+=deg[i]*(deg[i]-1)*(deg[i]-2)/6;
        ans+=12*cnt[6];
        //type 7: a square with a diagonal
        for(ll i=1;i<=n;i++)
            for(ll j=i+1;j<=n;j++)
                if(G[i][j]==1) cnt[7]+=(common[i][j])*(common[i][j]-1)/2;
        ans+=36*cnt[7];
        //type 8:a square with one additional edge hanged one one of the vertices
        for(ll i=1;i<=n;i++)
            for(ll j=1;j<=n;j++)
            {
                if(i==j) continue;
                cnt[8]+=common[i][j]*(common[i][j]-1)/2*(deg[i]-2);
            }
        cnt[8]-=2*cnt[7];
        ans+=12*cnt[8];
        //type 9: two cycles of 3 vertices that share a common vertex
        for(ll i=1;i<=n;i++)
        {
            ll tmp=0;
            for(ll j=1;j<=n;j++) if(G[i][j]==1) tmp+=common[i][j];
            tmp/=2;
            cnt[9]+=tmp*(tmp-1)/2;
        }
        cnt[9]-=2*cnt[7];
        ans+=24*cnt[9];
        //for(ll i=1;i<=9;i++) printf("%lld ",cnt[i]);
        //puts("");
        printf("%lld\n",ans);
    }
    return 0;
}

