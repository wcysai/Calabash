#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
const double eps=1e-10;
int cmp(double x)
{
    if(fabs(x)<eps) return 0;
    if(x>0) return 1;
    return -1;
}
inline double sqr(double x)
{
    return x*x;
}
struct point
{
    double x,y;
    point(){}
    point(double a,double b):x(a),y(b){}
    void input()
    {
        scanf("%lf%lf",&x,&y);
    }
    friend point operator + (const point &a,const point &b)
    {
        return point(a.x+b.x,a.y+b.y);
    }
    friend point operator - (const point &a,const point &b)
    {
        return point(a.x-b.x,a.y-b.y);
    }
    double dist()
    {
        return sqrt(sqr(x)+sqr(y));
    }
};

void circle_center(point p0,point p1,point p2,point &cp)
{
    double a1=p1.x-p0.x,b1=p1.y-p0.y,c1=(a1*a1+b1*b1)/2;
    double a2=p2.x-p0.x,b2=p2.y-p0.y,c2=(a2*a2+b2*b2)/2;
    double d=a1*b2-a2*b1;
    cp.x=p0.x+(c1*b2-c2*b1)/d;
    cp.y=p0.y+(a1*c2-a2*c1)/d;
}
void circle_center(point p0,point p1,point &cp)
{
    cp.x=(p0.x+p1.x)/2;
    cp.y=(p0.y+p1.y)/2;
}

point center;
double radius;

bool point_in(const point &p)
{
    return cmp((p-center).dist()-radius)<0;
}

void min_circle_cover(point a[],int n)
{
    radius=0;
    center=a[0];
    for(int i=1;i<n;i++)
    {
        if(!point_in(a[i]))
        {
            center=a[i];radius=0;
            for(int j=0;j<i;j++)
                if(!point_in(a[j]))
                {
                    circle_center(a[i],a[j],center);
                    radius=(a[j]-center).dist();
                    for(int k=0;k<j;k++)
                    {
                        if(!point_in(a[k]))
                        {
                            circle_center(a[i],a[j],a[k],center);
                            radius=(a[k]-center).dist();
                        }
                    }
                }
        }
    }
}
int n;
point a[MAXN];
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++) a[i].input();
    random_shuffle(a,a+n);
    min_circle_cover(a,n);
    printf("%.15f %.15f\n",center.x,center.y);
    printf("%.15f\n",radius);
    return 0;
}
