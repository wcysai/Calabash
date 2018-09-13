/*************************************************************************
    > File Name: F.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-09-02 17:25:44
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 20000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,a[50],c[50],d[MAXN],mx;
int l[50];
vector<P> good;
vector<int> v;
int main()
{
    scanf("%d",&n);
    bool f=false,flag=true;
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&a[i],&c[i]);a[i]--;mx=max(mx,a[i]);
        if(i>1&&c[i]!=c[i-1]) f=true;
        if(l[c[i]]==0) l[c[i]]=i;
        else if(l[c[i]]!=i-1) flag=false;
        else l[c[i]]=i;
    }
    if(!flag) {puts("0"); return 0;}
    if(!f) {puts("-1"); return 0;}
    int ans=0,tot=0;
    for(int i=1;i<=n;i++)
    {
        int last=0;
        for(int j=1;j<=a[i];j=last+1)
        {
            last=a[i]/(a[i]/j);
            d[++tot]=last;
        }
    }
    sort(d+1,d+tot+1);
    for(int i=1;i<=tot;i++)
    {
        if(d[i]==d[i-1]) continue;
        bool f=true;
        for(int j=2;j<=n;j++)
        {
            if((a[j]/d[i]==a[j-1]/d[i])^(c[j]==c[j-1]))
            {
                f=false;
                break;
            }
        }
        if(f) ans+=d[i]-d[i-1];
    }
    printf("%d\n",ans);
    return 0;
}
