#include<bits/stdc++.h>
#define MAXN 2000005
using namespace std;
int n,t,a[MAXN];
int main()
{
    scanf("%d%d",&n,&t);
    for(int i=1;i<=(1<<n);i++) scanf("%d",&a[i]);
    if(t%2==0) for(int i=1;i<=(1<<n);i++) printf("%d%c",a[i],i==(1<<n)?'\n':' ');
    else for(int i=(1<<n);i>=1;i--) printf("%d%c",a[i],i==1?'\n':' ');
    return 0;
}
