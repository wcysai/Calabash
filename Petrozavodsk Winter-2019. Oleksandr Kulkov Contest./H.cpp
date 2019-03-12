#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define INV 500000004
#define INV4 250000002
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
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
int t,m;
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&m);
        int l=1,r=INF;
        while(r-l>1)
        {
            int mid=(l+r)/2;
            if(4LL*mid*mid<=2LL*m*m+2LL*m) l=mid;
            else r=mid;
        }
        int k;
        if(1LL*m*m+m<2LL*l*(l+1)) k=l; else k=l+1;
        int ans=(1LL*m+INV-1LL*k*INV-(1LL*m*m%MOD+m)*INV4%MOD*pow_mod(k,MOD-2))%MOD;
        if(ans<0) ans+=MOD;
        printf("%d\n",ans);
    }
    return 0;
}
