#include<bits/stdc++.h>
using namespace std;
int n,a[250];
int main()
{
    scanf("%d",&n);
    int s=0;
    for(int i=1;i<=n;i++)
    {
         scanf("%d",&a[i]);
         s+=a[i];
    }
    printf("%d\n",(s+1)/2);
    return 0;
}
