#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
using namespace std;
int n,p;
int main()
{
    scanf("%d%d",&n,&p);
    int cnt=0,tmp=p;
    while(tmp)
    {
        cnt++;
        tmp/=10;
    }
    if(cnt>n) puts("T_T"); else
    {
        printf("%d",p);
        for(int i=0;i<n-cnt;i++) printf("0");
        puts("");
    }
    return 0;
}
