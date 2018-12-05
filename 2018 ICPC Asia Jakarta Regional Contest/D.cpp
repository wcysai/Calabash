#include<bits/stdc++.h>
#define MAXN 505
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int R,C;
char str[MAXN][MAXN];
int main()
{
    scanf("%d%d",&R,&C);
    for(int i=1;i<=R;i++) scanf("%s",str[i]+1);
    if(R==1)
    {
        int cnt=0;
        for(int i=2;i<=C-1;i++) if(str[1][i]=='.') cnt++;
        printf("%d\n",cnt);
        return 0;
    }
    if(C==1)
    {
        int cnt=0;
        for(int i=2;i<=R-1;i++) if(str[i][1]=='.') cnt++;
        printf("%d\n",cnt);
        return 0;
    }
    if(R==2)
    {
        int cnt=0;
        for(int i=2;i<=C-1;i++) if(str[1][i]=='.'&&str[2][i]=='.') cnt++;
        printf("%d\n",cnt);
        return 0;
    }
    else if(C==2)
    {
        int cnt=0;
        for(int i=2;i<=R-1;i++) if(str[i][1]=='.'&&str[i][2]=='.') cnt++;
        printf("%d\n",cnt);
        return 0;
    }
    int cnt=0;
    for(int i=2;i<=R-1;i++)
        for(int j=2;j<=C-1;j++)
            if(str[i][j]=='.') cnt++;
    bool f=false;
    for(int i=2;i<=R-1;i++) if(str[i][1]=='#'||str[i][C]=='#') f=true;
    for(int i=2;i<=C-1;i++) if(str[1][i]=='#'||str[R][i]=='#') f=true;
    if(!f) cnt++;
    printf("%d\n",cnt);
    return 0;
}
