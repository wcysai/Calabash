#include<bits/stdc++.h>
#define MAXN 305
#define MAXM 150005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef __int128 int128;
int T,n;
int128 k;
int128 dp[30][30];
void scan(int128 &x)
{
    x = 0;
    int f = 1;
    char ch;
    if((ch = getchar()) == '-') f = -f;
    else x = x*10 + ch-'0';
    while((ch = getchar()) >= '0' && ch <= '9')
        x = x*10 + ch-'0';
    x *= f;
}
void print(int128 x)
{
    if(x > 9) print(x/10);
    putchar(x%10 + '0');
}
int main()
{
    for(int i=0;i<=26;i++) dp[0][i]=1;
    for(int i=1;i<=26;i++)
        for(int j=0;j<=26;j++)
            dp[i][j]=j*dp[i-1][j]+dp[i-1][j+1];
    scanf("%d",&T);
    for(int t=1;t<=T;t++)
    {
        scanf("%d ",&n); scan(k);
        int now=0;
        string str="";
        for(int i=1;i<=n;i++)
        {
            if(k>now*dp[n-i][now])
            {
                k-=now*dp[n-i][now];
                str+=(char)('A'+now);
                now++;
            }
            else
            {
                int id=(k-1)/dp[n-i][now];
                str+=(char)('A'+id);
                k-=id*dp[n-i][now];
            }
        }
        printf("Case #%d: ",t);
        cout<<str<<endl;
    }
    return 0;
}
