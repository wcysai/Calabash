#include<bits/stdc++.h>
using namespace std;
int n,m;
char a[35],b[105];
char ans[105];
int main()
{
    scanf("%d%d",&n,&m);
    scanf("%s",a+1);scanf("%s",b+1);
    for(int i=m-n+1;i<=m;i++) ans[i]=a[i-(m-n)];
    for(int i=m-n;i>=1;i--) 
    {
        int x=b[i+n]-ans[i+n];
        if(x<0) x+=26;
        ans[i]=x+'a';
    }
    printf("%s\n",ans+1);
    return 0;
}
