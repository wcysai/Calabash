/*************************************************************************
    > File Name: E.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-08-30 15:05:01
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 300005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
//#define __LOCAL_DEBUG__
#define PROBLEM_NAME  "jumping"
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a,b;
int prime[MAXN],d[MAXN];
bool is_prime[MAXN];
int bit[2][MAXN];
int _mod(int x) 
{
    if(x>=MOD) return x-MOD;
    if(x<0) return x+MOD;
    return x;
}
int sum(int id,int i)
{
    int s=0;
    while(i>0)
    {
        s=_mod(s+bit[id][i]);
        i-=i&-i;
    }
    return s;
}
void add(int id,int i,int x)
{
    while(i<=n)
    {
        bit[id][i]=_mod(bit[id][i]+x);
        i+=i&-i;
    }
}
int sieve(int n)
{
    int p=0;
    for(int i=0;i<=n;i++) is_prime[i]=true;
    is_prime[0]=is_prime[1]=false;
    for(int i=2;i<=n;i++)
    {
        if(is_prime[i]) prime[p++]=i;
        for(int j=0;j<p;j++)
        {
            if(prime[j]*i>n) break;
            is_prime[prime[j]*i]=false;
            if(i%prime[j]==0) break;
        }
    }
    return p;
}
void update(int l,int r,int x)
{
    if(l>r) return;
    add(0,l,-1LL*x*(l-1)%MOD);
    add(1,l,x);
    add(0,r+1,1LL*x*r%MOD);
    add(1,r+1,-x);
}
int query(int l,int r)
{
    if(l>r) return 0;
    int res=(sum(0,r)+1LL*sum(1,r)*r)%MOD;
    res=(res-sum(0,l-1)-1LL*sum(1,l-1)*(l-1))%MOD;
    res=_mod(res);
    return res;
}
int main()
{
    #ifndef __LOCAL_DEBUG__
        freopen(PROBLEM_NAME ".in", "r", stdin);
        freopen(PROBLEM_NAME ".out", "w", stdout);
    #endif
    int p=sieve(40000);
    scanf("%d%d",&a,&b);
    n=b-a+1;
    int ans=0;
    memset(d,0,sizeof(d));
    for(int i=a;i<=b;i++)
    {
        if(i<=40000&&is_prime[i]) continue;
        for(int j=0;j<p;j++)
        {
            if(i%prime[j]==0)
            {
                d[i-a+1]=prime[j];
                break;
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        int l,r,cur;
        if(d[i])
        {
            r=i-d[i],l=max(1,i-(a+i-1)/d[i]);
            cur=query(l,r)+((i==1)?1:0);
            if(i==n) ans=_mod(ans+cur);
            l=i+d[i],r=min(n,i+(a+i-1)/d[i]);
            update(l,r,cur);
        }
    }
    printf("%d\n",_mod(ans+query(n,n)));
    return 0;
}
