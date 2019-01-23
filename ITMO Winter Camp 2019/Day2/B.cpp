#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,l,w,x,y,a;
int main()
{
    freopen("aisle.in","r",stdin);
    freopen("aisle.out","w",stdout);
    scanf("%d%d%d%d%d%d",&n,&l,&w,&x,&y,&a);
    int num=l/x;
    int ans=-1;
    for(int i=1;i*a<=w;i++)
   {
        int cnt=(w-i*a)/y;
        if(cnt*num<n) break;
        ans=max(ans,min(cnt,2*(i-1)+2)*num);
    }
    printf("%d\n",min(ans,n));
    return 0;
}

