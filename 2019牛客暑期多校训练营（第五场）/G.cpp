#include<bits/stdc++.h>
#define MAXN 3005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
char s[MAXN],t[MAXN];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
int T,n,m,cnts[MAXN],cntt[MAXN];
int f[MAXN][MAXN][2];
int solve(int i,int j,int gr)
{
    if(j==m+1) return (gr?1:0);
    if(i==n+1) return 0;
    if(f[i][j][gr]!=-1) return f[i][j][gr];
    int &res=f[i][j][gr];
    res=0;
    if(i<=n) add(res,solve(i+1,j,gr));
    if(!gr&&s[i]<t[j]) return res;
    add(res,solve(i+1,j+1,gr|(s[i]>t[j]?1:0)));
    return res;
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        scanf("%s",s+1); scanf("%s",t+1);
        for(int i=1;i<=n;i++) cnts[i]=0;
        for(int i=1;i<=m;i++) cntt[i]=0;
        for(int i=1;i<=n;i++)
        {
            for(int j=i;j>=2;j--) add(cnts[j],cnts[j-1]);
            if(s[i]!='0') add(cnts[1],1);
        }

        for(int i=1;i<=m;i++)
        {
            for(int j=i;j>=2;j--) add(cntt[j],cntt[j-1]);
            if(t[i]!='0') add(cntt[1],1);
        }
        int ans=0;
        for(int i=m+1;i<=n;i++) add(ans,1LL*cnts[i]*cntt[m]%MOD);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                f[i][j][0]=f[i][j][1]=-1;
        add(ans,solve(1,1,0));
        printf("%d\n",ans);
    }
    return 0;
}
