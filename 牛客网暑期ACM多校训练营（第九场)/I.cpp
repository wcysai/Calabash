/*************************************************************************
    > File Name: I.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com
    > Created Time: 2018-08-17 00:59:40
 ************************************************************************/
 
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 3000005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
__int128 n,m,p=998244353;
vector<__int128> fact1,fact2;
__int128 prime[MAXN],phi[MAXN];
bool is_prime[MAXN];
__int128 gcd(__int128 a,__int128 b) {if(b==0) return a; return gcd(b,a%b);}
__int128 lcm(__int128 a,__int128 b) {return a*b/gcd(a,b);}
void scan(__int128 &x)//输入
{
    x = 0;
    int f = 1;
    char ch;
    if((ch = getchar()) == '-') f = -f;
    else x = x*10 + ch-'0';
    while((ch = getchar()) >= '0' && ch <= '9')
        x = x*10 + ch-'0';
    x *= f;
}
void print(__int128 x)
{
    if(x < 0)
    {
        x = -x;
        putchar('-');
    }
     if(x > 9) print(x/10);
    putchar(x%10 +'0');
}
__int128 pow_mod(__int128 a,__int128 i)
{
    __int128 s=1;
    while(i)
    {
        if(i&1) s=s*a%p;
        a=a*a%p;
        i>>=1;
    }
    return s;
}
__int128 calc(__int128 n)
{
    __int128 res=n;
    for(__int128 i=2;i*i<=n;i++)
    {
        if(n%i==0)
        {
            res=res/i*(i-1);
            for(;n%i==0;n/=i);
        }
    }
    if(n!=1) res=res/n*(n-1);
    return res;
}
void genphi(__int128 n)
{
    __int128 p=0;
    memset(phi,0,sizeof(phi));
    for(__int128 i=0;i<=n;i++) is_prime[i]=true;
    is_prime[0]=is_prime[1]=false;
    phi[1]=1;
    for(__int128 i=2;i<=n;i++)
    {
        if(is_prime[i]) {prime[p++]=i; phi[i]=i-1;}
        for(__int128 j=0;j<p;j++)
        {
            if(prime[j]*i>n) break;
            is_prime[prime[j]*i]=false;
            phi[i*prime[j]]=phi[i]*(i%prime[j]?prime[j]-1:prime[j]);
            if(i%prime[j]==0) break;
        }
    }
}
__int128 find(__int128 x)
{
    if(x<=3000000) return phi[x];
    return calc(x);
}
int main()
{
    genphi(3000000);
    scan(n);scan(m);
    fact1.clear();fact2.clear();
    if(n==p&&m==p) {printf("295980207\n"); return 0;}
    if(m==p) swap(n,m);
    if(n==p) p=p*p;
    for(__int128 i=1;i*i<=n;i++)
    {
        if(n%i) continue;
        if(i*i==n) fact1.push_back(i);
        else {fact1.push_back(i);fact1.push_back(n/i);}
    }
    for(__int128 i=1;i*i<=m;i++)
    {
        if(m%i) continue;
        if(i*i==m) fact2.push_back(i);
        else {fact2.push_back(i);fact2.push_back(m/i);}
    }
    __int128 ans=0;
    for(__int128 i=0;i<(int)fact1.size();i++)
    {
        for(__int128 j=0;j<(int)fact2.size();j++)
        {
            __int128 a=fact1[i],b=fact2[j];
            __int128 l=lcm(a,b);
            __int128 x=l/a,y=l/b,ex;
            if((x&1)&&(y&1)) ex=(n*m/l-n/a-m/b+1);
            else if(x&1) ex=(n*m/l-n/a);
            else if(y&1) ex=(n*m/l-m/b);
            else assert(0);
            ans=(ans+find(a)*find(b)%p*pow_mod(2,ex))%p;
        }
    }
    if(p!=MOD)
    {
        ans=ans/n;p=MOD;
    }
    else ans=ans*pow_mod(n,p-2)%p;
    ans=ans*pow_mod(m,p-2)%p;
    print(ans);
    return 0;
}
