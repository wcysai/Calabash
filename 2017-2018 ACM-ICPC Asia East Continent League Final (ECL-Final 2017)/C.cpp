//
// Created by calabash_boy on 18-5-24.
//
#include<bits/stdc++.h>
#define MAXN 1005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,n,a[MAXN],b[MAXN],s[MAXN];
int main()
{
    scanf("%d",&t);
    int kase=0;
    while(t--)
    {
        kase++;
        scanf("%d",&n);
        double sum=0;
        for(int i=0;i<n+1;i++)
        {
            scanf("%d",&s[i]);
            sum+=s[i];
        }
        double res=0;
        for(int i=0;i<n;i++)
        {
            scanf("%d%d",&a[i],&b[i]);
            res=max(res,(double)b[i]);
        }
        printf("Case #%d: %.10f\n",kase,res+sum);
    }
    return 0;
}
