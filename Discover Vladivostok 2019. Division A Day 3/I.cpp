#include<vector>
#include<list>
#include<map>
#include<set>
#include<deque>
#include<queue>
#include<stack>
#include<bitset>
#include<algorithm>
#include<functional>
#include<numeric>
#include<utility>
#include<iostream>
#include<sstream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<cctype>
#include<string>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<climits>
#include<complex>
#define double long double
#define mp make_pair
#define pb push_back
using namespace std;
const double eps=1e-10;
const double pi=acos(-1.0);
const double inf=1e20;
const int maxp=50005;
int dblcmp(double d)
{
    if (fabs(d)<eps)return 0;
    return d>eps?1:-1;
}
inline double sqr(double x){return x*x;}
struct point
{
    double x,y;
    point(){}
    point(double _x,double _y):
    x(_x),y(_y){};
    void input()
    {
        scanf("%Lf%Lf",&x,&y);
    }
    void output()
    {
        printf("%.2f %.2f\n",x,y);
    }
    bool operator==(point a)const
    {
        return dblcmp(a.x-x)==0&&dblcmp(a.y-y)==0;
    }
    bool operator<(point a)const
    {
        return dblcmp(a.x-x)==0?dblcmp(y-a.y)<0:x<a.x;
    }
    double len()
    {
        return hypot(x,y);
    }
    double len2()
    {
        return x*x+y*y;
    }
    double distance(point p)
    {
        return hypot(x-p.x,y-p.y);
    }
    point add(point p)
    {
        return point(x+p.x,y+p.y);
    }
    point sub(point p)
    {
        return point(x-p.x,y-p.y);
    }
    point mul(double b)
    {
        return point(x*b,y*b);
    }
    point div(double b)
    {
        return point(x/b,y/b);
    }
    double dot(point p)
    {
        return x*p.x+y*p.y;
    }
    double det(point p)
    {
        return x*p.y-y*p.x;
    }
    double rad(point a,point b)
    {
        point p=*this;
        return fabs(atan2(fabs(a.sub(p).det(b.sub(p))),a.sub(p).dot(b.sub(p))));
    }
    point trunc(double r)
    {
        double l=len();
        if (!dblcmp(l))return *this;
        r/=l;
        return point(x*r,y*r);
    }
    point rotleft()
    {
        return point(-y,x);
    }
    point rotright()
    {
        return point(y,-x);
    }
    point rotate(point p,double angle)//з»•з‚№pйЂ†ж—¶й’€ж—‹иЅ¬angleи§’еє¦
    {
        point v=this->sub(p);
        double c=cos(angle),s=sin(angle);
        return point(p.x+v.x*c-v.y*s,p.y+v.x*s+v.y*c);
    }
};

struct line
{
    point a,b;
    line(){}
    line(point _a,point _b)
    {
        a=_a;
        b=_b;
    }
    bool operator==(line v)
    {
        return (a==v.a)&&(b==v.b);
    }
    //еЂѕж–њи§’angle
    line(point p,double angle)
    {
        a=p;
        if (dblcmp(angle-pi/2)==0)
        {
            b=a.add(point(0,1));
        }
        else
        {
            b=a.add(point(1,tan(angle)));
        }
    }
    //ax+by+c=0
    line(double _a,double _b,double _c)
    {
        if (dblcmp(_a)==0)
        {
            a=point(0,-_c/_b);
            b=point(1,-_c/_b);
        }
        else if (dblcmp(_b)==0)
        {
            a=point(-_c/_a,0);
            b=point(-_c/_a,1);
        }
        else
        {
            a=point(0,-_c/_b);
            b=point(1,(-_c-_a)/_b);
        }
    }
    void input()
    {
        a.input();
        b.input();
    }
    void adjust()
    {
        if (b<a)swap(a,b);
    }
    double length()
    {
        return a.distance(b);
    }
    double angle()//з›ґзєїеЂѕж–њи§’ 0<=angle<180
    {
        double k=atan2(b.y-a.y,b.x-a.x);
        if (dblcmp(k)<0)k+=pi;
        if (dblcmp(k-pi)==0)k-=pi;
        return k;
    }
    //з‚№е’Њзєїж®µе…ізі»
    //1 ењЁйЂ†ж—¶й’€
    //2 ењЁйЎєж—¶й’€
    //3 е№іиЎЊ
    int relation(point p)
    {
        int c=dblcmp(p.sub(a).det(b.sub(a)));
        if (c<0)return 1;
        if (c>0)return 2;
        return 3;
    }
    bool pointonseg(point p)
    {
        return dblcmp(p.sub(a).det(b.sub(a)))==0&&dblcmp(p.sub(a).dot(p.sub(b)))<=0;
    }
    bool parallel(line v)
    {
        return dblcmp(b.sub(a).det(v.b.sub(v.a)))==0;
    }
    //2 и§„иЊѓз›ёдє¤
    //1 йќћи§„иЊѓз›ёдє¤
    //0 дёЌз›ёдє¤
    int segcrossseg(line v)
    {
        int d1=dblcmp(b.sub(a).det(v.a.sub(a)));
        int d2=dblcmp(b.sub(a).det(v.b.sub(a)));
        int d3=dblcmp(v.b.sub(v.a).det(a.sub(v.a)));
        int d4=dblcmp(v.b.sub(v.a).det(b.sub(v.a)));
        if ((d1^d2)==-2&&(d3^d4)==-2)return 2;
        return (d1==0&&dblcmp(v.a.sub(a).dot(v.a.sub(b)))<=0||
                d2==0&&dblcmp(v.b.sub(a).dot(v.b.sub(b)))<=0||
                d3==0&&dblcmp(a.sub(v.a).dot(a.sub(v.b)))<=0||
                d4==0&&dblcmp(b.sub(v.a).dot(b.sub(v.b)))<=0);
    }
    int linecrossseg(line v)//*this seg v line
    {
        int d1=dblcmp(b.sub(a).det(v.a.sub(a)));
        int d2=dblcmp(b.sub(a).det(v.b.sub(a)));
        if ((d1^d2)==-2)return 2;
        return (d1==0||d2==0);
    }
    //0 е№іиЎЊ
    //1 й‡Ќеђ€
    //2 з›ёдє¤
    int linecrossline(line v)
    {
        if ((*this).parallel(v))
        {
            return v.relation(a)==3;
        }
        return 2;
    }
    point crosspoint(line v)
    {
        double a1=v.b.sub(v.a).det(a.sub(v.a));
        double a2=v.b.sub(v.a).det(b.sub(v.a));
        return point((a.x*a2-b.x*a1)/(a2-a1),(a.y*a2-b.y*a1)/(a2-a1));
    }
    double dispointtoline(point p)
    {
        return fabs(p.sub(a).det(b.sub(a)))/length();
    }
    double dispointtoseg(point p)
    {
        if (dblcmp(p.sub(b).dot(a.sub(b)))<0||dblcmp(p.sub(a).dot(b.sub(a)))<0)
        {
            return min(p.distance(a),p.distance(b));
        }
        return dispointtoline(p);
    }
    point lineprog(point p)
    {
        return a.add(b.sub(a).mul(b.sub(a).dot(p.sub(a))/b.sub(a).len2()));
    }
    point symmetrypoint(point p)
    {
        point q=lineprog(p);
        return point(2*q.x-p.x,2*q.y-p.y);
    }
};

struct Vector:public point
{
    Vector(){}
    Vector(double a,double b)
    {
        x=a;    y=b;
    }
    Vector(point _a,point _b)   //a->b
    {
        double dx=_b.x-_a.x;
        double dy=_b.y-_a.y;
        x=dx;   y=dy;
    }
    Vector(line v)
    {
        double dx=v.b.x-v.a.x;
        double dy=v.b.y-v.a.y;
        x=dx;   y=dy;
    }
    double length()
    {
        return (sqrt(x*x+y*y));
    }
    Vector Normal()
    {
        double L=sqrt(x*x+y*y);
        Vector Vans=Vector(-y/L,x/L);
        return Vans;
    }
};
bool sorted=false;
Vector operator - (point a, point b) {return Vector(b.x - a.x, b.y - a.y);}
Vector operator + (point a, point b) {return Vector(b.x + a.x, b.y + a.y);}
double operator ^ (Vector a, Vector b) {return a.x * b.y - a.y * b.x;}
struct halfplane:public line    //еЌЉе№ійќў
{
    double angle;
    halfplane(){}
    //иЎЁз¤єеђ‘й‡Џ a->bйЂ†ж—¶й’€(е·¦дѕ§)зљ„еЌЉе№ійќў
    halfplane(point _a,point _b)
    {
        a=_a;
        b=_b;
    }
    halfplane(line v)
    {
        a=v.a;
        b=v.b;
    }
    void calcangle()
    {
        angle=atan2(b.y-a.y,b.x-a.x);
    }
    bool operator<(const halfplane &b)const
    {
        return angle<b.angle;
    }
};
struct halfplanes   //еЌЉе№ійќўдє¤
{
    int n;
    halfplane hp[maxp];
    point p[maxp];
    int que[maxp];
    int st,ed;
    void push(halfplane tmp)
    {
        hp[n++]=tmp;
    }
    void unique()
    {
        int m=1,i;
        for (i=1;i<n;i++)
        {
            if (dblcmp(hp[i].angle-hp[i-1].angle))hp[m++]=hp[i];
            else if (dblcmp(hp[m-1].b.sub(hp[m-1].a).det(hp[i].a.sub(hp[m-1].a))>0))hp[m-1]=hp[i];
        }
        n=m;
    }
    bool halfplaneinsert()
    {
        int i;
        for (i=0;i<n;i++)hp[i].calcangle();
        if(!sorted) sort(hp,hp+n);
        sorted=true;
        unique();
        que[st=0]=0;
        que[ed=1]=1;
        p[1]=hp[0].crosspoint(hp[1]);
        for (i=2;i<n;i++)
        {
            while (st<ed&&dblcmp((hp[i].b.sub(hp[i].a).det(p[ed].sub(hp[i].a))))<0)ed--;
            while (st<ed&&dblcmp((hp[i].b.sub(hp[i].a).det(p[st+1].sub(hp[i].a))))<0)st++;
            que[++ed]=i;
            if (hp[i].parallel(hp[que[ed-1]]))return false;
            p[ed]=hp[i].crosspoint(hp[que[ed-1]]);
        }
        while (st<ed&&dblcmp(hp[que[st]].b.sub(hp[que[st]].a).det(p[ed].sub(hp[que[st]].a)))<0)ed--;
        while (st<ed&&dblcmp(hp[que[ed]].b.sub(hp[que[ed]].a).det(p[st+1].sub(hp[que[ed]].a)))<0)st++;
        if (st+1>=ed)return false;
        return true;
    }
    /*
    void getconvex(polygon &con)
    {
        p[st]=hp[que[st]].crosspoint(hp[que[ed]]);
        con.n=ed-st+1;
        int j=st,i=0;
        for (;j<=ed;i++,j++)
        {
            con.p[i]=p[j];
        }
    }*/
};

point p[50005];
Vector V[50005],Vt[50005];
halfplanes TH;
int n;
int main()
{
    //freopen("in.txt","r",stdin);
    cin >> n; 
        for (int i=0;i<n;i++)   //n points:[0..n-1]
            p[i].input();
    double aans = 0.0;
    for (int F = 0; F < 2; F++) {

        for (int i=0;i<n;i++)   //v[i]:p[i]->p[i+1]
        {
            V[i]=Vector(p[i],p[(i+1)%n]);
            //printf("vector:   %.6lf  %.6lf\n",V[i].x,V[i].y);
            Vt[i]=V[i].Normal();
        }

        double l=0,r=2e7;
        sorted=false;
        while (r-l>1e-6)
        {
            double mid=(l+r)/2;
            //double mid=l+(r-l)/2;
            TH.n=0;
            //halfplanes TH;
            
            for (int i=0;i<n;i++)
            {
                point t1=p[i].add(Vt[i].mul(mid));
                point t2=t1.add(V[i]);

                line tmp=line(t1,t2);
                TH.push(halfplane(tmp));
            }

            //printf("%.6lf  %d",mid,TH.n);

            if (TH.halfplaneinsert())
            {
                //cout<<"OK"<<endl;
                l=mid;      //l=mid+0.00001;
            }
            else
            {
                //cout<<"NO"<<endl;
                r=mid;      //r=mid-0.00001;
            }
        }
        reverse(p, p + n);
        aans = max(aans, l);
    }
    printf("%.12Lf\n", aans);
    return 0;
}
