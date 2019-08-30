#include<bits/stdc++.h>
#define MAXN 65
#define MAXM 6005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int color[MAXM];
ll val[MAXM];
int n,m,tot,tot2;
struct LinearMatroid
{
    ll basis[62];
    void clear()
    {
        memset(basis,0,sizeof(basis));
    }
    void add(ll x)
    {
        for(int j=60;j>=0;j--)
        {
            if(!(x&(1LL<<j))) continue;
            if(!basis[j])
            {
                basis[j]=x;
                return;
            }
            else x^=basis[j];
        }
    }
    bool test(ll x)
    {
        for(int j=60;j>=0;j--)
        {
            if(!(x&(1LL<<j))) continue;
            if(!basis[j]) return true; else x^=basis[j];
        }
        return false;
    }
};
struct ColorfulMatroid
{
    int cnt[125];
    void clear()
    {
        memset(cnt,0,sizeof(cnt));
    }
    void add(int x)
    {
        cnt[x]++;
    }
    bool test(int x)
    {
        return (cnt[x]==0);
    }
};


template <typename MT1, typename MT2>
struct MatroidIntersection
{
    int n;
    MatroidIntersection(int _n):n(_n){}
    int pre[MAXM],id[MAXM];
    bool vis[MAXM],sink[MAXM],has[MAXM];
    queue<int> que;
    void clear_all()
    {
        memset(vis,false,sizeof(vis));
        memset(sink,false,sizeof(sink));
        memset(pre,0,sizeof(pre));
        while(que.size()) que.pop();
    }
    vector<int> getcur()
    {
        vector<int> ret;
        for(int i=1;i<=n;i++) if(has[i]) ret.push_back(i);
        return ret;
    }
    void enqueue(int v,int p)
    {
        vis[v]=true; pre[v]=p;
        que.push(v);
    }
    vector<int> run()
    {
        MT1 mt1;  MT2 mt2;
        memset(has,false,sizeof(has));
        while(true)
        {
            vector<int> cur=getcur();
            int cnt=0;
            for(int i=1;i<=n;i++) if(has[i]) id[i]=cnt++;
            MT1 allmt1; MT2 allmt2; allmt1.clear(); allmt2.clear();
            vector<MT1> vmt1(cur.size()); vector<MT2> vmt2(cur.size());
            for(auto &x:vmt1) x.clear(); for(auto &x:vmt2) x.clear();
            clear_all();
            for(auto x:cur) allmt1.add(val[x]),allmt2.add(color[x]);
            for(int i=0;i<(int)cur.size();i++)
                for(int j=0;j<(int)cur.size();j++)
                {
                    if(i==j) continue;
                    vmt1[i].add(val[cur[j]]);
                    vmt2[i].add(color[cur[j]]);
                }
            for(int i=1;i<=n;i++)
            {
                if(has[i]) continue;
                if(allmt1.test(val[i])) {que.push(i); vis[i]=true;}
            }
            for(int i=1;i<=n;i++)
            {
                if(has[i]) continue;
                if(allmt2.test(color[i])) sink[i]=true;
            }
            int last=-1;
            while(que.size())
            {
                int v=que.front(); que.pop();
                if(sink[v]) {last=v; break;}
                for(int i=1;i<=n;i++)
                {
                    if(vis[i]) continue;
                    if(has[i]==has[v]) continue;
                    if(has[v])
                    {
                        if(vmt1[id[v]].test(val[i])) enqueue(i,v);
                    }
                    else
                    {
                        if(vmt2[id[i]].test(color[v])) enqueue(i,v);
                    }
                }
            }
            if(last==-1) return cur;
            while(last)
            {
                has[last]^=1;
                last=pre[last];
            }
        }
    }
};
//Pick Your Own Nim
//In real cases, Linear Matroid Need Optimization to Pass
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        ll x;
        scanf("%lld",&x);
        val[++tot]=x; color[tot]=++tot2;
    }
    scanf("%d",&m);
    for(int i=0;i<m;i++)
    {
        int k;
        scanf("%d",&k);
        tot2++;
        for(int j=0;j<k;j++)
        {
            ll x;
            scanf("%lld",&x);
            val[++tot]=x; color[tot]=tot2;
        }
    }
    MatroidIntersection<LinearMatroid,ColorfulMatroid> matint(tot);
    vector<int> res=matint.run();
    if(res.size()<n+m) {puts("-1"); return 0;}
    else
    {
        vector<ll> ans;
        int last=n;
        for(auto x:res)
        {
            if(color[x]>last)
            {
                ans.push_back(val[x]);
                last=color[x];
            }
        }
        for(auto x:ans) printf("%lld\n",x);
    }
    return 0;
}
