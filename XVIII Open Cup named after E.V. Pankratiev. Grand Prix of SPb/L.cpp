#include <bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll n,x,s;
int main()
{
    scanf("%lld",&n);
    s=0;
    for(int i=0;i<n;i++)
    {
        scanf("%lld",&x);
        s^=x;
    }
    if(s!=0) puts("0");
    else printf("%lld\n",(1LL<<n)-2);
    return 0;
}
