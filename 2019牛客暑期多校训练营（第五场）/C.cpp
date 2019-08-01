#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<time.h>
#define MAXN 100005
#define INF 1000000000000000005LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,x0,a,b,p,q;
ll n;
P mul(P A,P B)
{
    P C;
    C.F=1LL*A.F*B.F%p;
    C.S=(1LL*A.F*B.S+1LL*A.S)%p;
    return C;
}
int pow_mod(int a,int i,int m)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%m;
        a=1LL*a*a%m;
        i>>=1;
    }
    return s;
}
P pow_mod(P A,ll n)
{
    P B;
    B.F=1; B.S=0;
    while(n>0)
    {
        if(n&1) B=mul(B,A);
        A=mul(A,A);
        n>>=1;
    }
    return B;
}
unordered_map<int,int> mp;
int main()
{
   // freopen("input.in","r",stdin);
   // freopen("output.out","w",stdout);
   // double start = clock() / (double)CLOCKS_PER_SEC;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld%d%d%d%d",&n,&x0,&a,&b,&p); mp.clear();
        if(x0==0&&b==0)
        {
            scanf("%d",&q);
            while(q--)
            {
                int x;
                scanf("%d",&x);
                if(x==0) puts("0"); else puts("-1");
            }
            continue;
        }
        else if(a==0)
        {
            scanf("%d",&q);
            while(q--)
            {
                int x;
                scanf("%d",&x);
                if(x==x0) puts("0"); else if(x==b&&n>1) puts("1"); else puts("-1");
            }
            continue;
        }
        else if(a==1)
        {
            scanf("%d",&q);
            while(q--)
            {
                int x;
                scanf("%d",&x);
                if(b==0)
                {
                    if(x==x0) puts("0"); else puts("-1");
                }
                else
                {
                    int turns=1LL*(x-x0+p)%p*pow_mod(b,p-2,p)%p;
                    if(turns>=n) puts("-1"); else printf("%d\n",turns);
                }
            }
            continue;
        }
        int inv=pow_mod(a,p-2,p);
        P trans=P(a,b);
        P invtrans=P(inv,(p-1LL*inv*b%p)%p);
        ll t=550000;
        P invtranst=pow_mod(invtrans,t);
        P cur=P(1,0);
        for(int i=0;i<550000;i++)
        {
            int res=(1LL*cur.F*x0+cur.S)%p;
            if(mp.find(res)==mp.end()) mp[res]=i; else break;
            cur=mul(cur,trans);
        }
        //cerr<<"done processing "<<c1ock() / (double)CLOCKS_PER_SEC - start)<<endl;
        //assert(mp.size()==1&&mp[0]==0);
        scanf("%d",&q);
        while(q--)
        {
            int x;
            scanf("%d",&x);
            P cur=P(1,0);
            ll ans=INF;
            for(int i=0;i<2000;i++)
            {
                int res=(1LL*cur.F*x+cur.S)%p;
                //printf("%lld %lld\n",ret.F,ret.S);
                if(mp.find(res)!=mp.end())
                {
                    ans=1LL*i*t+mp[res];
                    break;
                }
                cur=mul(cur,invtranst);
            }
            if(ans==INF||n<=ans) puts("-1");
            else printf("%lld\n",ans);
        }
       // cerr<<"done all"<<c1ock() / (double)CLOCKS_PER_SEC - start)<<endl;
    }
    return 0;
}





