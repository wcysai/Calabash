#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int N,M,mx,x;
map<int,int> cnt;
int main()
{
    scanf("%d%d",&N,&M);
    x=mx=0;
    for(int i=0;i<M;i++)
    {
        int p;scanf("%d",&p);
        mx=max(mx,p);cnt[p]++;x=max(x,cnt[p]);
    }
    int ans=0;
    for(int i=1;i*i<=N;i++)
    {
        if(N%i) continue;
        if(i*i==N)
        {
            if(mx<=i&&x<=i) ans++;
        }
        else
        {
            if(mx<=i&&x<=N/i) ans++;
            if(x<=i&&mx<=N/i) ans++;
        }
    }
    if(ans==1) puts("YES"); else puts("NO");
    return 0;
}
