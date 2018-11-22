#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
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
int main()
{
    freopen("cover.in","r",stdin);
    freopen("cover.out","w",stdout);
    while(true)
    {
        scanf("%d",&n);
        if(n==0) break;
        int ans=0;
        for(int k=1;k<=n;k++)
        {
            int rem=(k-n%k); if(rem>=k) rem-=k;
            add(ans,pow_mod(2,k-rem));
        }
        printf("%d\n",ans);
    }
    return 0;
}
