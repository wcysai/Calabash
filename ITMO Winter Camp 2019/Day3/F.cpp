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
int n,k,a[MAXN];
vector<int> v;
int main()
{
    freopen("perm.in","r",stdin)
    freopen("perm.out","w",stdout);
    scanf("%d",&n);
    int t=(int)sqrt(n);
    while(t*t<n) t++;
    int rem=n;
    for(int i=0;i<t;i++) {int ans=min(t,rem-t+1+i); rem-=ans; v.push_back(ans);}
    reverse(v.begin(),v.end());
    int now=1;
    for(int i=0;i<t;i++)
    {
        int last=now+v[i]-1;
        for(int j=last;j>=now;j--) printf("%d ",j);
        now=last+1;
    }
    return 0;
}

