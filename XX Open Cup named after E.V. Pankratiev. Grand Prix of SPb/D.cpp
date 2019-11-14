#include<bits/stdc++.h>
#define MAXN 100005
#define MAXB 305
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,q,a[MAXN];
const int blocks=400;
vector<vector<int> > pre[MAXB];
vector<P> v;
ll s[MAXB][MAXN];
ll solve(vector<int> &lhs,vector<int> &rhs)
{
    int len=(int)rhs.size(),now=0;
    ll sum=0,smaller=0,res=0;
    for(int i=0;i<(int)rhs.size();i++) sum+=rhs[i];
    for(int i=0;i<(int)lhs.size();i++)
    {
        while(now<(int)rhs.size()&&rhs[now]<=lhs[i])
        {
            smaller+=rhs[now];
            now++;
        }
        res+=1LL*now*lhs[i]-smaller+(sum-smaller)-1LL*(len-now)*lhs[i];
    }
    return res;
}
int getid(int id)
{
    return (id-1)/blocks+1;
}
ll solve_prefix(int r1,int r2)
{
    if(r1==0||r2==0) return 0;
    int rid1=r1,rid2=r2;
    while(rid1%blocks!=0) rid1--;
    while(rid2%blocks!=0) rid2--;
    ll ret=0;
    if(rid1!=0) ret+=s[getid(rid1)][r2];
    if(rid2!=0) ret+=s[getid(rid2)][r1];
    if(rid1!=0&&rid2!=0) ret-=s[getid(rid1)][rid2];
    if(rid1!=r1&&rid2!=r2) ret+=solve(pre[getid(r1)][r1-rid1],pre[getid(r2)][r2-rid2]);
    return ret;
}
ll solve_all(int l1,int r1,int l2,int r2)
{
    return solve_prefix(r1,r2)-solve_prefix(l1-1,r2)-solve_prefix(r1,l2-1)+solve_prefix(l1-1,l2-1);
}
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        v.push_back(P(a[i],i));
    }
    sort(v.begin(),v.end());
    for(int i=1;i<=(n-1)/blocks+1;i++)
    {
        int st=(i-1)*blocks+1,ed=min(n,i*blocks);
        pre[i].resize(ed-st+2);
        for(int j=1;j<=ed-st+1;j++)
        {
            pre[i][j]=pre[i][j-1];
            if(j==1) pre[i][j].push_back(a[st+j-1]);
            else
            {
                int id=lower_bound(pre[i][j].begin(),pre[i][j].end(),a[st+j-1])-pre[i][j].begin();
                pre[i][j].insert(pre[i][j].begin()+id,a[st+j-1]);
            }
        }
    }
    for(int i=1;i<=(n-1)/blocks+1;i++)
    {
        int st=(i-1)*blocks+1,ed=min(n,i*blocks);
        int len=ed-st+1;
        ll sum=0;
        for(int j=st;j<=ed;j++) sum+=a[j];
        ll smaller=0;
        int now=0;
        for(int j=0;j<(int)v.size();j++)
        {
            while(now<(int)pre[i][len].size()&&pre[i][len][now]<=v[j].F)
            {
                smaller+=pre[i][len][now];
                now++;
            }
            s[i][v[j].S]=1LL*now*v[j].F-smaller+(sum-smaller)-1LL*(len-now)*v[j].F;
        }
    }
    for(int i=1;i<=(n-1)/blocks+1;i++)
        for(int j=1;j<=n;j++)
            s[i][j]+=s[i][j-1];
    for(int i=1;i<=(n-1)/blocks+1;i++)
        for(int j=1;j<=n;j++)
            s[i][j]+=s[i-1][j];
    for(int i=0;i<q;i++)
    {
        int l1,r1,l2,r2;
        scanf("%d%d%d%d",&l1,&r1,&l2,&r2);
        printf("%lld\n",solve_all(l1,r1,l2,r2));
    }
    return 0;
}
