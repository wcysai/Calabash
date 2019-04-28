#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef long double db;
const db eps=1e-6;
db a,b,c,d;
db Heron(db a,db b,db c)
{
    db p=(a+b+c)/2;
    return sqrt(p*(p-a)*(p-b)*(p-c));
}
int main()
{
    scanf("%Lf%Lf%Lf%Lf",&a,&b,&c,&d);
    db ans=0;
    db l=max(max(b-a,a-b),max(d-c,c-d)),r=min(a+b,c+d);
    for(int i=0;i<200;i++)
    {
        db lb=l+(r-l)/3,rb=l+(r-l)/3*2.0;
        if(Heron(a,b,lb)+Heron(c,d,lb)<Heron(a,b,rb)+Heron(c,d,rb)) l=lb; else r=rb;
    }
    ans=max(ans,Heron(a,b,l)+Heron(c,d,l));
    l=max(max(c-a,a-c),max(d-b,b-d)),r=min(a+c,b+d);
    for(int i=0;i<200;i++)
    {
        db lb=l+(r-l)/3,rb=l+(r-l)/3*2.0;
        if(Heron(a,c,lb)+Heron(b,d,lb)<Heron(a,c,rb)+Heron(b,d,rb)) l=lb; else r=rb;
    }
    ans=max(ans,Heron(a,c,l)+Heron(b,d,l));
    printf("%.15Lf\n",ans);
    return 0;
}

