#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef bitset<100005> bs;
int T,n,c;
int a[MAXN];
bs f,g;
double find_area(int a,int b,int c)
{
    double p=(a+b+c)/2.0;
    return sqrt((double)p*(p-a)*(p-b)*(p-c));
}
void solve(int n,int c)
{
    f.reset();
    for(int i=1;i<=n;i++)
    {
        int x;scanf("%d",&x);
        f.set(x);
    }
    double ans=INF;
    int p=0;
    for(int d=1;d<=c/2;d++)
    {
        while(p<=d||(p<=c&&!f.test(p))) p++;
        if(p>c) break;
        g=f&(f>>d);
        int pos=g._Find_next(p);
        if(pos<=c) ans=min(ans,find_area(p,pos,pos+d));
    }
    if(ans==INF) puts("-1"); else printf("%.15f\n",ans);
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&c);
        solve(n,c);
    }
    return 0;
}
