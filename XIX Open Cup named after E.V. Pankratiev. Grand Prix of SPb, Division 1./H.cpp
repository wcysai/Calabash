/*************************************************************************
    > File Name: H.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-12-07 14:59:51
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,C;
int a[20][20],b[20][20];
int l[20],r[20],ans[20];
int A;
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
vector<int> valid;
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
bool check(int now,int x)
{
    int ret=0,sz=(int)valid.size();
    for(int mask=1;mask<(1<<sz);mask++)
    {
        for(int i=1;i<=k;i++) l[i]=0,r[i]=C;
        r[now]=x+1;
        int bits=__builtin_popcount(mask);
        int cur=1;
        for(int i=0;i<sz;i++)
        {
            if(!cur) break;
            if((mask>>i)&1)
            {
                for(int j=now;j<=k;j++)
                {
                    l[j]=max(l[j],a[valid[i]][j]);
                    r[j]=min(r[j],b[valid[i]][j]);
                }
            }
        }
        for(int j=now;j<=k;j++) cur=1LL*cur*max(0,r[j]-l[j])%MOD;
        if(bits&1) add(ret,cur); else dec(ret,cur);
    }
    //printf("%d %lld\n",ret,1LL*A*(x+1)%MOD);
    return (ret!=1LL*A*(x+1)%MOD);
}
int main()
{
    scanf("%d%d%d",&n,&k,&C);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=k;j++) scanf("%d",&a[i][j]);
        for(int j=1;j<=k;j++) scanf("%d",&b[i][j]);
    }
    valid.clear();
    for(int i=1;i<=n;i++) valid.push_back(i);
    memset(ans,-1,sizeof(ans));
    A=pow_mod(C,k-1);
    if(!check(1,C-1)) {puts("NO"); return 0;}
    puts("YES");
    for(int i=1;i<=k;i++)
    {
        int lb=-1,rb=C-1;
        A=pow_mod(C,k-i);
        while(rb-lb>1)
        {
            int mid=(lb+rb)/2;
            if(check(i,mid)) rb=mid; else lb=mid;
        }
        ans[i]=rb;
        vector<int> tmp;tmp.clear();
        for(auto it:valid) if(ans[i]>=a[it][i]&&ans[i]<b[it][i]) tmp.push_back(it);
        valid.clear();
        for(auto it:tmp) valid.push_back(it);
    }
    for(int i=1;i<=k;i++) printf("%d%c",ans[i],i==k?'\n':' ');
    return 0;
}

