//
// Created by sy-chen on 18-5-20.
//

#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll n,m;
struct inc
{
    ll id;//L:1 U:2
    ll x,h;
};
bool cmp(inc a,inc b)
{
    if(a.x!=b.x) return a.x<b.x;
    return a.id<b.id;
}
vector<inc> event;
int main()
{
    cin >> n >> m;
    // scanf("%lld%lld",&n,&m);
    ll x,y,L,U;
    x=-INF;
    cin >> y;
    //scanf("%lld",&y);
    L=y;
    ll f1=0,f2=0;
    for(ll i=0;i<n;i++)
    {
        ll nx,ny;
        // scanf("%lld%lld",&nx,&ny);
        cin >> nx >> ny;
        if(ny>y) f1=0; else f1=1;
        event.push_back((inc){1,nx,ny-y});
        x=nx;y=ny;
    }
    x=-INF;
    // scanf("%lld",&y);
    cin >> y;
    U=y;
    for(ll i=0;i<m;i++)
    {
        ll nx,ny;
        // scanf("%lld%lld",&nx,&ny);
        cin >> nx >> ny;
        if(ny>y) f2=0; else f2=1;
        event.push_back((inc){2,nx,ny-y});
        x=nx;y=ny;
    }
    if(f1^f2)
    {
        puts("0 0");
        return 0;
    }
    sort(event.begin(),event.end(),cmp);
    ll cnt=0,ans=0,sum=0,lastx=-INF,stx=-INF;
    for(ll i=0;i<event.size();i++)
    {
        //printf("%lld %lld\n",event[i].x,lastx);
        if(U>L&&stx!=-INF) sum+=(event[i].x-lastx)*(U-L);
        ll nU=U,nL=L;
        if(event[i].id==1) nL+=event[i].h; else nU+=event[i].h;
        if(U>L&&nU<nL&&stx!=-INF)
        {
            cnt++;
            ans+=sum;
        }
        if((U>L&&nU<nL)||(U<L&&nU>nL)) stx=event[i].x;
        lastx=event[i].x;
        U=nU;L=nL;
        if(L>U) sum=0;
        //printf("%lld %lld %lld\n",L,U,sum);

    }
    cout << cnt << ' ' << ans << endl;
    // printf("%lld %lld\n",cnt,ans);
    return 0;
}
