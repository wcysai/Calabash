#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 20005
#define INF 1000000000
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int MOD,Q,deq[MAXN];
class Crypto
{
public:
    Crypto()
    {
        sm=cnt=0;
        seed();
    }
    int decode(int z)
    {
        z^=next();
        z^=(next()<<8);
        z^=(next()<<16);
        z^=(next()<<22);
        return z;
    }
    void query(ll z)
    {
        const ll B=425481007;
        const ll MD=1000000007;
        cnt++;
        sm=((sm*B%MD+z)%MD+MD)%MD;
        seed();
    }
private:
    ll sm;
    int cnt;
    uint8_t data[256];
    int I,J;
    void swap_data(int i,int j)
    {
        uint8_t tmp=data[i];
        data[i]=data[j];
        data[j]=tmp;
    }
    void seed()
    {
        uint8_t key[8];
        for(int i=0;i<4;i++) key[i]=(sm>>(i*8));
        for(int i=0;i<4;i++) key[i+4]=(cnt>>(i*8));
        for(int i=0;i<256;i++) data[i]=i;
        I=J=0;
        int j=0;
        for(int i=0;i<256;i++)
        {
            j=(j+data[i]+key[i%8])%256;
            swap_data(i,j);
        }
    }
    uint8_t next()
    {
        I=(I+1)%256;
        J=(J+data[I])%256;
        swap_data(I,J);
        return data[(data[I]+data[J])%256];
    }
};
struct st
{
    vector<ll> a[500];
    vector<P> items;
    int sz;
    ll find(int w)
    {
        return a[w][sz-1];
    }
    void init()
    {
        items.clear();
        for(ll i=0;i<MOD;i++)
        {
            a[i].resize(1);a[i].shrink_to_fit();
            if(i==0) a[i][0]=0; else a[i][0]=-1;
        }
        sz=1;
    }
    void push(int w,int v)
    {
        for(int i=0;i<MOD;i++)
        {
            a[i].resize(sz+1);
            a[i][sz]=a[i][sz-1];
            int to=i-w; if(to<0) to+=MOD;
            if(a[to][sz-1]!=-1) a[i][sz]=max(a[i][sz],a[to][sz-1]+v);
        }
        items.push_back(P(w,v));
        sz++;
    }
    void pop()
    {
        for(int i=0;i<MOD;i++) a[i].resize(sz-1);
        items.pop_back();
        sz--;
    }
    bool empty()
    {
        if(sz==1) return true;
        return false;
    }
}st1,st2;
void add_candy(int w,int v)
{
    st1.push(w,v);
}
void shuffle()
{
    while(!st1.empty())
    {
        P p=st1.items.back();
        st1.items.pop_back();
        st1.sz--;
        st2.push(p.F,p.S);
    }
    st1.init();
}
void delete_candy()
{
    if(!st2.empty()) {st2.pop(); return;}
    shuffle();
    st2.pop();
}
void debug()
{
    for(int i=0;i<MOD;i++) printf("%d %lld %lld\n",i,st1.find(i),st2.find(i));
    ll mx1=-INF,id1=-1,mx2=-INF,id2=-1;
    for(int i=0;i<MOD;i++) 
    {
        if(st1.find(i)>mx1)
        {
            mx1=st1.find(i);
            id1=i;
        }
        if(st2.find(i)>mx2)
        {
            mx2=st2.find(i);
            id2=i;
        }
    }
    printf("%lld %lld %lld\n",mx1+mx2,id1,id2);
}
ll find_ans(int l,int r)
{
    ll ans=-1;
    ll s=0,t=0;
    for(int i=r;i>=l;i--)
    {
        while(s<t&&st2.find(deq[t-1])<st2.find(i)) t--;
        deq[t++]=i;
    }
    for(int i=0;i<MOD;i++)
    {
        if(st1.find(i)!=-1)
        {
            ll id=deq[s];
            if(st2.find(id)!=-1) ans=max(ans,st2.find(id)+st1.find(i));
        }
        l--; if(l<0) l+=MOD;
        while(s<t&&st2.find(deq[t-1])<st2.find(l)) t--;
        deq[t++]=l;
        if(deq[s]==r) s++;
        r--; if(r<0) r+=MOD;
    }
    return ans;
}
int main()
{
    scanf("%d%d",&MOD,&Q);
    Crypto c;
    st1.init();st2.init();
    for(int i=0;i<Q;i++)
    {
        int t,w,v,l,r;
        scanf("%d%d%d%d%d",&t,&w,&v,&l,&r);
        t=c.decode(t);
        w=c.decode(w);
        v=c.decode(v);
        l=c.decode(l);
        r=c.decode(r);
        if(t==1) add_candy(w%MOD,v); else delete_candy();
        ll ans=find_ans(l,r); 
        printf("%lld\n",ans);
        c.query(ans);
    }
    return 0;
}

