#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
int T,n,k,q;
int main()
{
    scanf("%d",&T);
    for(int t=1;t<=T;t++)
    {
        scanf("%d%d%d",&n,&k,&q);
        int ans=1;
        if(n<=k)
        {
            for(int i=1;i<=n;i++) ans=1LL*ans*i%q;
            printf("Case #%d: %d\n",t,ans);
            continue;
        }
        for(int i=1;i<=k;i++) ans=1LL*ans*i%q;
        int cur=(1LL*(n-k-1)*(n-k-1)+1)%q;
        cur=(cur+1LL*k*(n-k))%q;
        cur=(cur+n-k-1)%q;
        ans=1LL*ans*cur%q;
        printf("Case #%d: %d\n",t,ans);
    }
    return 0;
}
