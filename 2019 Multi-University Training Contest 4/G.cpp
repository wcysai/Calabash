#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,a[17];
bool vis[17];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        int id=-1;
        for(int i=1;i<=16;i++)
        {
            scanf("%d",&a[i]);
            if(!a[i]) id=i;
        }
        while(id%4!=0) swap(a[id],a[id+1]),id++;
        while(id!=16) swap(a[id],a[id+4]),id+=4;
        memset(vis,false,sizeof(vis));
        int cnt=0;
        for(int i=1;i<=16;i++)
        {
            if(!vis[i])
            {
                cnt++;
                int now=i;
                do
                {
                    vis[now]=true;
                    now=a[now];
                }while(!vis[now]);
            }
        }
        if(cnt&1) puts("No"); else puts("Yes");
    }
}
