#include<bits/stdc++.h>
#define MAXN 36
#define MAXM (1<<18)
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,m,q,w[MAXN];
int ans[MAXM];
vector<P> A,B,C;
void add(int &a,int b) {a+=b; if(a>=q) a-=q;}
int main()
{
    scanf("%d",&T);
    for(int tot=1;tot<=T;tot++)
    {
        A.clear(); B.clear(); C.clear();
        scanf("%d%d%d",&n,&m,&q);
        for(int i=0;i<n;i++) scanf("%d",&w[i]);
        for(int i=0;i<m;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            u--; v--;
            if(u>v) swap(u,v);
            if(u<n/2&&v<n/2) A.push_back(P(u,v));
            else if(u>=n/2&&v>=n/2) B.push_back(P(u,v));
            else C.push_back(P(u,v));
        }
        memset(ans,0,sizeof(ans));
        for(int mask=0;mask<(1<<(n/2));mask++)
        {
            bool f=true;
            for(auto p:A)
            {
                int u=p.F,v=p.S;
                if((mask&(1<<u))||(mask&(1<<v))) ;
                else
                {
                    f=false;
                    break;
                }
            }
            if(!f) continue;
            int res=1;
            for(int i=0;i<n/2;i++) if(mask&(1<<i)) res=1LL*res*w[i]%q;
            ans[mask]=res;
        }
        for(int i=0;i<n/2;i++)
            for(int j=0;j<(1<<(n/2));j++)
                if(!(j&(1<<i))) add(ans[j],ans[j^(1<<i)]);
        int ret=0;
        for(int mask=0;mask<(1<<(n-n/2));mask++)
        {
             bool f=true;
            for(auto p:B)
            {
                int u=p.F-n/2,v=p.S-n/2;
                if((mask&(1<<u))||(mask&(1<<v))) ;
                else
                {
                    f=false;
                    break;
                }
            }
            if(!f) continue;
            int res=1;
            for(int i=0;i<n-n/2;i++) if(mask&(1<<i)) res=1LL*res*w[n/2+i]%q;
            int nmask=0;
            for(auto p:C)
            {
                int u=p.F,v=p.S-n/2;
                if(mask&(1<<v)) continue;
                else nmask|=(1<<u);
            }
            add(ret,1LL*res*ans[nmask]%q);
        }
        printf("Case #%d: %d\n",tot,ret);
    }
    return 0;
}
