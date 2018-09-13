//
// Created by calabash_boy on 18-5-24.
//
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
int t,n,a[5];
int main()
{
    scanf("%d",&t);
    int kase=0;
    while(t--)
    {
        kase++;
        for(int i=0;i<5;i++) scanf("%d",&a[i]);
        scanf("%d",&n);
        int s=0,x;
        for(int i=0;i<n;i++)
        {
            scanf("%d",&x);
            if(x>=1&&x<=48) s+=a[0];
            else if(x>=49&&x<=56) s+=a[1];
            else if(x>=57&&x<=60) s+=a[2];
            else if(x>=61&&x<=62) s+=a[3];
            else s+=a[4];
        }
        printf("Case #%d: %I64d\n",kase,10000LL*s);
    }
    return 0;
}
