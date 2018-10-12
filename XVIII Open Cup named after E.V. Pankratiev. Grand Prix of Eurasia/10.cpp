#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef long double db;
typedef pair<db,db> P;
int M,N;
db v,t,s,L;
P a[MAXN];
const db eps=1e-8;
int main()
{
    scanf("%d",&M);
    while(M--)
    {
        scanf("%d%Lf",&N,&L);L*=1000;
        for(int i=0;i<N;i++) {scanf("%Lf%Lf",&a[i].F,&a[i].S);  a[i].S/=1000000;}
        sort(a,a+N);
        v=0,t=0,s=0;
        for(int i=N-1;i>=0;i--)
        {
            db needed=L-s;
            db covered=v*a[i].S+a[i].F*a[i].S*a[i].S/2;
            if(covered>=needed)
            {
                db vt=sqrt((2*a[i].F*needed)+v*v);
                t+=(vt-v)/a[i].F;
                s=L;
                break;
            }
            else
            {
                t+=a[i].S;
                s+=covered;
                v+=a[i].F*a[i].S;
            }
        }
        if(s<L) t+=(L-s)/v;
        printf("%.15Lf\n",t);
    }
    return 0;
}
