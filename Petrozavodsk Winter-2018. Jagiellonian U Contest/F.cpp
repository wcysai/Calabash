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
int T,x,y,z,r,a,b,c,d;
const long double PI=acos(-1.0);
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d%d%d%d%d%d",&x,&y,&z,&r,&a,&b,&c,&d);
        printf("%.15Lf\n",PI*r*r);
    }
    return 0;
}

