#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
const double PI=acos(-1.0);
int T,a,b,r,d;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d%d",&a,&b,&r,&d);
        double ang=(double)d/180.0*PI;
        //printf("%.12f %.12f\n",ang,atan((double)b/(a+r)));
        if(atan((double)b/(a+r))<ang) {printf("%.12f\n",sqrt((a+r)*(a+r)+b*b)-r);}
        else
        {
            double a2=ang-atan((double)b/(a+r));
            printf("%.12f\n",sqrt((a+r)*(a+r)+b*b)*cos(a2)-r);
        }
    }
    return 0;
}
