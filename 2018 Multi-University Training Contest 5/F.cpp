/*************************************************************************
    > File Name: F.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-08-07 12:51:13
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 33
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,p[MAXN],inv[MAXN];
int c[MAXN][MAXN],a[MAXN],b[MAXN][MAXN],f[MAXN];
ll m;
struct Subset
{
    int cnt;
    pair<ll,int> val[1<<16|1];
    void parse(int n,int a[])
    {
        cnt=1<<n;
        for(int i=0;i<cnt;i++)
        {
            ll sum=0;
            int k=0;
            for(int j=0;j<n;j++)
            {
                if((i>>j)&1)
                {
                    sum+=a[j];
                    k++;
                }
            }
            val[i]=make_pair(sum,k);
        }
        sort(val,val+cnt);
    }
}lft,rht;
int main()
{
    inv[1]=1;
    for(int i=2;i<MAXN;i++) inv[i]=MOD-(int)(1LL*MOD/i*inv[MOD%i]%MOD);
    for(int i=0;i<MAXN;i++)
    {
        c[i][0]=c[i][i]=1;
        for(int j=1;j<i;j++)
        {
            c[i][j]=c[i-1][j-1]+c[i-1][j];
            if(c[i][j]>=MOD) c[i][j]-=MOD;
        }
    }
    scanf("%d",&T);
    while(T--)
    {
        m=0;
        scanf("%d",&n);
        for(int i=0;i<n;i++) scanf("%d",&p[i]);
        for(int i=0;i<n;i++) m+=p[i]-1;
        m>>=1;a[0]=1;
        for(int i=1;i<n;i++)
        {
            int coeff0=1LL*(m+i)%MOD*inv[i]%MOD;
            int coeff1=MOD-inv[i];
            a[i]=1LL*coeff1*a[i-1]%MOD;
            for(int j=i-1;j>0;j--)
                a[j]=(1LL*coeff0*a[j]+1LL*coeff1*a[j-1])%MOD;
            a[0]=1LL*coeff0*a[0]%MOD;
        }
        for(int i=0;i<n;i++)
            for(int j=i;j<n;j++)
                b[i][j]=1LL*a[j]*c[j][i]%MOD;
        int half=n>>1;
        lft.parse(half,p);
        rht.parse(n-half,p+half);
        memset(f,0,n*sizeof(int));
        int ans=0;
        for(int i=lft.cnt-1,j=0;i>=0;i--)
        {
            for(;j<rht.cnt&&lft.val[i].F+rht.val[j].F<=m;j++)
            {
                int cur=rht.val[j].S&1?MOD-1:1,prd=rht.val[j].F%MOD;
                for(int x=0;x<n;x++)
                {
                    f[x]+=cur;
                    if(f[x]>=MOD) f[x]-=MOD;
                    cur=1LL*cur*prd%MOD;
                }
            }
            int cur=lft.val[i].S&1?MOD-1:1,prd=lft.val[i].F%MOD;
            for(int x=0;x<n;x++)
            {
                int sum=0;
                for(int y=x;y<n;y++)
                    sum=(sum+1LL*b[x][y]*f[y-x])%MOD;
                ans=(ans+1LL*cur*sum)%MOD;
                cur=1LL*cur*prd%MOD;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
