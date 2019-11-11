#include<bits/stdc++.h>
#define MAXN 205
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
bool swp;
deque<P> ans;
void construct(int m)
{
    ans.push_back(P(1,3)); ans.push_back(P(1,1)); ans.push_back(P(1,4));
    ans.push_back(P(1,2)); ans.push_back(P(1,5)); ans.push_front(P(1,6));
    int now=6;
    while(now+4!=m)
    {
        now++; if(now&1) ans.push_back(P(1,now)); else ans.push_front(P(1,now));
    }
    if(now&1)
    {
        ans.push_back(P(1,now+3)); ans.push_back(P(1,now+1));
        ans.push_back(P(1,now+4)); ans.push_back(P(1,now+2));
    }
    else
    {
        ans.push_front(P(1,now+3)); ans.push_front(P(1,now+1));
        ans.push_front(P(1,now+4)); ans.push_front(P(1,now+2));
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    if(n>m) {swap(n,m); swp=true;} else swp=false;
    if(n==1)
    {
        if(m<10&&m!=5)
        {
            puts("-1");
            return 0;
        }
        else if(m==5)
        {
            ans.push_back(P(1,3)); ans.push_back(P(1,1)); ans.push_back(P(1,4));
            ans.push_back(P(1,2)); ans.push_back(P(1,5));
        }
        else construct(m);
    }
    else if(m>=5)
    {
        construct(n*m);
        for(auto &p:ans)
        {
            int pos=p.S;
            int x=pos/m+1,y=pos%m;
            if(y==0) {y=m; x--;}
            if(x%2==0) y=m+1-y;
            p.F=x; p.S=y;
        }
    }
    else if(n==2)
    {
        if(m==2) {puts("-1"); return 0;}
        else if(m==3)
        {
            ans.push_back(P(1,1)); ans.push_back(P(2,2)); ans.push_back(P(1,3));
            ans.push_back(P(2,1)); ans.push_back(P(1,2)); ans.push_back(P(2,3));
        }
        else
        {
            ans.push_back(P(1,1)); ans.push_back(P(2,2)); ans.push_back(P(2,4)); ans.push_back(P(1,3));
            ans.push_back(P(2,1)); ans.push_back(P(1,2)); ans.push_back(P(1,4)); ans.push_back(P(2,3));
        }
    }
    else if(n==3)
    {
        if(m==3)
        {
            ans.push_back(P(1,1)); ans.push_back(P(3,2)); ans.push_back(P(1,3));
            ans.push_back(P(2,2)); ans.push_back(P(3,1)); ans.push_back(P(1,2));
            ans.push_back(P(3,3)); ans.push_back(P(2,1)); ans.push_back(P(2,3));
        }
        else if(m==4)
        {
            ans.push_back(P(1,1)); ans.push_back(P(1,3)); ans.push_back(P(2,4)); ans.push_back(P(3,3));
            ans.push_back(P(1,4)); ans.push_back(P(3,4)); ans.push_back(P(2,3)); ans.push_back(P(3,2));
            ans.push_back(P(2,1)); ans.push_back(P(1,2)); ans.push_back(P(3,1)); ans.push_back(P(2,2));
        }
    }
    else if(n==4)
    {
        ans.push_back(P(1,1)); ans.push_back(P(1,3)); ans.push_back(P(2,4)); ans.push_back(P(3,3));
        ans.push_back(P(4,4)); ans.push_back(P(4,2)); ans.push_back(P(3,4)); ans.push_back(P(4,3));
        ans.push_back(P(2,3)); ans.push_back(P(1,4)); ans.push_back(P(1,2)); ans.push_back(P(2,1));
        ans.push_back(P(3,2)); ans.push_back(P(4,1)); ans.push_back(P(2,2)); ans.push_back(P(3,1));
    }
    if(swp)
    {
        for(auto &p:ans) swap(p.F,p.S);
    }
    for(auto p:ans) printf("%d %d\n",p.F,p.S);
    return 0;
}
