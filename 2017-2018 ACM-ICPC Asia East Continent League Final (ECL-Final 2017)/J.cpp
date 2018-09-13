//
// Created by calabash_boy on 18-5-24.
//
#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,n;
int a[MAXN],d[MAXN];
int main()
{
    scanf("%d",&t);
    int kase=0;
    while(t--)
    {
        kase++;
        scanf("%d",&n);
        int s=0;
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        a[n+1]=0;
        a[0]=0;
        for(int i=1;i<=n+1;i++)
            d[i]=a[i]-a[i-1];
        int lb=1,rb=1;
        while(d[rb]>=0) rb++;
        while(d[lb]<=0) lb++;
        bool f=true;
        while(rb<=n+1)
        {
            if(rb-lb<3) {f=false;break;}
            int x=min(d[lb],-d[rb]);
            d[lb]-=x;d[rb]+=x;
            while(d[rb]>=0&&rb<=n+1) rb++;
            while(d[lb]<=0&&lb<=n+1) lb++;
        }
        if(f) printf("Case #%d: Yes\n",kase); else printf("Case #%d: No\n",kase);
    }
    return 0;
}
