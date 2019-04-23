#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 2005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int a[MAXN],b[MAXN],f[MAXN][MAXN][2],g[MAXN][MAXN][2];
int n,m,save[MAXN][MAXN][2];
//0: last is <
//1: otherwise
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
int bit[MAXN][MAXN][2];
int sum(int id,int i,int type)
{
    int s=0;
    while(i)
    {
        add(s,bit[id][i][type]);
        i-=i&-i;
    }
    return s;
}
void add(int id,int i,int type,int x)
{
    while(i<=2000)
    {
        add(bit[id][i][type],x);
        i+=i&-i;
    }
}
void dec(int id,int i,int type,int x)
{
    while(i<=2000)
    {
        dec(bit[id][i][type],x);
        i+=i&-i;
    }
}
void update(int id,int l,int r,int type,int v)
{
    add(id,l,type,v); dec(id,r+1,type,v);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=m;i++) scanf("%d",&b[i]);
    memset(f,0,sizeof(f)); memset(g,0,sizeof(g));
    for(int i=1;i<=n;i++) g[i][0][1]=1; 
    for(int i=1;i<=n;i++)
        for(int j=0;j<=m;j++)
            for(int k=0;k<2;k++)
            {
                add(g[i][j][k],sum(j,a[i],k));
                add(f[i][j][k],save[i][b[j]][k]);
                if(f[i][j][k])
                {
                    if(k==0) update(j,1,a[i]-1,1,f[i][j][k]);
                    else update(j,a[i]+1,2000,0,f[i][j][k]);
                }
                add(save[i][a[i]][k],g[i][j][k]);
            }
    int ans=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            for(int k=0;k<2;k++)
                add(ans,f[i][j][k]);
    printf("%d\n",ans);
    return 0;
}
