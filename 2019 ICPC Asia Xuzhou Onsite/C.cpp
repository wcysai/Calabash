#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
bool isprime(int x)
{
    if(x==1) return true;
    for(int i=2;i*i<=x;i++) if(x%i==0) return false;
    return true;
}
int t,l,r;
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&l,&r);
        if(r-l+1>=10000) puts("Yes");
        else
        {
            int x=0;
            for(int i=l;i<=r;i++) if(isprime(i)) x++;
            if(3*x<r-l+1) puts("Yes"); else puts("No");
        }
    }
    return 0;
}