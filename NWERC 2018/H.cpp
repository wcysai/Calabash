#include<bits/stdc++.h>
#define MAXN 500005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,c,b;
int z[MAXN];
int ans[MAXN];
int main()
{
    scanf("%d%d%d",&n,&c,&b);
    for(int i=1;i<=b;i++) scanf("%d",&z[i]);
    for(int i=b;i>1;i--)
    {
        int dif=z[i]-z[i-1];
        int now=z[i]-1;
        while(c>=2&&now>z[i-1])
        {
            ans[now]=1;
            now-=2;
            c-=2;
        }
    }
    int now=z[1]-1;
    while(c>=2&&now>=1)
    {
        ans[now]=1;
        now-=2;
        c-=2;
    }
    assert(c<2);
    if(c==1)
    {
        assert(ans[2]!=1);
        ans[1]=1;
    }
    for(int i=1;i<=n;i++) printf("%d",ans[i]);
    return 0;
}
