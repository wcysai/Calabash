#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
vector<P> points;
int dx[4]={0,0,-1,1};
int dy[4]={-1,1,0,0};
int dis2(P u,P v)
{
    return (u.F-v.F)*(u.F-v.F)+(u.S-v.S)*(u.S-v.S);
}
void update(int x,P p)
{
    vector<P> newp; newp.clear();
    for(auto q:points) if(dis2(p,q)==x) newp.push_back(q);
    points=newp;
}
void extend()
{
    set<P> s; s.clear();
    for(auto q:points)
    {
        int x=q.F,y=q.S;
        for(int i=0;i<4;i++)
        {
            int nx=x+dx[i],ny=y+dy[i];
            if(nx>=0&&nx<=100&&ny>=0&&ny<=100) s.insert(P(nx,ny));
        }
    }
    points.clear(); for(auto p:s) points.push_back(p);
}
int ask(P p)
{
    printf("Q %d %d\n",p.F,p.S);
    fflush(stdout);
    int x;scanf("%d",&x);
    return x;
}
int getsqrt(int x)
{
    for(int i=1;i*i<=x;i++) if(i*i==x) return i;
    return -1;
}
int main()
{
    int d1=ask(P(0,-1000)),d2=ask(P(0,-1000));
    int dif=d2-d1;
    if(dif>0&&dif>=2001)
    {
        int y=(dif-2001)/2;
        int x=getsqrt(d1-(y+1000)*(y+1000));
        printf("A %d %d\n",x,y); fflush(stdout);
    }
    else if(dif>0)
    {
        int x=(dif-1)/2;
        int y=getsqrt(d1-x*x)-1000;
        printf("A %d %d\n",x,y); fflush(stdout);
    }
    else if(dif<=-1999)
    {
        int y=(-1999-dif)/2;
        int x=getsqrt(d1-(y+1000)*(y+1000));
        printf("A %d %d\n",x,y); fflush(stdout);
    }
    else
    {
        int x=(1-dif)/2;
        int y=getsqrt(d1-x*x)-1000;
        printf("A %d %d\n",x,y); fflush(stdout);
    }
    return 0;
}
