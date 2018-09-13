#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,w,l,x,y;
int main()
{
    scanf("%d",&w);
    scanf("%d",&n);
    ll s=0;
    for(int i=0;i<n;i++)
    {
        scanf("%d%d",&x,&y);
        s+=1LL*x*y;
    }
    printf("%I64d\n",s/w);
    return 0;
}
