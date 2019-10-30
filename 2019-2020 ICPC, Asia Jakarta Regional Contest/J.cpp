#include<bits/stdc++.h>
#define MAXN 100005
#define MAXM 55
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int N,K,val[4];
string str;
vector<int> sharp;
bool valid[MAXN];
bool dp[MAXM][MAXM][MAXM][2];
bool compatible(int x,int y)
{
    return sharp[x]+2<sharp[y];
}
int main()
{
    scanf("%d%d",&N,&K);
    for(int i=1;i<=3;i++) scanf("%d",&val[i]);
    cin>>str;
    for(int i=0;i<N;i++)
    {
        if(str[i]=='#')
        {
            sharp.push_back(i);
            int cur=(int)sharp.size()-1;
            if(i==0||i==N-1||str[i-1]=='#'||str[i+1]=='#') valid[cur]=false; else valid[cur]=true;
        }
    }
    memset(dp,false,sizeof(dp));
    dp[0][0][0][0]=true;
    int sz=(int)sharp.size();
    for(int i=0;i<sz;i++)
    {
        for(int j=0;j<=i;j++)
        {
            for(int l=0;l<=i;l++)
            {
                for(int k=0;k<2;k++)
                {
                    if(!dp[i][j][l][k]) continue;
                    int last=0;
                    if(i!=0) last=(k?sharp[i-1]:sharp[i-1]+1);
                    int parity=(sharp[i]-last)&1;
                    dp[i+1][j+parity][l][0]=true;
                    if((valid[i])&&((i==0)||(!k)||(k&&compatible(i-1,i))))
                    {
                        dp[i+1][j+(parity^1)][l+1][1]=true;
                    }
                }
            }
        }
    }
    int ans=0;
    for(int i=0;i<=sz;i++)
        for(int j=0;j<=sz;j++)
            for(int k=0;k<2;k++)
            {
                if(!dp[sz][i][j][k]) continue;
                int odd=i;
                if(sz==0) odd+=(N&1);
                else
                {
                    int last=k?sharp[sz-1]+1:sharp[sz-1];
                    odd+=(N-1-last)&1;
                }
                int res=j*val[3];
                int cnt=N-(int)sharp.size()-2*j;
                int has2=(cnt-odd)/2,has1=odd;
                ans=max(ans,res+val[1]*min(K,has1)+val[2]*has2);
                if(has1<K)
                {
                    int offer=min(has2,(K-has1)/2);
                    has1+=2*offer; has2-=offer;
                    ans=max(ans,res+val[1]*has1+val[2]*has2);
                    if(has1<K&&has2) ans=max(ans,res+val[1]*(has1+1)+val[2]*(has2-1));
                }
            }
    printf("%d\n",ans);
    return 0;
}
