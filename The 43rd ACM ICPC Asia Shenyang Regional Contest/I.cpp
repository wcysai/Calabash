#include<bits/stdc++.h>
#define MAXN 2005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll T,I1,I2,A1,A2,G1,G2;
ll i[2048],a[2048],g[2048];
ll fwti[2048],fwta[2048],fwtg[2048];
ll res[2048],lastres[2048];
unsigned long long ans;
void FWT(ll a[],ll n)
{
    for(ll d=1;d<n;d<<=1)
        for(ll m=d<<1,i=0;i<n;i+=m)
            for(ll j=0;j<d;j++)
            {
                ll x=a[i+j],y=a[i+j+d];
                a[i+j]=x+y;a[i+j+d]=x-y;
            }
}
void UFWT(ll a[],ll n)
{
    for(ll d=1;d<n;d<<=1)
        for(ll m=d<<1,i=0;i<n;i+=m)
            for(ll j=0;j<d;j++)
            {
                ll x=a[i+j],y=a[i+j+d];
                a[i+j]=(x+y)/2,a[i+j+d]=(x-y)/2;
            }
}
int main()
{
    scanf("%llu",&T);
    for(ll t=1;t<=T;t++)
    {
        scanf("%llu%llu%llu%llu%llu%llu",&I1,&A1,&G1,&I2,&A2,&G2);
        ans=0;
        memset(i,0,sizeof(i));memset(a,0,sizeof(a));memset(g,0,sizeof(g));
        memset(fwti,0,sizeof(fwti));memset(fwta,0,sizeof(fwta));memset(fwtg,0,sizeof(fwtg));
        memset(res,0,sizeof(res));memset(lastres,0,sizeof(lastres));
        for(ll d=0;d<2048;d++)
        {
            for(ll j=0;j<=I1&&j+d<=I2;j++) i[j^(j+d)]++;
            if(d)for(ll j=0;j<=I2&&j+d<=I1;j++) i[j^(j+d)]++;
            for(ll j=0;j<=A1&&j+d<=A2;j++) a[j^(j+d)]++;
            if(d)for(ll j=0;j<=A2&&j+d<=A1;j++) a[j^(j+d)]++;
            for(ll j=0;j<=G1&&j+d<=G2;j++) g[j^(j+d)]++;
            if(d)for(ll j=0;j<=G2&&j+d<=G1;j++) g[j^(j+d)]++;
            for(ll j=0;j<2048;j++) fwti[j]=i[j];
            for(ll j=0;j<2048;j++) fwta[j]=a[j];
            for(ll j=0;j<2048;j++) fwtg[j]=g[j];
            for(ll j=0;j<2048;j++) res[j]=1;
            FWT(fwti,2048);FWT(fwta,2048),FWT(fwtg,2048);
            //for(ll j=0;j<2048;j++) res[j]=1;
            for(ll j=0;j<2048;j++) res[j]*=fwti[j];
            for(ll j=0;j<2048;j++) res[j]*=fwta[j];
            for(ll j=0;j<2048;j++) res[j]*=fwtg[j];
            UFWT(res,2048);
            for(ll j=0;j<2048;j++)
            {
                assert(res[j] >= lastres[j]);
                ans += (res[j] - lastres[j]) * (j ^ d);
            }
            //printf("%llu %llu\n",d,ans);
            for(ll j=0;j<2048;j++) lastres[j]=res[j];
        }
        printf("Case #%llu: %llu\n",t,ans);
    }
}
