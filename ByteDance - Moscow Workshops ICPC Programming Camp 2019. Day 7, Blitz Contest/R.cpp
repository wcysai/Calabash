#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAXN 2000005
#define INF 1000000001
#define MOD 998244353
using namespace std;
int V,E,F;
int p,q;
int sum[MAXN];
set<pair<int, int>> ss = {
        {4,4},{6,8},{8,6},{12,20},{20,12}
};


int main()
{
    while(scanf("%d%d",&p,&q)==2)
    {
        if(!p&&!q) break;
        bool f=true;
        int s=4*p;
        int d=2*(p+q)-p*q;
        if(d<=0||s%d!=0)
        {
            f=false;
            puts("-1 -1 -1");
            continue;
        }
        V=s/d;
        if(q%2==1&&V%2==1) f=false;
        else E=q*V/2;
        F=E-V+2;
        if(f&&ss.count(make_pair(V,F)))
        {
            printf("%d %d %d\n",V,E,F);
        }
        else puts("-1 -1 -1");
    }
    return 0;
}
