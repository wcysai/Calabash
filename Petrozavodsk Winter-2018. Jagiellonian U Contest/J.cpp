#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 2000005
#define INF 1000000000
#define MOD 1000000009
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef long double db;
const db eps=1e-3;
int T,t,m,x,tot;
db lg[MAXN],pre[MAXN];
int prime[MAXN],val[MAXN],fact[MAXN],invf[MAXN];
bool is_prime[MAXN];
mt19937 wcy(time(NULL));
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
    fact[0]=invf[0]=1;tot=0;
    for(int i=1;i<=2000000;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[2000000]=pow_mod(fact[2000000],MOD-2);
    for(int i=1999999;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    for(int i=1;i<=2000000;i++) lg[i]=log((db)i);
    for(int i=1;i<=2000000;i++) pre[i]=pre[i-1]+lg[i];
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&t,&m);
        db ans=0;
        int v=1;
        for(int i=1;i<=t;i++)
        {
            scanf("%d",&x); v=1LL*v*x%MOD;
            ans+=lg[x];
        }
        bool f=false;
        for(int i=1;i<=m;i++)
        {
            int l=1,r=m-i+2;
            while(r-l>1)
            {
                int mid=(l+r)/2;
                db res=pre[mid+i-1]-pre[mid-1]-pre[i];
                if(res<=ans) l=mid; else r=mid;
            }
            for(int j=max(1,l-20);j<=min(m-i+1,l+20);j++)
            {
                if(1LL*fact[j+i-1]*invf[j-1]%MOD*invf[i]%MOD==v)
                {
                    puts("YES");
                    printf("%d %d\n",j+i-1,i);
                    f=true;
                    break;
                }
            }
            if(f) break;
        }
        if(!f) puts("NO");
    }
    return 0;
}
