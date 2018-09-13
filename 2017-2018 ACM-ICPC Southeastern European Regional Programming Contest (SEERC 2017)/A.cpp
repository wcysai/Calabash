#include<bits/stdc++.h>
#define MAXN 100005
#define MAXK 305
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,d[26],dp[2][MAXN];
string str1,str2;
int find_ans(int i,int j)
{
    if(j>n) return i>k?1:0;
    if(dp[i&1][j]!=-1) return dp[i&1][j];
    if(str1[i-1]==str2[j-1]) return dp[i&1][j]=(find_ans(i,j+1)+find_ans(i+1,j+d[str1[i-1]-'A']+1))%MOD;
    return dp[i&1][j]=find_ans(i,j+1);
}
int main()
{
    scanf("%d%d",&k,&n);
    for(int i=0;i<26;i++) scanf("%d",&d[i]);
    cin>>str1;
    cin>>str2;
    memset(dp,-1,sizeof(dp));
    for(int j=1;j<=n;j++)
        dp[(k+1)&1][j]=1;
    for(int i=k;i>=1;i--)
    {
        for(int j=0;j<=n+1;j++)
            dp[(i&1)][j]=-1;
        for(int j=1;j<=n;j++) {
            if (dp[i & 1][j] == -1) dp[i & 1][j] = find_ans(i, j);
            //printf("%d ", dp[i & 1][j]);
        }
        //puts("");
    }
    printf("%d\n",dp[1][1]);
    return 0;
}
