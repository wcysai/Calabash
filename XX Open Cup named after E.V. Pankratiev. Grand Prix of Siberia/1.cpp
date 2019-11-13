#include<bits/stdc++.h>
#define MAXN 1005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
int n,m;
char str[MAXN][MAXN];
int ans1,ans2;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++) scanf("%s",str[i]);
    ans1=ans2=0;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {
            if((i+j)&1) ans1+=(str[i][j]=='1'),ans2+=(str[i][j]=='2');
            else ans1+=(str[i][j]=='2'),ans2+=(str[i][j]=='1');
        }
    printf("%d\n",min(ans1,ans2));
    return 0;
}
