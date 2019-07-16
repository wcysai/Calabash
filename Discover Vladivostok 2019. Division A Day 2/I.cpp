#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k;
double p;
int main()
{
    freopen("stat.in","r",stdin);
    freopen("stat.out","w",stdout);
    scanf("%d%d%lf",&n,&k,&p);
    double prob=pow((1-p)/(2-p),k);
    printf("%.20lf\n",(1.0-prob)*(n-1)+1);
    return 0;
}
