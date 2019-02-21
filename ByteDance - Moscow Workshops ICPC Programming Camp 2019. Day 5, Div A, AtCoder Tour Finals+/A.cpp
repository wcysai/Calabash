#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAXN 100005
#define INF 1000000001
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef pair<int,int> P;
int n,k,a[MAXN],d[MAXN];
int main()
{
    scanf("%d%d",&n,&k);
    int sum=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        d[i]=max(0,k+1-a[i]);
        sum+=d[i];
    }
    bool f= true;
    if(sum>k) f=false;
    for(int i=1;i<=n;i++)
    {
        if(d[i]>(k+1)/2) f=false;
    }
    if(!f) {puts("-1"); return 0;}
    for(int i=1;i<=n;i++)
    {
        while(sum<k&&d[i]<(k+1)/2)
        {
            d[i]++;
            sum++;
        }
    }
    set<P> s;
    for(int i=1;i<=n;i++)
    {
        if(d[i]) s.insert(P(d[i],i));
    }
    printf("%d\n",n+k*(n-1));
    auto it=s.end();it--;
    int last=it->S;
    if(it->F==1) s.erase(it);
    else
    {
        P p=*it;
        s.erase(it);
        p.F--; s.insert(p);
    }
    for(int i=1;i<=n;i++)
    {
        if(i==last) continue;
        printf("%d ",i);
    }
    printf("%d ",last);
    while(s.size())
    {
        auto it=s.end();
        it--;
        if(it->S==last)
        {
            assert(s.size()>1);
            it--;
        }
        for(int i=1;i<=n;i++)
        {
            if(i==last||i==it->S) continue;
            printf("%d ",i);
        }
        last=it->S;
        if(it->F==1) s.erase(it); else
        {
            P p=*it;
            s.erase(it);
            p.F--; s.insert(p);
        }
        printf("%d ",last);
    }
    for(int i=1;i<=n;i++)
    {
        if(i==last) continue;
        printf("%d ",i);
    }
    return 0;
}
