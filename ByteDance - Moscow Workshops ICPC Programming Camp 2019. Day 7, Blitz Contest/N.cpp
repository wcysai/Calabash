#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAXN 2000005
#define INF 1000000001
#define MOD 998244353
#define F first
#define S second
int n,k,z;
int x[5005],y[5005];
int sum[MAXN];
int main()
{
    while(scanf("%d%d%d",&n,&k,&z)==3)
    {
        if(!n&&!k&&!z) break;
        for(int i=1;i<=2*z;i++) sum[i]=0;
        for (int i=0;i<n;i++)
        {
            scanf("%d%d",&x[i],&y[i]);
        }
        for(int i=0;i<n;i++)
            for(int j=i+1;j<n;j++)
            {
                int res=abs(x[i]-x[j])+abs(y[i]-y[j]);
                if(res>2*z) continue;
                sum[res]++;
            }
        for(int i=1;i<=2*z;i++) sum[i]+=sum[i-1];
        for(int i=0;i<k;i++)
        {
            int l,r;
            scanf("%d%d",&l,&r);
            printf("%d\n",sum[r]-sum[l-1]);
        }
        puts("");
    }
    return 0;
}
