#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,k,d,c[MAXN];
vector<int> v;
vector<P> vv;
int main()
{
    scanf("%d%d%d%d",&n,&m,&k,&d);
    for(int i=0;i<m;i++) scanf("%d",&c[i]);
    sort(c,c+m);
    for(int i=0;i<k;i++)
    {
        int x;scanf("%d",&x);
        v.push_back(x);
    }
    int last=1;
    v.push_back(n);
    sort(v.begin(),v.end());
    if(n-1<=d)
    {
        puts("0");
        return 0;
    }
    bool flag=true;
    for(auto it:v)
    {
        if(it-last>d) {flag=false; break;}
        last=it;
    }
    ll ans=0;
    if(!flag)
    {
        for(int i=m-1;i>=1;i--) ans+=c[i];
        int last=1;
        for(auto it:v)
        {
            if(it-last>d) ans+=c[0];
            last=it;
        }
    }
    else
    {
        for(int i=0;i<(int)v.size()-1;i++) {vv.push_back(P(v[i]-d+1,1)); vv.push_back(P(v[i]+1,-1));}
        int num=INF;
        vv.emplace_back(2,0);
        sort(vv.begin(),vv.end());
        int cur=0;
        for(int i=0;i<(int)vv.size();i++)
        {
            cur+=vv[i].S;
            if(vv[i].F<=1) continue;
            if(vv[i].F+d-1>=n) break;
            if(i==vv.size()-1||vv[i+1].F!=vv[i].F) num=min(num,cur);
        }
        for(int i=0;i+num<m;i++) ans+=c[i];
    }
    printf("%lld\n",ans);
    return 0;
}
