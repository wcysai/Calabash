#include<bits/stdc++.h>
#define MAXN 10005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<double,double> P;
int N;
double X[MAXN],Y[MAXN];
double sqrt2;
const double PI=acos(-1.0);
const double eps=1e-10;
int sgn(double x,double y)
{
    if(fabs(x-y)<eps) return 0;
    if(x>y) return 1;
    return -1;
}
vector<pair<double,int> > v;
bool check(double x)
{
    v.clear();
    int cnt=0;
    for(int i=1;i<=N;i++)
    {
        double dist=sqrt(X[i]*X[i]+Y[i]*Y[i]);
        if(dist<x) return false;
        if(dist>=sqrt2*x) continue;
        cnt++;
        double ang=atan2(Y[i],X[i]);
        double interval=acos(x/dist);
        double l=PI/4-interval,r=PI/4+interval;
        l+=ang; r+=ang;
        while(l<0) l+=PI/2; while(l>=PI/2) l-=PI/2;
        while(r<0) r+=PI/2; while(r>=PI/2) r-=PI/2;
        if(!sgn(r-l,2*interval))
        {
            v.push_back(make_pair(l,-1));
            v.push_back(make_pair(r,1));
        }
        else
        {
            v.push_back(make_pair(l,-1));
            v.push_back(make_pair(0.0,-1));
            v.push_back(make_pair(r,1));
        }
    }
    if(!cnt) return true;
    sort(v.begin(),v.end());
    int res=0;
    for(auto p:v)
    {
        res-=p.S;
        if(res==cnt) return true;
    }
    return false;
}
int main()
{
    scanf("%d",&N);
    for(int i=1;i<=N;i++) scanf("%lf%lf",&X[i],&Y[i]);
    sqrt2=sqrt(2.0);
    double l=0.0,r=2e9;
    for(int i=0;i<200;i++)
    {
        double mid=(l+r)/2;
        if(check(mid)) l=mid; else r=mid;
    }
    printf("%.4f\n",8*l);
    return 0;
}
