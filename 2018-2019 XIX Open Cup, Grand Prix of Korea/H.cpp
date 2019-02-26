#include<bits/stdc++.h>
#define MAXN 100005
using namespace std;
typedef long long ll;
ll A,B,C,D;
int main()
{
    scanf("%lld%lld%lld%lld",&A,&B,&C,&D);
    ll ans=0;
    for(int i=1;i<999;i++)
        for(int j=1;i+j<=999;j++)
        {
            if(__gcd(i,j)>1) continue;
            if(i>B||j>D) continue;
            ll l1=(A-1)/i+1,r1=B/i,l2=(C-1)/j+1,r2=D/j;
            l1=max(l1,l2);r1=min(r1,r2);
            ans+=max(0LL,r1-l1+1);
        }
    printf("%lld\n",ans);
    return 0;
}
