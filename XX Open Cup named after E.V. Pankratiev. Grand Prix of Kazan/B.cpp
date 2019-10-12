#include<bits/stdc++.h>
#define MAXN 300005
#define MAXM 20000005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,tot;
ll k,a[MAXN];
int dp[MAXN];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
int trie[MAXM][2];
int val[MAXM];
void insert(ll x,int v)
{
    int rt=0;
    for(int i=60;i>=0;i--)
    {
        int d=(x>>i)&1;
        if(!trie[rt][d]) trie[rt][d]=++tot;
        rt=trie[rt][d];
        add(val[rt],v);
    }
}
int get_ans(ll x)
{
    int ans=0,rt=0;
    for(int i=60;i>=0;i--)
    {
        int d1=(x>>i)&1,d2=(k>>i)&1;
        if(!d2)
        {
            add(ans,val[trie[rt][d1^1]]);
            if(!trie[rt][d1]) return ans; else rt=trie[rt][d1];
        }
        else
        {
            if(!trie[rt][d1^1]) return ans; else rt=trie[rt][d1^1];
        }
    }
    add(ans,val[rt]);
    return ans;
}
int main()
{
    tot=0;
    memset(trie,0,sizeof(trie));
    memset(val,0,sizeof(val));
    scanf("%d%lld",&n,&k);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    sort(a+1,a+n+1);
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        int res=get_ans(a[i]);
        add(res,1);
        dp[i]=res;
        add(ans,dp[i]);
        insert(a[i],dp[i]);
    }
    printf("%d\n",ans);
    return 0;
}
