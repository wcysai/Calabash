/*************************************************************************
    > File Name: K.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-06-15 21:18:05
 ************************************************************************/

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
int b,n,e,m,sb,sn,se,c[MAXN];
struct node
{
    int speed;
    int cb,cn,ce;
}a[6];
bool cmp(node x,node y)
{
    return x.speed>y.speed;
}
bool C(int x)
{
    int tb=b,tn=n,te=e;
    for(int i=0;i<m;i++)
    {
        bool f=false;
        for(int j=5;j>=0;j--)
        {
            if(a[j].speed*c[i]>=x&&tb>=a[j].cb&&tn>=a[j].cn&&te>=a[j].ce)
            {
                f=true;
                tb-=a[j].cb;
                tn-=a[j].cn;
                te-=a[j].ce;
                break;
            }
        }
        if(!f) return false;
    }
    return true;
}
int main()
{
    scanf("%d%d%d",&b,&n,&e);
    scanf("%d%d%d",&sb,&sn,&se);
    a[0].speed=2*sb;a[0].cn=a[0].ce=0;a[0].cb=2;
    a[1].speed=sb+sn;a[1].cb=a[1].cn=1;a[0].ce=0;
    a[2].speed=2*sn;a[2].cb=a[2].ce=0;a[2].cn=2;
    a[3].speed=sb+se;a[3].ce=a[3].cb=1;a[3].cn=0;
    a[4].speed=sn+se;a[4].ce=a[4].cn=1;a[4].cb=0;
    a[5].speed=2*se;a[5].ce=2;a[5].cb=a[5].cn=0;
    sort(a,a+6,cmp);
    m=(b+n+e)/2;
    for(int i=0;i<m;i++)
        scanf("%d",&c[i]);
    sort(c,c+m);
    int l=c[0]*a[5].speed,r=c[m-1]*a[0].speed+1;
    while(r-l>1)
    {
        int mid=(l+r)/2;
        if(C(mid)) l=mid; else r=mid;
    }
    printf("%d\n",l);
    return 0;
}
