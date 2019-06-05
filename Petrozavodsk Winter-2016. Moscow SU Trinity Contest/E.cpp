#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int a,b,ta,tb;
set<int> s;
vector<int> da,db;
set<int> forbid;
void solve(int x)
{
    if(x==ta||x==tb) return;
    if(forbid.count(x*2)) solve(x*2); else s.insert(x*2);
    if(forbid.count(x*2+1)) solve(x*2+1); else s.insert(x*2+1);
}
int main()
{
    scanf("%d%d",&a,&b);
    bool f=true;
    tb=b,ta=a;
    while(tb)
    {
        tb>>=1;
        if(a==tb) f=false;
    }
    while(ta)
    {
        ta>>=1;
        if(b==ta) f=false;
    }
    if(!f) {puts("-1"); return 0;}
    ta=a; tb=b;
    s.insert(a); s.insert(b);
    while(a)
    {
        da.push_back(a&1);
        a>>=1;
    }
    while(b)
    {
        db.push_back(b&1);
        b>>=1;
    }
    reverse(da.begin(),da.end()); reverse(db.begin(),db.end());
    int x=0;
    for(int i=0;i<(int)da.size();i++)
    {
        x<<=1; x+=da[i];
        forbid.insert(x);
    }
    x=0;
    for(int i=0;i<(int)db.size();i++)
    {
        x<<=1; x+=db[i];
        forbid.insert(x);
    }
    solve(1);
    for(auto x:s) printf("%d ",x);
    return 0;
}
    
