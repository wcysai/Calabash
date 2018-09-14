#include<bits/stdc++.h>
#define MAXN 15
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
double EPS= 1e-10;
double add(double a,double b)
{
    if(abs(a+b)<EPS*(abs(a)+abs(b))) return 0;
    return a+b;
}
struct P
{
    double x,y;
    P(){}
    P(double x,double y):x(x),y(y){}
    P operator +(P p)
    {
        return P(add(x,p.x),add(y,p.y));
    }
    P operator -(P p)
    {
        return P(add(x,p.x),add(y,-p.y));
    }
    P operator *(double d)
    {
        return P(x*d,y*d);
    }
    double dot(P p)
    {
        return add(x*p.x,y*p.y);
    }
    double det(P p)
    {
        return add(x*p.y,-y*p.x);
    }
};
int r,b;
P p[MAXN],q[MAXN];
int perm[MAXN];
bool on_seg(P p1,P p2, P q)
{
	return (p1-q).det(p2-q)==0&&(p1-q).dot(p2-q)<=0;
}
P intersection(P p1,P p2,P q1,P q2)
{
	return p1+(p2-p1)*((q2-q1).det(q1-p1)/(q2-q1).det(p2-p1));
}
int main()
{
	scanf("%d%d",&r,&b);
	for(int i=0;i<r;i++)
		scanf("%lf%lf",&p[i].x,&p[i].y);
	for(int i=0;i<b;i++)
		scanf("%lf%lf",&q[i].x,&q[i].y);
	if(r!=b) {puts("No"); return 0;}
	for(int i=0;i<r;i++) perm[i]=i;
	do
	{
		bool flag=true,f;
		for(int i=0;i<r;i++)
		{
			if(!flag) break;
			for(int j=i+1;j<r;j++)
			{
				if((p[i]-q[perm[i]]).det(p[j]-q[perm[j]])==0)
				{
					f=on_seg(p[i],q[perm[j]],p[j])||on_seg(p[i],q[perm[i]],q[perm[j]])||on_seg(p[j],q[perm[j]],p[i])||on_seg(p[j],q[perm[j]],q[perm[i]]);
				}
				else
				{
					P t=intersection(p[i],q[perm[i]],p[j],q[perm[j]]);
					f=on_seg(p[i],q[perm[i]],t)&&on_seg(p[j],q[perm[j]],t);
				}
				if(f) {flag=false; break;}
			}
		}
		if(flag) {puts("Yes"); return 0;}
	}while(next_permutation(perm,perm+r));
	puts("No");
	return 0;
}
