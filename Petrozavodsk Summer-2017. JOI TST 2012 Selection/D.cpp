/*************************************************************************
    > File Name: D.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-11-13 22:41:54
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll N,n,k,a[MAXN];   
ll pow_mod(ll a,ll i)
{
    ll s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
struct Point
{
    ll x,y;
    ll type;
}pt[MAXN],p[MAXN];
ll xmult(const Point &po,const Point &ps,const Point &pe)
{
    return (ps.x-po.x)*(pe.y-po.y)-(pe.x-po.x)*(ps.y-po.y);
}
ll getdis(const Point &st,const Point &se)
{
    return (st.x-se.x)*(st.x-se.x)+(st.y-se.y)*(st.y-se.y);
}
Point gsort;
bool gcmp( const Point &ta, const Point &tb)
{
    ll tmp = xmult( gsort, ta, tb);
    if(tmp==0) return getdis( gsort, ta) < getdis( gsort, tb);
    else if(tmp>0) return 1;
    return 0;
}
ll sgn(ll ta, ll tb)
{
    if(ta==tb) return 0;
    if(ta<tb) return -1;
    return 1;
}
void graham(Point _p[],ll _n)
{
    ll cur=0;
    for(ll i=1;i<_n;i++)
        if(sgn(_p[cur].y,_p[i].y)<0||(sgn(_p[cur].y,_p[i].y)==0&&sgn(_p[cur].x,_p[i].x)<0)) cur=i;
    swap(_p[cur],_p[0]);
    n=0,gsort=pt[n++]=_p[0];
    if( _n<=1) return;
    sort(_p+1,_p+_n,gcmp);
    pt[n++]=_p[1];
    for(ll i=2;i<_n;i++)
    {
        while(n>1&&sgn(xmult(pt[n-2],pt[n-1],_p[i]),0)<=0) n--;
        pt[n++]=_p[i];
    }
}
int main()
{
    scanf("%lld",&N);
    ll cnt=0,CNT1=0,CNT2=0;
    for(ll i=0;i<N;i++) 
    {
        scanf("%lld%lld%lld",&p[i].x,&p[i].y,&p[i].type); 
        if(p[i].type==0) cnt++;
        if(p[i].type==1) CNT1++;
        if(p[i].type==2) CNT2++;
    }
    graham(p,N);
    for(ll i=0;i<n;i++) if(pt[i].type==0) cnt--;
    ll ans=pow_mod(2,cnt);
    bool f=false;
    ll cnt1=0,cnt2=0;
    for(ll i=0;i<n;i++) 
    {
        if(pt[i].type==1) {cnt1++; f=true;}
        if(pt[i].type==2) {cnt2++; f=true;}
    }
    if(!f)
    {
        ans=(1LL*(n-1)*n+2)%MOD*ans%MOD;
        if(CNT1==0) ans--;
        if(CNT2==0) ans--;
        printf("%lld\n",ans);
        return 0;
    }
    ll lastcolor=-1,len=0,cntdiff=0,res=0;
    for(ll i=n-1;i>=0;i--)
    {
        if(pt[i].type!=0)
        {
            lastcolor=pt[i].type;
            break;
        }
        len++;
    }
    if(cnt1!=0&&cnt2!=0) res=1;
    for(ll i=0;i<n;i++)
    {
        if(pt[i].type==0) len++;
        else
        {
            if(pt[i].type==1)
            {
                if(lastcolor==2) cntdiff++; 
                if(cnt2==0) 
                {
                    if(len) res=(res+1LL*len*(len+1)/2)%MOD;
                }
                if(lastcolor==2) res=1LL*res*(len+1)%MOD;
                lastcolor=1;len=0;
            }
            else if(pt[i].type==2)
            {
                if(lastcolor==1) cntdiff++;
                if(cnt1==0) 
                {
                    if(len) res=(res+1LL*len*(len+1)/2)%MOD;
                }
                if(lastcolor==1) res=1LL*res*(len+1)%MOD;
                lastcolor=2;len=0;
            }
        }
    }
    if(cntdiff>2)
    {
        puts("0");
        return 0;
    }
    if(cnt1==0||cnt2==0) res++; else assert(cntdiff==2);
    ans=1LL*ans*res%MOD;
    if(CNT1==0) ans--;
    if(CNT2==0) ans--;
    if(ans<0) ans+=MOD;
    printf("%lld\n",ans);
    return 0;
}

