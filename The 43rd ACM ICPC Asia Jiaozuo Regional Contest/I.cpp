#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,a[MAXN],sum[MAXN];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n-1;i++) scanf("%d",&a[i]);
        for(int i=1;i<=n-1;i++) sum[i]=sum[i-1]+a[i];
        ll l=0,r=n-1,lsum=0,rsum=0;
        ll ans=0;
        for(int i=1;i<=n;i++)
        {
            if(i&1)
            {
                ans+=rsum-lsum;
                rsum+=sum[r];r--;
            }
            else
            {
                ans+=rsum-lsum-sum[l];
                lsum+=sum[l];l++;
            }
            //printf("%d %d\n",lsum,rsum);
            printf("%lld%c",ans,i==n?'\n':' ');
        }
    }
    return 0;
}
