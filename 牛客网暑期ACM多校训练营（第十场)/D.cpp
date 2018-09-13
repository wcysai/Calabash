/*************************************************************************
    > File Name: D.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com
    > Created Time: 2018-08-19 12:45:50
 ************************************************************************/
 
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 200500
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,m,k,a[MAXN];
int _mod(int x) {return x>=MOD?x-MOD:x;}
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
int fact[MAXN],invf[MAXN];
struct op
{
    int t,pos,val;
};
vector<op> v;
int comb(int n,int k)
{
    if(n<k) return 0;
    return 1LL*fact[n]*invf[k]%MOD*invf[n-k]%MOD;
}
int main()
{
    fact[0]=invf[0]=1;
    for(int i=1;i<=200005;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[200005]=pow_mod(fact[200005],MOD-2);
    for(int i=200004;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        v.clear();
        scanf("%d",&m);
        int type,l,r,w;
        int tot=0;
        for(int i=0;i<m;i++)
        {
            scanf("%d",&type);
            if(type==1)
            {
                scanf("%d%d%d",&l,&r,&w);
                v.push_back((op){tot-1,l,w});
                v.push_back((op){tot-1,r+1,-w});
            }
            else if(type==2) tot++;
            else
            {
                scanf("%d%d",&l,&r);
                int ans=0;
                for(int j=0;j<(int)v.size();j++)
                {
                    op p=v[j];
                    int tt=tot-p.t,res;
                    if(p.pos<=l-1)
                    {
                        res=1LL*p.val*comb(l-p.pos+tt-1,l-p.pos-1)%MOD;
                        ans=ans-res;
                        if(ans>=MOD) ans-=MOD;
                        if(ans<0) ans+=MOD;
                    }
                    //printf("%d\n",ans);
                    if(p.pos<=r)
                    {
                        res=1LL*p.val*comb(r-p.pos+tt,r-p.pos)%MOD;
                        ans=ans+res;
                        if(ans>=MOD) ans-=MOD;
                        if(ans<0) ans+=MOD;
                    }
                    //printf("%d\n",ans);
                }
                printf("%d\n",ans);
            }
        }
    }
    return 0;
}
