#include<bits/stdc++.h>
#define MAXN 5005
using namespace std;
int n,m;
int sg[MAXN];
bool f[MAXN];
int main()
{
    sg[2]=1;
    for(int i=3;i<=5000;i++)
    {
        memset(f,false,sizeof(f));
        for(int j=0;j<=i/2;j++)
            f[sg[j]^sg[i-2-j]]=true;
        for(int j=0;;j++)
            if(!f[j]) {sg[i]=j; break;}
    }
    scanf("%d",&n);
    while(n--)
    {
        scanf("%d",&m);
        if(!sg[m]) puts("Second"); else puts("First");
    }
    return 0;
}
