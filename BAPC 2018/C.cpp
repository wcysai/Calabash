#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
int V;
int main()
{
    scanf("%d",&V);
    int ans=INF;
    for(int i=1;i<=V;i++)
    {
        if(V%i) continue;
        int S=V/i;
        int t=sqrt(S)+1;
        for(int j=t;j>=1;j--)
        {
            if(S%j) continue;
            ans=min(ans,2*i*j+2*j*(S/j)+2*i*(S/j));
        }
    }
    printf("%d\n",ans);
    return 0;
}
