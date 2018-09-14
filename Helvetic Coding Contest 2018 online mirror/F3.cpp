#include <bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
const double PI=acos(-1.0);
struct Complex
{
    double x,y;
    Complex(double _x = 0.0,double _y = 0.0)
    {
        x=_x;
        y=_y;
    }
    Complex operator-(const Complex &b)const
    {
        return Complex(x-b.x,y-b.y);
    }
    Complex operator +(const Complex &b)const
    {
        return Complex(x+b.x,y+b.y);
    }
    Complex operator *(const Complex &b)const
    {
        return Complex(x*b.x-y*b.y,x*b.y+y*b.x);
    }
};
ll dbit(ll x)
{
    while(x!=(x&-x)) x+=x&-x;
    return x;
}
void change(vector<Complex> &y,ll len)
{
    ll i,j,k;
    for(i=1,j=len/2;i<len-1;i++)
    {
       if(i<j)swap(y[i],y[j]);
       k = len/2;
       while(j>=k)
        {
            j-=k;
            k/=2;
        }
        if(j<k) j+=k;
    }
}
void fft(vector<Complex> &y,ll len,ll on)
{
    change(y,len);
    for(ll h=2;h<=len;h<<=1)
    {
        Complex wn(cos(-on*2*PI/h),sin(-on*2*PI/h));
        for(ll j=0;j<len;j+=h)
        {
            Complex w(1,0);
            for(ll k=j;k<j+h/2;k++)
            {
                Complex u=y[k];
                Complex t=w*y[k+h/2];
                y[k]=u+t;
                y[k+h/2]=u-t;
                w=w*wn;
            }
        }
    }
    if(on==-1)
    for(ll i=0;i<len;i++)
        y[i].x/=len;
}
ll n,m,k,x,cnt[MAXN];
vector<Complex> G[MAXN];
int main()
{
    scanf("%I64d%I64d%I64d",&n,&m,&k);
    for(ll i=1;i<=m;i++)
        G[i].clear();
    for(ll i=0;i<n;i++)
    {
        scanf("%I64d",&x);
        cnt[x]++;
    }
    for(ll i=1;i<=m;i++)
    {
        G[i].resize(cnt[i]+1);
        for(ll j=0;j<=cnt[i];j++)
            G[i][j]=Complex(1,0);
    }
    priority_queue<P,vector<P>, greater<P> > pque;
    for(ll i=1;i<=m;i++)
        pque.push(P(G[i].size(),i));
    while(pque.size()>1)
    {
        P p=pque.top();pque.pop();
        P q=pque.top();pque.pop();
        ll len=dbit(p.F+q.F-1);
        G[p.S].resize(len); G[q.S].resize(len);
        fft(G[p.S],len,1);fft(G[q.S],len,1);
        for(ll i=0;i<len;i++)
            G[p.S][i]=G[p.S][i]*G[q.S][i];
        fft(G[p.S],len,-1);
        for(ll i=0;i<len;i++)
        {
            G[p.S][i].x=1.0*((ll)(G[p.S][i].x+0.5)%1009);
            G[p.S][i].y=0;
        }
        G[p.S].resize(p.F+q.F-1);
        G[q.S].clear();
        G[q.S].shrink_to_fit();
        pque.push(P(p.F+q.F-1,p.S));
    }
    printf("%I64d\n",(ll)(G[pque.top().S][k].x+0.5));
    return 0;
}
