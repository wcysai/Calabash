#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
int n;
int s[MAXN];
int sg[MAXN],mex[MAXN];
int main()
{
/*    sg[0]=0;
    for(int i=1;i<=100;i++)
    {
        for(int j=0;j<i;j++) mex[sg[j]]=i;
        for(int j=1;j<i;j++)
            for(int k=j;k<i&&k<=i-j-k;k++)
                if(sg[j]^sg[k]^sg[i-j-k]<=100000) mex[sg[j]^sg[k]^sg[i-j-k]]=i;
        for(int j=0;;j++) if(mex[j]!=i) {sg[i]=j; break;}
        printf("%d %d\n",i,sg[i]);
    }
*/
    scanf("%d",&n);
    int maxi=0,x=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&s[i]);
        int g;
        if(s[i]%8==7) g=s[i]+1; else if(s[i]%8==0) g=s[i]-1; else g=s[i];
        x^=g;
    }
    if(!x) puts("Second"); else puts("First");
    return 0;
}
