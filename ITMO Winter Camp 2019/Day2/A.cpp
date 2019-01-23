#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 105
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
char str[MAXN][MAXN];
int main()
{
    scanf("%d%d",&n,&m);
    int ans=0;
    for(int i=1;i<=n;i++) 
    {
        scanf("%s",str[i]+1);
        bool f=false;
        int len=strlen(str[i]+1);
        for(int j=1;j<=len;j++) if(str[i][j]=='+') f=true;
        if(f) ans++;
    }
    printf("%d\n",ans);
    return 0;
}

