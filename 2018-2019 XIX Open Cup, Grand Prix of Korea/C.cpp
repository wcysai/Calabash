#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define MAXN 5005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef pair<int,int> P;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
typedef __gnu_pbds::priority_queue<int,greater<int>,pairing_heap_tag> pq;
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
int pow_mod(int a,int i)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
int n,r,h,a,b,p,q;
char str[MAXN+1];
int dp1[MAXN][MAXN],dp2[MAXN][MAXN];
//p: probability of winning by hand
//q=1-p
int main()
{
    scanf("%d%d%d",&n,&r,&h);
    p=1LL*r*pow_mod(r+h,MOD-2)%MOD;
    q=(1-p+MOD)%MOD; 
    scanf("%s",str+1);
    scanf("%d%d",&a,&b);
    memset(dp1,0,sizeof(dp1));
    dp1[0][b]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=n;j++)
        {
            if(str[i]=='H')
            {
                add(dp1[i][j],dp1[i-1][j+1]);
            }
            else
            {
                if(j!=0) add(dp1[i][j],1LL*dp1[i-1][j]*p%MOD);
                if(j!=0) add(dp1[i][j],1LL*dp1[i][j-1]*q%MOD);
            }
        }
    }
    dp2[n+1][a]=1;
    for(int i=n;i>=1;i--)
    {
        for(int j=0;j<=n;j++)
        {
            if(str[i]=='R')
            {
                add(dp2[i][j],dp2[i+1][j+1]);
            }
            else
            {
                if(j!=0) add(dp2[i][j],1LL*dp2[i+1][j]*q%MOD);
                if(j!=0) add(dp2[i][j],1LL*dp2[i][j-1]*p%MOD);
            }
        }
    }
    int ans=0;
    for(int i=0;i<=n;i++) add(ans,1LL*dp1[i][0]*dp2[i+1][0]%MOD);
    printf("%d\n",ans);
    return 0;
}

