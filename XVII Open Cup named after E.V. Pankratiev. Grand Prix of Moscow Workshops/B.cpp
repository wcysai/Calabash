#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int prime[MAXN];
mt19937 wcy(time(NULL));
int val[MAXN];
bool isprime[MAXN];
int sieve(int n)
{
    int p=0;
    memset(isprime,true,sizeof(isprime));
    isprime[0]=isprime[1]=false;
    val[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(isprime[i]) {prime[p++]=i; if(i==3) val[i]=1; else val[i]=(i%3==1?1:-1);}
        for(int j=0;j<p;j++)
        {
            if(i*prime[j]>n) break;
            isprime[i*prime[j]]=false;
            val[i*prime[j]]=val[i]*val[prime[j]];
            if(i%prime[j]==0) break;
        }
    }
    return 0;
}
int calc(int n)
{
    int sum=0,maxi=0;
    for(int i=1;i<=1000000;i++) 
    {
        sum+=val[i];
        maxi=max(maxi,max(sum,-sum));
    }
    return maxi;
}
int n;
int main()
{
    scanf("%d",&n);
    sieve(1000000);
    for(int i=1;i<=n;i++) printf("%d ",val[i]);
    return 0;
}
