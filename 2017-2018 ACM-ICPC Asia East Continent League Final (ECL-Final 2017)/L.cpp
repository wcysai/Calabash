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
typedef pair<int,int> P;
int t,n;
int main()
{
    scanf("%d",&t);
    int kase=0;
    while(t--)
    {
        kase++;
        scanf("%d",&n);
        if(n>=7)
        {
           if(n&1) printf("Case #%d: Panda\n",kase);
           else if(n>15) printf("Case #%d: Sheep\n",kase);
           else printf("Case #%d: Draw\n",kase);
        }
        else printf("Case #%d: Draw\n",kase);
    }
    return 0;
}
