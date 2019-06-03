#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,A,B,C,D;
int fact[MAXN],fact2[MAXN];
int invf[MAXN],invf2[MAXN];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
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
int solve(int val,int x,int y)
{
    if(x==0||y==0) return 1;
    if(val==1) return 1LL*invf2[x+y-1]*fact2[x-1]%MOD*fact2[y-1]%MOD;
    return 1LL*invf2[val+x+y-2]*fact2[val+x-2]%MOD*fact2[val+y-2]%MOD*invf2[val-2]%MOD;
}
int main()
{
    fact[0]=fact2[0]=invf[0]=invf2[0]=1;
    for(int i=1;i<=1000000;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[1000000]=pow_mod(fact[1000000],MOD-2);
    for(int i=999999;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    for(int i=1;i<=1000000;i++) fact2[i]=1LL*fact2[i-1]*fact[i]%MOD;
    invf2[1000000]=pow_mod(fact2[1000000],MOD-2);
    for(int i=999999;i>=1;i--) invf2[i]=1LL*invf2[i+1]*fact[i+1]%MOD;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d%d",&A,&B,&C,&D);
        A-=B-1; C-=D-1;
        if(A>=C) {swap(A,C); swap(B,D);}
        if(B<=D) 
        {
            int ans=fact[C*D];
            ans=1LL*ans*solve(1,C,D)%MOD;
            printf("%d\n",ans);
        }
        else
        {
            int ans=fact[B*C-(C-A)*(B-D)];
            ans=1LL*ans*solve(1,C-A,D)%MOD*solve(1,B-D,A)%MOD*solve(B+C-A-D+1,A,D)%MOD;
            printf("%d\n",ans);
        }
    }
}
