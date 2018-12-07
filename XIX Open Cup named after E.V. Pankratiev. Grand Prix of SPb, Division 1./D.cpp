#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
#define x1 dsjfiol
#define x2 sdfjkjkl
#define y1 dsajkfo
#define y2 dsoijf
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
bool check(ll x,ll y)
{
    if(x&1) {x-=1; y+=2;}
    y-=x/2;
    if(y%5) return false;
    return true;
}
ll x1,y1,x2,y2;
int main()
{
    scanf("%lld%lld%lld%lld",&x1,&y1,&x2,&y2);
    ll nx1,nx2,ny1,ny2;
    if(check(x1,y1)) {nx1=x1;ny1=y1;}
    if(check(x1-1,y1)) {nx1=x1-1;ny1=y1;}
    if(check(x1+1,y1)) {nx1=x1+1;ny1=y1;}
    if(check(x1,y1-1)) {nx1=x1;ny1=y1-1;}
    if(check(x1,y1+1)) {nx1=x1;ny1=y1+1;}
    if(check(x2,y2)) {nx2=x2;ny2=y2;}
    if(check(x2-1,y2)) {nx2=x2-1;ny2=y2;}
    if(check(x2+1,y2)) {nx2=x2+1;ny2=y2;}
    if(check(x2,y2-1)) {nx2=x2;ny2=y2-1;}
    if(check(x2,y2+1)) {nx2=x2;ny2=y2+1;}
    //printf("%lld %lld %lld %lld\n",nx1,ny1,nx2,ny2);
    ll newx1=(2*nx1+ny1)/5,newy1=(2*ny1-nx1)/5;
    ll newx2=(2*nx2+ny2)/5,newy2=(2*ny2-nx2)/5;
    printf("%lld\n",abs(newx1-newx2)+abs(newy1-newy2));
    return 0;
}
