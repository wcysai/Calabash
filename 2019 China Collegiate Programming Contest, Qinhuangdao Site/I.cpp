#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
char str[MAXN];
int n;
int dist[30][30];
int a[3];
int dp[MAXN][30];
vector<int> masks[20];
map<int,int> hardcode;
map<char,int> mp;
int get_state(int mask)
{
    a[0]=mask%3; mask=mask/3;
    a[1]=mask%3; mask=mask/3;
    a[2]=mask%3; mask=mask/3;
    sort(a,a+3);
    int nmask=a[0]*9+a[1]*3+a[2];
    return hardcode[nmask];
}
int get_dist(int mask1,int mask2)
{
    if(mask1==mask2) return 0;
    if(mask1%9==mask2/3) return 1;
    if(mask1%3==mask2/9) return 2;
    return 3;
}
int main()
{
    hardcode[0]=0; hardcode[1]=1; hardcode[2]=2; hardcode[4]=4;
    hardcode[5]=9; hardcode[8]=7; hardcode[13]=3; hardcode[14]=5;
    hardcode[17]=8; hardcode[26]=6;
    mp['Y']=0; mp['V']=1; mp['G']=2; mp['C']=3; mp['X']=4;
    mp['Z']=5; mp['T']=6; mp['F']=7; mp['D']=8; mp['B']=9;
    for(int i=0;i<10;i++) masks[i].clear();
    for(int mask=0;mask<27;mask++)
        masks[get_state(mask)].push_back(mask);
    for(int mask1=0;mask1<27;mask1++)
        for(int mask2=0;mask2<27;mask2++)
            dist[mask1][mask2]=get_dist(mask1,mask2);
    scanf("%s",str+1);
    n=strlen(str+1);
    for(int i=0;i<=n;i++)
        for(int j=0;j<27;j++)
            dp[i][j]=INF;
    for(int i=0;i<27;i++) dp[0][i]=3;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<27;j++)
        {
            if(dp[i][j]==-1) continue;
            int state=mp[str[i+1]];
            for(auto mask:masks[state]) dp[i+1][mask]=min(dp[i+1][mask],dp[i][j]+dist[j][mask]+1);
        }
    }
    int ans=INF;
    for(int i=0;i<27;i++) ans=min(ans,dp[n][i]);
    printf("%d\n",ans);
    return 0;
}
