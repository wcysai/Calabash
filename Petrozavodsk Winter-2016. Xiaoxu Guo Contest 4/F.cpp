#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define MAXD 16
#define MAXM 256
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,d,d1,d2;
string str;
int a[MAXN][MAXD];
int dp[MAXM][MAXM];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
void update(int mask)
{
    int x=0;
    int mask1=(mask>>d2),mask2=mask&((1<<d2)-1);
    for(int i=0;i<(1<<d2);i++)
        if((mask2&i)==i) add(x,dp[mask1][i]);
    add(x,1);
    for(int i=0;i<(1<<d1);i++)
        if((mask1&i)==mask1) add(dp[i][mask2],x);
}
int main()
{
    scanf("%d%d",&n,&d);
    d1=d/2; d2=d-d1;
    for(int i=0;i<n;i++)
    {
        cin>>str;
        for(int j=0;j<d;j++) a[i][j]=str[j]-'0';
    }
    memset(dp,0,sizeof(dp));
    for(int i=0;i<n;i++)
    {
        int mask=0;
        for(int j=0;j<d;j++) mask=(mask<<1)+a[i][j];
        update(mask);
    }
    int ans=0;
    for(int i=0;i<(1<<d2);i++) add(ans,dp[(1<<d1)-1][i]);
    printf("%d\n",ans);
    return 0;
}

