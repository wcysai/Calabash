#include<bits/stdc++.h>
#define MAXN 305
#define MAXM 150005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
const double PI=acos(-1.0);
namespace fft
{
    struct num
    {
        double x,y;
        num() {x=y=0;}
        num(double x,double y):x(x),y(y){}
    };
    inline num operator+(num a,num b) {return num(a.x+b.x,a.y+b.y);}
    inline num operator-(num a,num b) {return num(a.x-b.x,a.y-b.y);}
    inline num operator*(num a,num b) {return num(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);}
    inline num conj(num a) {return num(a.x,-a.y);}

    int base=1;
    vector<num> roots={{0,0},{1,0}};
    vector<int> rev={0,1};
    const double PI=acosl(-1.0);

    void ensure_base(int nbase)
    {
        if(nbase<=base) return;
        rev.resize(1<<nbase);
        for(int i=0;i<(1<<nbase);i++)
            rev[i]=(rev[i>>1]>>1)+((i&1)<<(nbase-1));
        roots.resize(1<<nbase);
        while(base<nbase)
        {
            double angle=2*PI/(1<<(base+1));
            for(int i=1<<(base-1);i<(1<<base);i++)
            {
                roots[i<<1]=roots[i];
                double angle_i=angle*(2*i+1-(1<<base));
                roots[(i<<1)+1]=num(cos(angle_i),sin(angle_i));
            }
            base++;
        }
    }

    void fft(vector<num> &a,int n=-1)
    {
        if(n==-1) n=a.size();
        assert((n&(n-1))==0);
        int zeros=__builtin_ctz(n);
        ensure_base(zeros);
        int shift=base-zeros;
        for(int i=0;i<n;i++)
            if(i<(rev[i]>>shift))
                swap(a[i],a[rev[i]>>shift]);
        for(int k=1;k<n;k<<=1)
        {
            for(int i=0;i<n;i+=2*k)
            {
                for(int j=0;j<k;j++)
                {
                    num z=a[i+j+k]*roots[j+k];
                    a[i+j+k]=a[i+j]-z;
                    a[i+j]=a[i+j]+z;
                }
            }
        }
    }

    vector<num> fa,fb;

    vector<ll> multiply(vector<int> &a, vector<int> &b)
    {
        int need=a.size()+b.size()-1;
        int nbase=0;
        while((1<<nbase)<need) nbase++;
        ensure_base(nbase);
        int sz=1<<nbase;
        if(sz>(int)fa.size()) fa.resize(sz);
        for(int i=0;i<sz;i++)
        {
            int x=(i<(int)a.size()?a[i]:0);
            int y=(i<(int)b.size()?b[i]:0);
            fa[i]=num(x,y);
        }
        fft(fa,sz);
        num r(0,-0.25/sz);
        for(int i=0;i<=(sz>>1);i++)
        {
            int j=(sz-i)&(sz-1);
            num z=(fa[j]*fa[j]-conj(fa[i]*fa[i]))*r;
            if(i!=j) fa[j]=(fa[i]*fa[i]-conj(fa[j]*fa[j]))*r;
            fa[i]=z;
        }
        fft(fa,sz);
        vector<ll> res(need);
        for(int i=0;i<need;i++) res[i]=fa[i].x+0.5;
        return res;
    }

    vector<int> multiply_mod(vector<int> &a,vector<int> &b,int m,int eq=0)
    {
        int need=a.size()+b.size()-1;
        int nbase=0;
        while((1<<nbase)<need) nbase++;
        ensure_base(nbase);
        int sz=1<<nbase;
        if(sz>(int)fa.size()) fa.resize(sz);
        for(int i=0;i<(int)a.size();i++)
        {
            int x=(a[i]%m+m)%m;
            fa[i]=num(x&((1<<15)-1),x>>15);
        }
        fill(fa.begin()+a.size(),fa.begin()+sz,num{0,0});
        fft(fa,sz);
        if(sz>(int)fb.size()) fb.resize(sz);
        if(eq) copy(fa.begin(),fa.begin()+sz,fb.begin());
        else
        {
            for(int i=0;i<(int)b.size();i++)
            {
                int x=(b[i]%m+m)%m;
                fb[i]=num(x&((1<<15)-1),x>>15);
            }
            fill(fb.begin()+b.size(),fb.begin()+sz,num{0,0});
            fft(fb,sz);
        }
        double ratio=0.25/sz;
        num r2(0,-1),r3(ratio,0),r4(0,-ratio),r5(0,1);
        for(int i=0;i<=(sz>>1);i++)
        {
            int j=(sz-i)&(sz-1);
            num a1=(fa[i]+conj(fa[j]));
            num a2=(fa[i]-conj(fa[j]))*r2;
            num b1=(fb[i]+conj(fb[j]))*r3;
            num b2=(fb[i]-conj(fb[j]))*r4;
            if(i!=j)
            {
                num c1=(fa[j]+conj(fa[i]));
                num c2=(fa[j]-conj(fa[i]))*r2;
                num d1=(fb[j]+conj(fb[i]))*r3;
                num d2=(fb[j]-conj(fb[i]))*r4;
                fa[i]=c1*d1+c2*d2*r5;
                fb[i]=c1*d2+c2*d1;
            }
            fa[j]=a1*b1+a2*b2*r5;
            fb[j]=a1*b2+a2*b1;
        }
        fft(fa,sz);fft(fb,sz);
        vector<int> res(need);
        for(int i=0;i<need;i++)
        {
            ll aa=fa[i].x+0.5;
            ll bb=fb[i].x+0.5;
            ll cc=fa[i].y+0.5;
            res[i]=(aa+((bb%m)<<15)+((cc%m)<<30))%m;
        }
        return res;
    }
    vector<int> square_mod(vector<int> &a,int m)
    {
        return multiply_mod(a,a,m,1);
    }
};
int T,N;
ll ans;
vector<int> A,B,C;
vector<int> Aval,Bval,Cval;
void solve_fft()
{
    vector<ll> tmp=fft::multiply(Aval,Bval);
    for(int i=1;i<(int)Cval.size();i++)
    {
        tmp[i]+=tmp[i-1];
        ans-=tmp[i-1]*Cval[i];
    }
    tmp=fft::multiply(Bval,Cval);
    for(int i=1;i<(int)Aval.size();i++)
    {
        tmp[i]+=tmp[i-1];
        ans-=tmp[i-1]*Aval[i];
    }
    tmp=fft::multiply(Aval,Cval);
    for(int i=1;i<(int)Bval.size();i++)
    {
        tmp[i]+=tmp[i-1];
        ans-=tmp[i-1]*Bval[i];
    }
}
void solve_brute()
{
    for(int i=(int)Aval.size()-2;i>=0;i--) Aval[i]+=Aval[i+1];
    for(int i=(int)Bval.size()-2;i>=0;i--) Bval[i]+=Bval[i+1];
    for(int i=(int)Cval.size()-2;i>=0;i--) Cval[i]+=Cval[i+1];
    for(int i=0;i<(int)A.size();i++)
        for(int j=0;j<(int)B.size();j++)
            if(A[i]+B[j]<100000) ans-=Cval[A[i]+B[j]+1];
    for(int i=0;i<(int)A.size();i++)
        for(int j=0;j<(int)C.size();j++)
            if(A[i]+C[j]<100000) ans-=Bval[A[i]+C[j]+1];
    for(int i=0;i<(int)B.size();i++)
        for(int j=0;j<(int)C.size();j++)
            if(B[i]+C[j]<100000) ans-=Aval[B[i]+C[j]+1];
}
int main()
{
    scanf("%d",&T);
    for(int t=1;t<=T;t++)
    {
        scanf("%d",&N);
        ans=1LL*N*N*N;
        A.clear(); B.clear(); C.clear();
        Aval.clear(); Bval.clear(); Cval.clear();
        Aval.resize(100001); Bval.resize(100001); Cval.resize(100001);
        for(int i=0;i<N;i++)
        {
            int x;
            scanf("%d",&x); A.push_back(x);
            Aval[x]++;
        }
        for(int i=0;i<N;i++)
        {
            int x;
            scanf("%d",&x); B.push_back(x);
            Bval[x]++;
        }
        for(int i=0;i<N;i++)
        {
            int x;
            scanf("%d",&x); C.push_back(x);
            Cval[x]++;
        }
        if(N<=1000) solve_brute(); else solve_fft();
        printf("Case #%d: %lld\n",t,ans);
    }
    return 0;
}
