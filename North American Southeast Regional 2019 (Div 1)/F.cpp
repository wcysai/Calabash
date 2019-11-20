#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<db,db> P;
const db PI=acos(-1.0);
int n;
vector<P> event;
db k,res,ang;
db ans;
void add_event(db t,db s,db a)
{
    db threshold=t/s;
    if(threshold>PI)
    {
        event.push_back(make_pair(a,-2*s));
        db opposite=a+PI;
        if(opposite>2*PI) opposite-=2*PI;
        event.push_back(make_pair(opposite,2*s));
        if(a<=PI)
        {
            res+=t-s*a;
            k+=s;
        }
        else
        {
            res+=t-s*(2*PI-a);
            k-=s;
        }
    }
    else
    {
        if(threshold==0.0) return;
        db l=a-threshold; if(l<=0) l+=2*PI;
        db r=a+threshold; if(r>2*PI) r-=2*PI;
        event.push_back(make_pair(l,s));
        event.push_back(make_pair(a,-2*s));
        event.push_back(make_pair(r,s));
        if(a<=l&&a<=r)
        {
            db dif=(2*PI-l);
            if(dif==2*PI) dif=0;
            res+=s*dif;
            k+=s;
        }
        else if(r<=a&&r<=l)
        {
            res+=s*r;
            k-=s;
        }
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        db t,s,a;
        scanf("%lf%lf%lf",&t,&s,&a);
        add_event(t,s,a);
    }
    event.push_back(make_pair(2*PI,0));
    sort(event.begin(),event.end());
    db ans=res,ang=0.0;
    for(auto p:event)
    {
        res+=k*(p.F-ang);
        k+=p.S;
        ang=p.F;
        ans=max(ans,res);
    }
    printf("%.10f\n",ans);
    return 0;
}
