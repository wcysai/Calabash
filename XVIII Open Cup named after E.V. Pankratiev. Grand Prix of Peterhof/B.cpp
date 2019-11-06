#include<bits/stdc++.h>
#define MAXN 6
#define MAXM 305
#define MAXK (1<<12)
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int,int> P;
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
int n,m;
unordered_map<ull,int> dp[64],ndp[64];
void go(ll match_mask,int pos,int color_mask,int cnt,unordered_map<ull,int> &to,int curbit)
{
    ll to_mask=0;
    for(int i=0;i<(1<<n);i++)
    {
        if(!(match_mask&(1ULL<<i))) continue;
        if(!(i&(1<<pos)))
        {
            if(((color_mask>>pos)&1)!=curbit)
            {
                int res=i|(1<<pos);
                to_mask|=(1ULL<<res);
            }
        }
        else
        {
            int res=i&(~(1<<pos));
            to_mask|=(1ULL<<res);
            if(pos>0&&!(i&(1<<(pos-1)))&&((color_mask>>(pos-1))&1)!=curbit)
            {
                res=i|(1<<pos)|(1<<(pos-1));
                to_mask|=(1ULL<<res);
            }
        }
    }
    if(to_mask&&cnt) add(to[to_mask],cnt);
}
int main()
{
    freopen("dabiao.txt","w",stdout);
    int tot=0;
    for(n=1;n<=6;n++)
    {
        m=300;
        for(int color_mask=0;color_mask<(1<<n);color_mask++)
        {
            dp[color_mask].clear();
            ndp[color_mask].clear();
        }
        dp[0][(1ULL<<(1<<n)-1)]=1;
        for(int j=0;j<m;j++)
        {
            for(int i=0;i<n;i++)
            {
                for(int color_mask=0;color_mask<(1<<n);color_mask++)
                {
                    for(auto x:dp[color_mask])
                    {
                        go(x.F,i,color_mask,x.S,ndp[color_mask|(1<<i)],1);
                        go(x.F,i,color_mask,x.S,ndp[color_mask&(~(1<<i))],0);
                    }
                }
                for(int color_mask=0;color_mask<(1<<n);color_mask++)
                {
                    dp[color_mask].swap(ndp[color_mask]);
                    ndp[color_mask].clear();
                }
            }
            int ans=0;
            for(int color_mask=0;color_mask<(1<<n);color_mask++)
                for(auto x:dp[color_mask])
                    if(((x.F>>((1<<n)-1))&1)==1) add(ans,x.S);
            printf("%d,",ans);
            tot++;
            if(tot%20==0) printf("\n");
        }
    }
    return 0;
}
