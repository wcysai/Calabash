#include<bits/stdc++.h>
#define MAXN 3005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,p,n;
int comb[MAXN][MAXN];
int ways[MAXN][MAXN];
int val[MAXN],ans[MAXN],cnt[MAXN],num[MAXN];
int pw[MAXN][MAXN];
int fact[MAXN],notwofact[MAXN];
int pow_mod(int a,int i)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%p;
        a=1LL*a*a%p;
        i>>=1;
    }
    return s;
}
void add(int &a,int b) {a+=b; if(a>=p) a-=p;}
int main()
{
    scanf("%d%d",&T,&p);
    fact[0]=1;
    for(int i=1;i<=3000;i++) fact[i]=1LL*fact[i-1]*i%p;
    notwofact[2]=1;
    for(int i=3;i<=3000;i++) notwofact[i]=1LL*notwofact[i-1]*i%p;
    for(int i=1;i<=3000;i++)
    {
        pw[i][0]=1%p;
        for(int j=1;j<=3000;j++) pw[i][j]=1LL*pw[i][j-1]*i%p;
    }
    comb[0][0]=1;
    for(int i=1;i<=3000;i++)
    {
        comb[i][0]=comb[i][i]=1;
        for(int j=1;j<i;j++) 
        {
            comb[i][j]=comb[i-1][j-1];
            add(comb[i][j],comb[i-1][j]);
        }
    }
    for(int i=1;i<=3000;i++)
    {
        if(i==1)
        {
            ways[i][1]=1;
            continue;
        }
        if(i==2)
        {
            ways[i][1]=ways[i][2]=1;
            continue;
        }
        ways[i][1]=ways[i][2]=pw[i][i-2];
        for(int j=3;j<i;j++) ways[i][j]=1LL*comb[i][j]*notwofact[j]%p*pw[i][i-j-1]%p;
        ways[i][i]=notwofact[i-1];
    }
    for(int i=1;i<=3000;i++) 
        for(int j=1;j<=i;j++)
        {
            if(j==2) continue;
            add(cnt[i],ways[i][j]); 
            if(j>=3) add(val[i],1LL*ways[i][j]*j%p);
        }
    num[0]=1;num[1]=1;num[2]=2;
    for(int i=3;i<=3000;i++)
    {
        num[i]=cnt[i];
        for(int j=1;j<i;j++) add(num[i],1LL*comb[i-1][j-1]*cnt[j]%p*num[i-j]%p);
    }
    for(int i=3;i<=3000;i++)
        for(int j=1;j<=i;j++)
        {
            add(ans[i],1LL*comb[i-1][j-1]*ans[i-j]%p*cnt[j]%p);
            add(ans[i],1LL*comb[i-1][j-1]*num[i-j]%p*val[j]%p);
        }
    while(T--)
    {
         scanf("%d",&n);
         printf("%d\n",ans[n]%p);
    }
    return 0;
}
