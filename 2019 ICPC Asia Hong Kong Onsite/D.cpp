#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,k,X;
ll p[MAXN],sum[MAXN];
string get_str(int base,int X)
{
    string t="";
    int now;
    p[0]=1; sum[0]=0;
    for(int i=1;i<=30;i++) p[i]=p[i-1]*base,sum[i]=sum[i-1]+p[i];
    for(now=1;sum[now]<X;now++);
    bool f=true;
    for(;now>=1;now--)
    {
        int cur;
        if(f) cur=(X-sum[now-1]+p[now-1]-1)/p[now-1]; else cur=(X+p[now-1]-1)/p[now-1];
        t+=(char)'0'+(10-base)+(cur-1);
        if(f) {X-=sum[now-1]; f=false;} 
        X-=1LL*(cur-1)*p[now-1];
    }
    return t;
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        int k,X;
        scanf("%d%d",&k,&X);
        cout<<get_str(k,X)<<endl;
    }
    return 0;
}
