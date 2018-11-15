#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a,b,c,d;
int get(int x,int y)
{
    if(y>x) return INF;
    return x/(x/y);
}
int main()
{
    scanf("%d",&n);
    while(n--)
    {
        scanf("%d%d%d%d",&a,&b,&c,&d);
        a--;c--;
        int last=-1,ans=0;
        for(int i=1;i<=max(b,d);i=last+1)
        {
            last=min(min(get(a,i),get(b,i)),min(get(c,i),get(d,i)));
            if((b/i-a/i>0)&&(d/i-c/i>0)) ans=max(ans,last);
        }
        printf("%d\n",ans);
    }
    return 0;
}
