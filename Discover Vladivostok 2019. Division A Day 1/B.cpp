#include<bits/stdc++.h>
#define MAXN 2505
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef long double db;
const db PI=acos(-1.0);
const db eps=1e-10;

int sgn(db ta,db tb)
{
    if(abs(ta-tb)<eps) return 0;
    if(ta<tb) return -1;
    return 1;
}

class Point
{
public:
    db x,y;
    Point(){}
    Point(db tx,db ty) {x=tx, y=ty;}
    bool operator < (const Point &_se) const
    {
        if(sgn(atan2(y,x),atan2(_se.y,_se.x))!=0) return atan2(y,x)<atan2(_se.y,_se.x);
        return atan2(y,x)>=0?(x<_se.x||(x==_se.x&&y<_se.y)):(x>_se.x||(x==_se.x&&y>_se.y));
    }
    friend Point operator + (const Point &_st,const Point &_se)
    {
        return Point(_st.x+_se.x, _st.y+_se.y);
    }
    friend Point operator - (const Point &_st,const Point &_se)
    {
        return Point(_st.x - _se.x, _st.y-_se.y);
    }
    db operator ^(const Point &b)const
    {
        return x*b.y - y*b.x;
    }
    bool operator == (const Point &_off)const
    {
        return  sgn(x, _off.x)== 0 && sgn(y, _off.y) == 0;
    }
};
db xmult(const Point &po,const Point &ps,const Point &pe)
{
    return (ps.x-po.x)*(pe.y-po.y)-(pe.x-po.x)*(ps.y-po.y);
}
db getdis(const Point &st,const Point &se)
{
    return sqrt((st.x-se.x)*(st.x-se.x)+(st.y-se.y)*(st.y-se.y));
}
Point center;
int n;
Point p[MAXN];
db dp[MAXN][MAXN];
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%Lf%Lf",&p[i].x,&p[i].y);
    for(int i=0;i<n;i++) center.x+=p[i].x,center.y+=p[i].y;
    center.x/=n; center.y/=n;
    for(int i=0;i<n;i++) p[i]=p[i]-center;
    sort(p,p+n);
    for(int i=0;i<n-1;i++) dp[i][i+1]=dp[i+1][i]=getdis(p[i],p[i+1]);
    for(int len=3;len<=n;len++)
        for(int i=0;i+len-1<n;i++)
        {
            int j=i+len-1;
            dp[i][j]=min(dp[i+1][j]+getdis(p[i],p[i+1]),dp[j][i+1]+getdis(p[j],p[i]));
            dp[j][i]=min(dp[j-1][i]+getdis(p[j],p[j-1]),dp[i][j-1]+getdis(p[j],p[i]));
        }
    db ans=min(getdis(p[n-1],p[n-2])+dp[n-2][0],getdis(p[n-1],p[0])+dp[0][n-2]);
    for(int i=0;i<n-2;i++) ans=min(ans,getdis(p[0],p[n-1])+getdis(p[n-2],p[n-1])+dp[0][i]+dp[n-2][i+1]);
    for(int i=2;i<n-2;i++) ans=min(ans,getdis(p[0],p[n-1])+getdis(p[n-1],p[i])+dp[0][i-1]+dp[i][n-2]);
    for(int i=1;i<n-3;i++) ans=min(ans,getdis(p[n-1],p[n-2])+getdis(p[n-1],p[i])+dp[i][0]+dp[n-2][i+1]);
    for(int i=0;i<n-2;i++) ans=min(ans,getdis(p[n-1],p[i])+getdis(p[n-1],p[i+1])+dp[i][0]+dp[i+1][n-2]);
    printf("%.20Lf\n",ans);
    return 0;
}
