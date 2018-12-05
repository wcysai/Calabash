#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int N,K,a[MAXN];
vector<P> st[MAXN];
vector<int> ed[MAXN];
int sum[MAXN],has[MAXN];
int now[MAXN];
set<P> s;
int main()
{
    scanf("%d%d",&N,&K);
    for(int i=1;i<=N;i++) scanf("%d",&a[i]);
    for(int i=1;i<=N;i++)
    {
        has[i]=has[i-1];sum[i]=sum[i-1];
        if(a[i]==0) has[i]++;sum[i]+=a[i];
    }
    bool f=true;
    for(int i=1;i<=K;i++)
    {
        int l,r,x;
        scanf("%d%d%d",&l,&r,&x);
        int s=sum[r]-sum[l-1],unfilled=has[r]-has[l-1];
        if(s+unfilled<x) f=false;
        int most=(s+unfilled-x)/2;
        st[l].push_back(P(most,i));
        ed[r+1].push_back(i);
    }
    if(!f) {puts("Impossible"); return 0;}
    int cur=0;
    for(int i=1;i<=N;i++)
    {
        for(auto p:st[i]) {s.insert(P(p.F+cur,p.S)); now[p.S]=p.F+cur;}
        for(auto p:ed[i]) s.erase(P(now[p],p));
        if(a[i]!=0) continue;
        if(!s.size())
        {
            a[i]=-1;
            continue;
        }
        else
        {
            auto it=s.begin();
            if(it->F>cur)
            {
                cur++;
                a[i]=-1;
            }
            else a[i]=1;
        }
    }
    for(int i=1;i<=N;i++) printf("%d%c",a[i],i==N?'\n':' ');
    return 0;
}
