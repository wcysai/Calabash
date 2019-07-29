#include<bits/stdc++.h>
#define MAXN 3005
#define MAXK 100
#define INF 1000000000
#define BASE 19991020
#define MOD1 1012423549
#define MOD2 998244353
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
char str[MAXN][MAXN];
int fact[MAXN];
P pre[MAXK][MAXN],suf[MAXK][MAXN];
P pcoef[MAXN],scoef[MAXN];
int cnt[MAXN][MAXK];
int maxi[MAXK];
map<P,int> pr,su;
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
void compute_hash(int id)
{
    for(int i=0;i<m;i++)
    {
        int hash1=0,hash2=0;
        for(int j=0;j<n-1;j++) 
        {
            hash1=(1LL*hash1*BASE+(str[j][i]=='?'?id+1:str[j][i]-32))%MOD1;
            hash2=(1LL*hash2*BASE+(str[j][i]=='?'?id+1:str[j][i]-32))%MOD2;
        }
        pre[id][i]=P(hash1,hash2);
        //printf("%d %d\n",i,hash);
    }       
    for(int i=0;i<m;i++)
    {
        int hash1=0,hash2=0;
        for(int j=1;j<n;j++) 
        {
            hash1=(1LL*hash1*BASE+(str[j][i]=='?'?id+1:str[j][i]-32))%MOD1;
            hash2=(1LL*hash2*BASE+(str[j][i]=='?'?id+1:str[j][i]-32))%MOD2;
        }
        suf[id][i]=P(hash1,hash2);
        //printf("%d %d\n",i,hash);
    }
}
void compute_coefficient()
{
    for(int i=0;i<m;i++)
    {
        int hash1=0,hash2=0;
        for(int j=0;j<n-1;j++) 
        {
            hash1=(1LL*hash1*BASE+(str[j][i]=='?'))%MOD1;
            hash2=(1LL*hash2*BASE+(str[j][i]=='?'))%MOD2;
        }
        pcoef[i]=P(hash1,hash2);
    }
    for(int i=0;i<m;i++)
    {
        int hash1=0,hash2=0;
        for(int j=1;j<n;j++) 
        {
            hash1=(1LL*hash1*BASE+(str[j][i]=='?'))%MOD1;
            hash2=(1LL*hash2*BASE+(str[j][i]=='?'))%MOD2;
        }
        scoef[i]=P(hash1,hash2);
    }
}
void propagate(int id)
{
    for(int i=0;i<m;i++) 
    {
        pre[id][i].F=(pre[0][i].F+1LL*id*pcoef[i].F)%MOD1;
        pre[id][i].S=(pre[0][i].S+1LL*id*pcoef[i].S)%MOD2;
    }
    for(int i=0;i<m;i++) 
    {
        suf[id][i].F=(suf[0][i].F+1LL*id*scoef[i].F)%MOD1;
        suf[id][i].S=(suf[0][i].S+1LL*id*scoef[i].S)%MOD2;
    }
}
int find_ans(int pos)
{
    pr.clear();su.clear();
    for(int i=0;i<m;i++) pr[pre[pos][i]]++;
    for(int i=0;i<m;i++) su[suf[pos][i]]++;
    int ans=1;
    for(auto p:pr)
    {
        if(su[p.F]!=p.S) return 0;
        ans=1LL*ans*fact[p.S]%MOD;
    }
    return ans;
}
int main()
{
    fact[0]=1;
    for(int i=1;i<=3000;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++) scanf("%s",str[i]);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++) if(str[i][j]!='?') cnt[i][str[i][j]-33]++;
        for(int j=0;j<100;j++) maxi[j]=max(maxi[j],cnt[i][j]);
    }
    int s=0;
    for(int j=0;j<100;j++) s+=maxi[j];
    //printf("%d\n",s);
    if(s!=m-1&&s!=m) {puts("0"); return 0;}
    if(s==m)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                if(str[i][j]=='?')
                { 
                    int id=-1;
                    for(int k=0;k<100;k++) if(cnt[i][k]==maxi[k]-1) {id=k; break;}
                    assert(id!=-1);
                    str[i][j]=(char)33+id;
                }
            }
        }
        compute_hash(0);
        printf("%d\n",find_ans(0));
    }
    else
    {
        int ans=0;
        compute_hash(0); compute_coefficient();
        for(int i=1;i<=93;i++) propagate(i);
        for(int i=0;i<=93;i++)
        {
            //printf("%d %d\n",i,find_ans(i));
            if(i!=30) add(ans,find_ans(i));
            else dec(ans,92LL*find_ans(i)%MOD);
        }
        printf("%d\n",ans);
    }
    return 0;
}
