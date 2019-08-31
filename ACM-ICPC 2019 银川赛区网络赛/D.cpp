#include<bits/stdc++.h>
#define MAXN 5000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,m;
int main()
{
    scanf("%d",&T);
    for(int tot=1;tot<=T;tot++)
    {
        scanf("%d%d",&n,&m);
        printf("Case #%d: ",tot);
        if(n==1) printf("%.6f ",1.0); else printf("%.6f ",0.5);
        printf("%.6f\n",(0.5+0.5*m)/m);
    }
    return 0;
}
