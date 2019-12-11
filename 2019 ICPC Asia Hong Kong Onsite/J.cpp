#include<bits/stdc++.h>
#define MAXN 5005
#define MAXM 65
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,L,R,m;
string str;
int p[MAXN],sz;
int dp[MAXN][MAXM][MAXM][2];
int table[64][64];
vector<int> v;
void addmod(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void decmod(int &a,int b) {a-=b; if(a<0) a+=MOD;}
void add(int &a,int b) {a+=b; if(a>=m) a-=m;}
void dec(int &a,int b) {a-=b; if(a<0) a+=m;}
void dec(string &str)
{
    int sz=(int)str.size();
    for(int i=sz-1;i>=0;i--)
    {
        str[i]--;
        if(str[i]>='0'&&str[i]<='9') return; else str[i]+=10;
    }
}
void preprocess(string str)
{
    v.clear();
    sz=(int)str.size();
    for(int i=0;i<sz;i++) v.push_back((int)str[i]-'0');
    for(int i=0;i<=sz;i++)
        for(int j=0;j<m;j++)
            for(int k=0;k<60;k++)
                for(int less=0;less<2;less++) 
                    dp[i][j][k][less]=0;
}
int solve()
{
    for(int sum=0;sum<m;sum++)
        for(int dif=0;dif<m;dif++)
            dp[sz][sum][dif][0]=dp[sz][sum][dif][1]=(dif==0);
    for(int now=sz-1;now>=0;now--)
        for(int presum=0;presum<m;presum++)
            for(int dif=0;dif<m;dif++)
            {
                for(int less=0;less<2;less++)
                {
                    int limit=(less?9:v[now]);
                    for(int i=0;i<=limit;i++)
                    {
                        int di=i<m?i:i%m;
                        int npresum=presum;
                        add(npresum,di);
                        int ndif=dif;
                        add(ndif,table[di][presum]);
                        dec(ndif,table[di][p[sz-1-now]]);
                        //add(ndif,1LL*di*presum%m);
                        //dec(ndif,1LL*di*p[sz-1-now]%m);
                        addmod(dp[now][presum][dif][less],dp[now+1][npresum][ndif][less|(i<limit)]);
                    }
                }
            }
    return dp[0][0][0][0];
}
string strl,strr;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        cin>>strl; cin>>strr;
        scanf("%d",&m);
        for (int i = 0; i < m; i++) for (int j = 0; j < m; j++) table[i][j] = i * j % m;
        p[0]=1;
        sz=(int)strr.size();
        for(int i=1;i<=sz;i++) p[i]=10LL*p[i-1]%m;
        preprocess(strr);
        int ans=solve();
        dec(strl);  preprocess(strl);
        decmod(ans,solve());
        printf("%d\n",ans);
    }
    return 0;
}