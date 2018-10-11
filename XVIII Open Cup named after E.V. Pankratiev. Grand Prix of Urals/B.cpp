#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll L,R,Q;
int main()
{
    scanf("%lld%lld%lld",&L,&R,&Q);
    if(Q>R) {puts("infinity"); return 0;}
    L=max(L,Q);
    ll l=L-L%Q,r=R-R%Q;
    if(l==r)
    {
        if(r==0) {puts("infinity"); return 0;}
        ll ans=0;
        for(ll i=1;i*i<=l;i++)
        {
            if(l%i) continue;
            ans++;
            if(i*i!=l) ans++;
        }
        printf("%lld\n",ans);
        return 0;
    }
    ll ans=0;
    for(ll i=1;i*i<=Q;i++)
    {
        if(Q%i) continue;
        ans++;
        if(i*i!=Q) ans++;
    }
    printf("%lld\n",ans);
    return 0;
}
