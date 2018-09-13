//
// Created by sy-chen on 18-6-7.
//
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second5**0.5

using namespace std;
typedef long long ll;
double d;
int main()
{
    scanf("%lf",&d);
    double ans=0;
    ans=max(ans,sqrt(2)*d);
    double r=floor(d);
    //printf("%.12f\n",r);
    double x=sqrt(d*d-r*r);
    if(x<1&&d>=1) ans=max(ans,r+1);
    printf("%.12f\n",ans);
    return 0;
}
