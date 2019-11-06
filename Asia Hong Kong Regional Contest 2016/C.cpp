#include<bits/stdc++.h>
#define MAXN 50005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int N;
P res[MAXN];
P preg[MAXN],sufg[MAXN],prel[MAXN],sufl[MAXN];
P minans[MAXN],maxans[MAXN];
int sgn(P p,P q)
{
    if(p.F==q.F&&p.S==q.S) return 0;
    double x=p.F*log(2.0)+p.S*log(3.0);
    double y=q.F*log(2.0)+q.S*log(3.0);
    return x>y?1:-1;
}
P gcd(P x,P y)
{
    return P(min(x.F,y.F),min(x.S,y.S));
}
P lcm(P x,P y)
{
    return P(max(x.F,y.F),max(x.S,y.S));
}
int main()
{
    scanf("%d",&N);
    for(int i=1;i<=N;i++) scanf("%d%d",&res[i].F,&res[i].S);
    if(N==1)
    {
        printf("%d %d %d %d\n",res[1].F,res[1].S,res[1].F,res[1].S);
        return 0;
    }
    preg[0]=P(2001,2001); prel[0]=P(0,0);
    for(int i=1;i<=N;i++) 
    {
        preg[i]=gcd(preg[i-1],res[i]);
        prel[i]=lcm(prel[i-1],res[i]);
    }
    sufg[N+1]=P(2001,2001); sufl[N+1]=P(0,0);
    for(int i=N;i>=1;i--)
    {
        sufg[i]=gcd(sufg[i+1],res[i]);
        sufl[i]=lcm(sufl[i+1],res[i]);
    }
    P p=P(0,0);
    for(int i=1;i<=N;i++) p=lcm(p,res[i]);
    minans[0]=maxans[0]=p; 
    p=P(2001,2001);
    for(int i=1;i<=N;i++) p=gcd(p,res[i]);
    minans[N-1]=maxans[N-1]=p;
    p=P(2001,2001);
    for(int i=1;i<=N;i++)
    {
        P q=gcd(res[i],lcm(prel[i-1],sufl[i+1]));
        if(sgn(q,p)<0) p=q;
    }
    minans[1]=p;
    int minf=2000,mins=2000;
    for(int i=1;i<=N;i++)
    {
        minf=min(minf,res[i].F);
        mins=min(mins,res[i].S);
    }
    for(int i=2;i<=N-1;i++) minans[i].F=minf,minans[i].S=mins;
    p=P(0,0);
    for(int i=1;i<=N;i++)
    {
        P q=lcm(res[i],gcd(preg[i-1],sufg[i+1]));
        if(sgn(q,p)>0) p=q;
    }
    maxans[N-2]=p;
    int maxf=0,maxs=0;
    for(int i=1;i<=N;i++)
    {
        maxf=max(maxf,res[i].F);
        maxs=max(maxs,res[i].S);
    }
    for(int i=N-3;i>=0;i--) maxans[i].F=maxf,maxans[i].S=maxs;
    for(int i=0;i<=N-1;i++) printf("%d %d %d %d\n",maxans[i].F,maxans[i].S,minans[i].F,minans[i].S);
    return 0; 
}
