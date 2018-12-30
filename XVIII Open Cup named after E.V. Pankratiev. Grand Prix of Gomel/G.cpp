/*************************************************************************
    > File Name: G.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-12-25 23:59:40
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
const double PI = acos(-1.0);
const double eps = 1e-10;

/****************常用函数***************/
//判断ta与tb的大小关系
int sgn( double ta, double tb)
{
    if(fabs(ta-tb)<eps)return 0;
    if(ta<tb)   return -1;
    return 1;
}

//点
class Point
{
public:

    double x, y;

    Point(){}
    Point( double tx, double ty){ x = tx, y = ty;}

    bool operator < (const Point &_se) const
    {
        return x<_se.x || (x==_se.x && y<_se.y);
    }
    friend Point operator + (const Point &_st,const Point &_se)
    {
        return Point(_st.x + _se.x, _st.y + _se.y);
    }
    friend Point operator - (const Point &_st,const Point &_se)
    {
        return Point(_st.x - _se.x, _st.y - _se.y);
    }
    double operator ^(const Point &b)const
    {
        return x*b.y - y*b.x;
    }
    //点位置相同(double类型)
    bool operator == (const Point &_off)const
    {
        return  sgn(x, _off.x) == 0 && sgn(y, _off.y) == 0;
    }

};

/****************常用函数***************/
//点乘
double dot(const Point &po,const Point &ps,const Point &pe)
{
    return (ps.x - po.x) * (pe.x - po.x) + (ps.y - po.y) * (pe.y - po.y);
}
//叉乘
double xmult(const Point &po,const Point &ps,const Point &pe)
{
    return (ps.x - po.x) * (pe.y - po.y) - (pe.x - po.x) * (ps.y - po.y);
}
//两点间距离的平方
double getdis2(const Point &st,const Point &se)
{
    return (st.x - se.x) * (st.x - se.x) + (st.y - se.y) * (st.y - se.y);
}
//两点间距离
double getdis(const Point &st,const Point &se)
{
    return sqrt((st.x - se.x) * (st.x - se.x) + (st.y - se.y) * (st.y - se.y));
}

//两点表示的向量
class Line
{
public:

    Point s, e;//两点表示，起点[s]，终点[e]
    double a, b, c;//一般式,ax+by+c=0
    double angle;//向量的角度，[-pi,pi]

    Line(){}
    Line( Point ts, Point te):s(ts),e(te){}//get_angle();}
    Line(double _a,double _b,double _c):a(_a),b(_b),c(_c){}

    //排序用
    bool operator < (const Line &ta)const
    {
        if(angle!=ta.angle) return angle<ta.angle;
        return ((s - ta.s)^(ta.e - ta.s)) < 0;
    }
    //向量与向量的叉乘
    friend double operator / ( const Line &_st, const  Line &_se)
    {
        return (_st.e.x - _st.s.x) * (_se.e.y - _se.s.y) - (_st.e.y - _st.s.y) * (_se.e.x - _se.s.x);
    }
    //向量间的点乘
    friend double operator *( const Line &_st, const  Line &_se)
    {
        return (_st.e.x - _st.s.x) * (_se.e.x - _se.s.x) - (_st.e.y - _st.s.y) * (_se.e.y - _se.s.y);
    }
    //从两点表示转换为一般表示
    //a=y2-y1,b=x1-x2,c=x2*y1-x1*y2
    bool pton()
    {
        a = e.y - s.y;
        b = s.x - e.x;
        c = e.x * s.y - e.y * s.x;
        return true;
    }
    //半平面交用
    //点在向量左边（右边的小于号改成大于号即可,在对应直线上则加上=号）
    friend bool operator < (const Point &_Off, const Line &_Ori)
    {
        return (_Ori.e.y - _Ori.s.y) * (_Off.x - _Ori.s.x)
            < (_Off.y - _Ori.s.y) * (_Ori.e.x - _Ori.s.x);
    }
    //求直线或向量的角度
    double get_angle( bool isVector = true)
    {
        angle = atan2( e.y - s.y, e.x - s.x);
        if(!isVector && angle < 0)
            angle += PI;
        printf("%.10lf\n",angle);
        return angle;
    }

    //点在线段或直线上 1:点在直线上 2点在s,e所在矩形内
    bool has(const Point &_Off, bool isSegment = false) const
    {
        bool ff = sgn( xmult( s, e, _Off), 0) == 0;
        if( !isSegment) return ff;
        return ff
            && sgn(_Off.x - min(s.x, e.x), 0) >= 0 && sgn(_Off.x - max(s.x, e.x), 0) <= 0
            && sgn(_Off.y - min(s.y, e.y), 0) >= 0 && sgn(_Off.y - max(s.y, e.y), 0) <= 0;
    }

    //点到直线/线段的距离
    double dis(const Point &_Off, bool isSegment = false)
    {
        ///化为一般式
        pton();
        //到直线垂足的距离
        double td = (a * _Off.x + b * _Off.y + c) / sqrt(a * a + b * b);
        //如果是线段判断垂足
        if(isSegment)
        {
            double xp = (b * b * _Off.x - a * b * _Off.y - a * c) / ( a * a + b * b);
            double yp = (-a * b * _Off.x + a * a * _Off.y - b * c) / (a * a + b * b);
            double xb = max(s.x, e.x);
            double yb = max(s.y, e.y);
            double xs = s.x + e.x - xb;
            double ys = s.y + e.y - yb;
           if(xp > xb + eps || xp < xs - eps || yp > yb + eps || yp < ys - eps)
                td = min( getdis(_Off,s), getdis(_Off,e));
        }
        return fabs(td);
    }

    //关于直线对称的点
    Point mirror(const Point &_Off)
    {
        ///注意先转为一般式
        Point ret;
        double d = a * a + b * b;
        ret.x = (b * b * _Off.x - a * a * _Off.x - 2 * a * b * _Off.y - 2 * a * c) / d;
        ret.y = (a * a * _Off.y - b * b * _Off.y - 2 * a * b * _Off.x - 2 * b * c) / d;
        return ret;
    }
    //计算两点的中垂线
    static Line ppline(const Point &_a,const Point &_b)
    {
        Line ret;
        ret.s.x = (_a.x + _b.x) / 2;
        ret.s.y = (_a.y + _b.y) / 2;
        //一般式
        ret.a = _b.x - _a.x;
        ret.b = _b.y - _a.y;
        ret.c = (_a.y - _b.y) * ret.s.y + (_a.x - _b.x) * ret.s.x;
        //两点式
        if(fabs(ret.a) > eps)
        {
            ret.e.y = 0.0;
            ret.e.x = - ret.c / ret.a;
            if(ret.e == ret. s)
            {
                ret.e.y = 1e10;
                ret.e.x = - (ret.c - ret.b * ret.e.y) / ret.a;
            }
        }
        else
        {
            ret.e.x = 0.0;
            ret.e.y = - ret.c / ret.b;
            if(ret.e == ret. s)
            {
                ret.e.x = 1e10;
                ret.e.y = - (ret.c - ret.a * ret.e.x) / ret.b;
            }
        }
        return ret;
    }

    //------------直线和直线（向量）-------------
    //向量向左边平移t的距离
    Line& moveLine( double t)
    {
        Point of;
        of = Point( -( e.y - s.y), e.x - s.x);
        double dis = sqrt( of.x * of.x + of.y * of.y);
        of.x= of.x * t / dis, of.y = of.y * t / dis;
        s = s + of, e = e + of;
        return *this;
    }
    //直线重合
    static bool equal(const Line &_st,const Line &_se)
    {
        return _st.has( _se.e) && _se.has( _st.s);
    }
    //直线平行
    static bool parallel(const Line &_st,const Line &_se)
    {
        return sgn( _st / _se, 0) == 0;
    }
    //两直线（线段）交点
    //返回-1代表平行，0代表重合，1代表相交
    static bool crossLPt(const Line &_st,const Line &_se, Point &ret)
    {
        if(parallel(_st,_se))
        {
            if(Line::equal(_st,_se)) return 0;
            return -1;
        }
        ret = _st.s;
        double t = ( Line(_st.s,_se.s) / _se) / ( _st / _se);
        ret.x += (_st.e.x - _st.s.x) * t;
        ret.y += (_st.e.y - _st.s.y) * t;
        return 1;
    }
    //------------线段和直线（向量）----------
    //直线和线段相交
    //参数：直线[_st],线段[_se]
    friend bool crossSL( Line &_st, Line &_se)
    {
        return sgn( xmult( _st.s, _se.s, _st.e) * xmult( _st.s, _st.e, _se.e), 0) >= 0;
    }

    //判断线段是否相交(注意添加eps)
    static bool isCrossSS( const Line &_st, const  Line &_se)
    {
        //1.快速排斥试验判断以两条线段为对角线的两个矩形是否相交
        //2.跨立试验（等于0时端点重合）
        return
            max(_st.s.x, _st.e.x) >= min(_se.s.x, _se.e.x) &&
            max(_se.s.x, _se.e.x) >= min(_st.s.x, _st.e.x) &&
            max(_st.s.y, _st.e.y) >= min(_se.s.y, _se.e.y) &&
            max(_se.s.y, _se.e.y) >= min(_st.s.y, _st.e.y) &&
            sgn( xmult( _se.s, _st.s, _se.e) * xmult( _se.s, _se.e, _st.s), 0) >= 0 &&
            sgn( xmult( _st.s, _se.s, _st.e) * xmult( _st.s, _st.e, _se.s), 0) >= 0;
    }
};

//寻找凸包的graham 扫描法所需的排序函数
Point gsort;
bool gcmp( const Point &ta, const Point &tb)/// 选取与最后一条确定边夹角最小的点，即余弦值最大者
{
    double tmp = xmult( gsort, ta, tb);
    if( fabs( tmp) < eps)
        return getdis( gsort, ta) < getdis( gsort, tb);
    else if( tmp > 0)
        return 1;
    return 0;
}

class Polygon
{
public:
    const static int maxpn = 5e4+7;
    Point pt[maxpn];//点（顺时针或逆时针）
    Line dq[maxpn]; //求半平面交打开注释
    int n;//点的个数


    //-----------半平面交-------------
    //复杂度:O(nlog2(n))
    //获取半平面交的多边形（多边形的核）
    //参数：向量集合[l]，向量数量[ln];(半平面方向在向量左边）
    //函数运行后如果n[即返回多边形的点数量]为0则不存在半平面交的多边形（不存在区域或区域面积无穷大）
    int judege( Line &_lx, Line &_ly, Line &_lz)
    {
        Point tmp;
        Line::crossLPt(_lx,_ly,tmp);
        return sgn(xmult(_lz.s,tmp,_lz.e),0);
    }
    int halfPanelCross(Line L[], int ln)
    {
        int i, tn, bot, top;
        for(int i = 0; i < ln; i++)
            L[i].get_angle();
        //sort(L, L + ln);
        //平面在向量左边的筛选
        for(i = tn = 1; i < ln; i ++)
            if(fabs(L[i].angle - L[i - 1].angle) > eps)
                L[tn ++] = L[i];
        ln = tn, n = 0, bot = 0, top = 1;
        dq[0] = L[0], dq[1] = L[1];
        for(i = 2; i < ln; i ++)
        {
            while(bot < top &&  judege(dq[top],dq[top-1],L[i]) > 0)
                top --;
            while(bot < top &&  judege(dq[bot],dq[bot+1],L[i]) > 0)
                bot ++;
            dq[++ top] = L[i];
        }
        while(bot < top && judege(dq[top],dq[top-1],dq[bot]) > 0)
            top --;
        while(bot < top && judege(dq[bot],dq[bot+1],dq[top]) > 0)
            bot ++;
        dq[++top] = dq[bot];
        for(i = bot; i < top; i ++)
            Line::crossLPt(dq[i],dq[i + 1],pt[n++]);
        return n;
    }
};
int n,num,tot=0;
Line a[2*MAXN];
int l[MAXN],r[MAXN];
Polygon P;
int findlen(int pt1,int pt2,int d)
{
    int prev1=(pt1+1)%num,prev2=(pt2-1+num)%num;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",&l[i],&r[i]);
    for(int i=n;i>=1;i--)
    {
        if(i==1)
        {
            a[tot].s=Point(0,l[i]);
            a[tot++].e=Point(1,l[i]);
        }
        else
        {
            a[tot].s=Point(0,l[i]);
            a[tot++].e=Point((double)l[i]/(i-1),0);
        }
    }
    for(int i=n;i>=1;i--)
    {
        if(i==1)
        {
            a[tot].s=Point(1,r[i]);
            a[tot++].e=Point(0,r[i]);
        }
        else
        {
            a[tot].s=Point((double)r[i]/(i-1),0);
            a[tot++].e=Point(0,r[i]);
        }
    }
    num=P.halfPanelCross(a,tot);
    if(num<3)
    {
        puts("0");
        return 0;
    }
    for(int i=0;i<num;i++)
    {
        printf("%.10lf %.10lf\n",P.pt[i].x,P.pt[i].y);
    }
    int leftmost=-1;
    double curx=INF;
    for(int i=0;i<num;i++)
    {
        if(P.pt[i].x<curx)
        {
            curx=P.pt[i].x;
            leftmost=i;
        }
    }
    int pt1=(leftmost-1+num)%num,pt2=(leftmost+1)%num,lastd=ceil(curx);
    long long ans=0;
    while(pt1!=pt2)
    {
        int nowd=round(min(P.pt[pt1].x,P.pt[pt2].x));
        int ub,lb;
    }
    
    return 0;
}

