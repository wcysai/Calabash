#include<bits/stdc++.h>
#define MAXN 105
#define INF 10000000000
#define MOD 10000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int h,w,n;
char str[MAXN][MAXN];
void check(int x,int y)
{
    if(x*2-1<=h&&y*2-1<=w)
    {
        for(int i=1;i<=h;i++)
            for(int j=1;j<=w;j++)
                str[i][j]='.';
        for(int i=1;i<=x-1;i++)
        {
            int r=i*2;
            for(int j=1;j<=w;j++) str[r][j]='#';
        }
        for(int i=1;i<=y-1;i++)
        {
            int c=i*2;
            for(int j=1;j<=h;j++) str[j][c]='#';
        }
        for(int i=1;i<=h;i++) printf("%s\n",str[i]+1);
        exit(0);
    }
}
int main()
{
    freopen("kotlin.in","r",stdin);
    freopen("kotlin.out","w",stdout);
    scanf("%d%d%d",&h,&w,&n);
    for(int i=1;i*i<=n;i++)
    {
        if(n%i) continue;
        check(i,n/i);
        if(i*i!=n) check(n/i,i);
    }
    puts("Impossible");
    return 0;
}
