#include<bits/stdc++.h>
#define MAXN 5000
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,double> P;
int n,x,r[MAXN];
map<int,double> mp;
int nbit(int x)
{
    while(x!=(x&-x)) x+=(x&-x);
    return x;
}
bool cmp(int x,int y) {return x>y;}
vector<P> G[MAXN];
void fight(vector<P> &a,vector<P> &b,vector<P> &c)
{
    c.clear();
    mp.clear();
    for(int i=0;i<a.size();i++)
        for(int j=0;j<b.size();j++)
        {
            P p1=a[i],p2=b[j];
            if(p1.F==0&&p2.F==0)
            {
                if(mp.find(0)==mp.end()) mp[0]=p1.S*p2.S; else mp[0]+=p1.S*p2.S;
                c.push_back(P(0,p1.S*p2.S));
                continue;
            }
            if(mp.find(p1.F)==mp.end()) mp[p1.F]=p1.S * p2.S * p1.F / (p1.F + p2.F); else mp[p1.F]+=p1.S * p2.S * p1.F / (p1.F + p2.F);
            if(mp.find(p2.F)==mp.end()) mp[p2.F]=p1.S * p2.S * p2.F / (p1.F + p2.F); else mp[p2.F]+=p1.S * p2.S * p2.F / (p1.F + p2.F);
        }
        for(auto it=mp.begin();it!=mp.end();it++) c.push_back(P(it->first,it->second));
}
int main()
{
    scanf("%d",&n);
    int len=nbit(n);
    double cur=0;
    for(int i=0;i<n;i++)
    {
        scanf("%d",&r[i]);
        if(i==0) cur=(double)r[i];
    }
    sort(r+1,r+n,cmp);
    for(int i=1;i<n;i++)
        G[i-1].push_back(P(r[i],1.0));
    if(n!=len)
    {
        int advance=len-n;
        int remain=n-advance;
        for(int i=0;i<remain/2;i++)
        {
            vector<P> v;
            fight(G[i*2],G[i*2+1],v);
            G[i].clear();
            for (int j = 0; j < v.size(); j++)
                G[i].push_back(v[j]);
        }
        for(int i=remain/2;i<len/2-1;i++)
        {
            G[i].clear();
            G[i].push_back(G[remain+i-remain/2][0]);
        }
        len/=2;
    }
    double prob=1;
    for(;len>1;len>>=1)
    {
        double res = 0.0;
        for (int i = 0; i < G[len - 2].size(); i++)
        {
            P p = G[len - 2][i];
            res += p.S * cur / (p.F + cur);
        }
        prob*=res;
        for (int i = 0; i < len / 2 - 1; i++)
        {
            vector<P> v;
            fight(G[i*2],G[i*2+1],v);
            G[i].clear();
            for (int j = 0; j < v.size(); j++)
                G[i].push_back(v[j]);
        }
    }
    printf("%.10f\n",prob);
    return 0;
}
