#include<bits/stdc++.h>
#define MAXN 300005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
#define x1 dijof
#define x2 dfsikfo
#define y1 fdsjiof
#define y2 dajipofs
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
ll T,n,m,x,y,k;
ll lmerge,rmerge,umerge,dmerge;
ll l,r,u,d;
P rook[MAXN];
ll res[4*MAXN];
ll bit[MAXN];
ll sum(ll i)
{
    ll s=0;
    while(i>0)
    {
        s+=bit[i];
        i-=i&-i;
    }
    return s;
}
void add(ll i,ll x)
{
    while(i<MAXN)
    {
        bit[i]+=x;
        i+=i&-i;
    }
}
set<ll> q;
char str[5];
struct answer
{
    ll tot,type,x,y;
};
bool cmp2(answer p,answer q)
{
    return p.tot<q.tot;
}
vector<answer> ans;
struct query
{
    ll x,y,cont,tot;
};
bool cmp(query p,query q)
{
    return p.x<q.x;
}
vector<query> v;
int main()
{
    scanf("%lld",&T);
    while(T--)
    {
        memset(bit,0,sizeof(bit));
        lmerge=rmerge=umerge=dmerge=0;
        q.clear();v.clear();ans.clear();
        //printf("u=%lld d=%lld l=%lld r=%lld\n",u,d,l,r);
        scanf("%lld%lld",&n,&m);l=1;r=n;u=1;d=n;
        for(ll i=0;i<4*m;i++) res[i]=0;
        for(ll i=1;i<=n;i++) scanf("%lld%lld",&rook[i].F,&rook[i].S);
        for(ll i=0;i<m;i++)
        {
            //printf("u=%lld d=%lld l=%lld r=%lld\n",u,d,l,r);
            scanf("%s",str);
            ll x;
            if(str[0]=='L')
            {
                scanf("%lld",&x);
                if(l-x>=1) {l-=x; r-=x;}
                else
                {
                    lmerge+=(x-(l-1));if(lmerge+rmerge>=n-1) {rmerge=0; lmerge=n-1;}
                    l=1;r=n-lmerge-rmerge;
                }
            }
            else if(str[0]=='R')
            {
                scanf("%lld",&x);
                if(r+x<=n) {l+=x; r+=x;}
                else
                {
                    rmerge+=(x-(n-r));if(lmerge+rmerge>=n-1) {lmerge=0; rmerge=n-1;}
                    r=n;l=1+lmerge+rmerge;
                }
            }
            else if(str[0]=='U')
            {
                scanf("%lld",&x);
                if(u-x>=1) {u-=x; d-=x;}
                else
                {
                    umerge+=(x-(u-1));if(umerge+dmerge>=n-1) {dmerge=0; umerge=n-1;}
                    //printf("%lld %lld\n",umerge,dmerge);
                    u=1;d=n-umerge-dmerge;
                }
            }
            else if(str[0]=='D')
            {
                scanf("%lld",&x);
                if(d+x<=n) {u+=x; d+=x;}
                else
                {
                    dmerge+=(x-(n-d)); if(umerge+dmerge>=n-1) {umerge=0; dmerge=n-1;}
                    //printf("%lld %lld\n",umerge,dmerge);
                    d=n;u=1+umerge+dmerge;
                }
			}
			else if(str[0]=='?')
			{
                ll xx,yy,k;scanf("%lld",&k);
                if(rook[k].F<=umerge+1) xx=u; else if(rook[k].F>=n-dmerge) xx=d; else  xx=u-1+(rook[k].F-umerge);
                if(rook[k].S<=lmerge+1) yy=l; else if(rook[k].S>=n-rmerge) yy=r; else  yy=l-1+(rook[k].S-lmerge);
                //printf("%d %d %d %d %d %d\n",lmerge,rmerge,umerge,dmerge,xx,yy);
                ans.push_back((answer){i,0,xx,yy});
            }
            else
            {
                v.push_back((query){1+umerge,1+lmerge,1,i*4});
                v.push_back((query){1+umerge,n,1,i*4+1});v.push_back((query){1+umerge,n-rmerge-1,-1,i*4+1});
                v.push_back((query){n-dmerge-1,1+lmerge,-1,i*4+2});v.push_back((query){n,1+lmerge,1,i*4+2});
                v.push_back((query){n,n,1,i*4+3});v.push_back((query){n-dmerge-1,n,-1,i*4+3});v.push_back((query){n,n-rmerge-1,-1,i*4+3});v.push_back((query){n-dmerge-1,n-rmerge-1,1,i*4+3});
                q.insert(i);
            }
            //printf("u=%lld d=%lld l=%lld r=%lld\n",u,d,l,r);
        }
        sort(rook+1,rook+n+1);
        sort(v.begin(),v.end(),cmp);
        ll now=1;
        for(ll i=0;i<(int)v.size();i++)
        {
            while(now<=n&&rook[now].F<=v[i].x) {add(rook[now].S,1); now++;}
            res[v[i].tot]+=v[i].cont*sum(v[i].y);
        }
        for(auto t:q)
        {
            ll sum=0;
            //printf("%d %d %d %d\n",res[4*t],res[4*t+1],res[4*t+2],res[4*t+3]);
            sum+=res[4*t]*(res[4*t]-1)/2;
            sum+=res[4*t+1]*(res[4*t+1]-1)/2;
            sum+=res[4*t+2]*(res[4*t+2]-1)/2;
            sum+=res[4*t+3]*(res[4*t+3]-1)/2;
            ans.push_back({t,1,sum,0});
        }
        sort(ans.begin(),ans.end(),cmp2);
        for(ll i=0;i<(int)ans.size();i++)
        {
            if(ans[i].type==0) printf("%lld %lld\n",ans[i].x,ans[i].y);
            else printf("%lld\n",ans[i].x);
        }
    }
    return 0;
}
