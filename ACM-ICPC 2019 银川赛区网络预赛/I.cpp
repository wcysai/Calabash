#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 105
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,k,q;
int a[MAXN];
int fact[MAXN],p[MAXN];
void add(int &a,int b) {a+=b; if(a>=q) a-=q;}
int pow_mod(int a,int i)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%q;
        a=1LL*a*a%q;
        i>>=1;
    }
    return s;
}
int main()
{
    scanf("%d",&T);
    for(int tot=1;tot<=T;tot++)
    {
        scanf("%d%d%d",&n,&k,&q);
        fact[0]=1;
        for(int i=1;i<=50;i++) fact[i]=1LL*fact[i-1]*i%q;
        if(k>n)
        {
            printf("Case #%d: %d\n",tot,fact[n]);
            continue;
        }
        p[0]=1;
        for(int i=1;i<=50;i++) p[i]=1LL*p[i-1]*(k+1)%q;
        int ans=p[n-k];
        for(int i=2;i<=n-k;i++) add(ans,1LL*p[n-k-1]*(n-k-i+1)%q);
        for(int i=3;i<=n-k;i++) add(ans,1LL*p[n-k-i+1]*(n-k-i+1)%q);
        ans=1LL*ans*fact[k]%q;
        printf("Case #%d: %d\n",tot,ans);
    }
    return 0;
}
