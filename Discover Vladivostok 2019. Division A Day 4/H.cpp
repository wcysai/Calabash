#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,s,f,ans;
int main()
{
    scanf("%d%d%d",&n,&s,&f);
    ans=0;
    if(s>f) swap(s,f);
    if(s==f)
    {
        if(n==1) puts("0"); else puts("-1");
        return 0;
    }
    int dist=f-s;
    if(s!=1) {dist--; ans++;}
    if(f!=n) {dist--; ans++;}
    if(dist<=-1) {puts("-1"); return 0;}
    ans+=(dist/3)+dist%3;
    printf("%d\n",ans);
    return 0;
}
