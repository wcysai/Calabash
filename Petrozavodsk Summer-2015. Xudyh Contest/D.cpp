#include<bits/stdc++.h>
#define MAXN 105
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int fact[MAXN];
int T,n,m;
bool has[MAXN];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
int pow_mod(int a,int i)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
bool is_perm(vector<int> &a)
{
    memset(has,false,sizeof(has));
    for(int i=0;i<n;i++)
    {
        if(has[a[i]]) return false;
        has[a[i]]=true;
    }
    return true;
}
vector<int> perm[MAXN];
vector<int> comb(vector<int> &a,vector<int> &b)
{
    vector<int> c;
    c.resize(a.size());
    for(int i=0;i<n;i++) c[i]=b[a[i]];
    return c;
}
int main()
{
    fact[0]=1;
    for(int i=1;i<=100;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        int cnt=0;
        int x;
        bool f=true;
        for(int i=0;i<m;i++)
        {
            scanf("%d",&x);
            if(x==-1) {cnt++; continue;}
            else
            {
                perm[i].clear();
                perm[i].push_back(x-1);
                for(int j=0;j<n-1;j++)
                {
                    scanf("%d",&x);
                    perm[i].push_back(x-1);
                }
                if(!is_perm(perm[i])) f=false;
            }
        }
        if(!f) {puts("0"); continue;}
        if(cnt!=0)
        {
            int ans=pow_mod(fact[n],cnt-1);
            printf("%d\n",ans);
            continue;
        }
        vector<int> tmp;
        tmp.resize(n);
        for(int i=0;i<n;i++) tmp[i]=i;
        for(int i=m-1;i>=0;i--) tmp=comb(tmp,perm[i]);
        for(int i=0;i<n;i++) if(tmp[i]!=i) f=false;
        if(f) puts("1"); else puts("0");
    }
    return 0;
}
