#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a[MAXN],b[MAXN];
vector<P> v;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) scanf("%d",&b[i]);
    for(int i=1;i<=n;i++) v.push_back(P(a[i],b[i]));
    sort(v.begin(),v.end(),greater<P>());
    ll ans=0;
    priority_queue<int,vector<int>,greater<int> > pque;
    for(int i=1;i<n;i+=2)
    {
        if(i<n) {pque.push(v[i].S); ans+=v[i].S;}
        if(i+1<n) {pque.push(v[i+1].S); ans+=v[i+1].S;}
        if(i+1<n) {ans-=pque.top(); pque.pop();}
    }
    printf("%lld\n",ans);
    return 0;
}
