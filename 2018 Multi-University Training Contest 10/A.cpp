#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int RLEN=1<<18|1;
inline char nc() {
    static char ibuf[RLEN],*ib,*ob;
    (ib==ob) && (ob=(ib=ibuf)+fread(ibuf,1,RLEN,stdin));
    return (ib==ob) ? -1 : *ib++;
}
inline int rd() {
    char ch=nc(); int i=0,f=1;
    while(!isdigit(ch)) {if(ch=='-')f=-1; ch=nc();}
    while(isdigit(ch)) {i=(i<<1)+(i<<3)+ch-'0'; ch=nc();}
    return i*f;
}
inline void W(int x) {
    static int buf[50];
    if(!x) {putchar('0'); return;}
    if(x<0) {putchar('-'); x=-x;}
    while(x) {buf[++buf[0]]=x%10; x/=10;}
    while(buf[0]) {putchar(buf[buf[0]--]+'0');}
}

const int mod=998244353, G=3;
inline int add(int x,int y) {return (x+y>=mod) ? (x+y-mod) : (x+y);}
inline int dec(int x,int y) {return (x-y<0) ? (x-y+mod) : (x-y);}
inline int mul(int x,int y) {return (LL)x*y%mod;}
inline int power(int a,int b,int rs=1) {for(;b;b>>=1,a=mul(a,a)) if(b&1) rs=mul(rs,a); return rs;}

const int N=1<<20|1;
const int inv6=power(6,mod-2), inv2=(mod+1)/2, inv24=mul(inv2,mul(inv2,inv6)); 
int n,k,w[N],pos[N],A[N],B[N],tp[N],tp2[N],tp3[N];
inline void init(int nn) {
    for(k=1;k<=nn;k<<=1);
    for(int i=1;i<k;i++) pos[i]=(i&1) ? ((pos[i>>1]>>1)^(k>>1)) : (pos[i>>1]>>1);
}
inline void dft(int *a,int o=1) {
    for(int i=1;i<k;i++) if(pos[i]>i) swap(a[pos[i]],a[i]);
    for(int bl=1;bl<k;bl<<=1) {
        int tl=bl<<1, wn=power(G,(mod-1)/tl);
        w[0]=1; for(int i=1;i<bl;i++) w[i]=mul(w[i-1],wn);
        for(int bg=0;bg<k;bg+=tl)
            for(int j=0;j<bl;j++) {
                int &t1=a[bg+j], &t2=a[bg+j+bl], t=mul(t2,w[j]);
                t2=dec(t1,t); t1=add(t1,t);
            }
    }
    if(!~o) {
        const int inv=power(k,mod-2); reverse(a+1,a+k);
        for(int i=0;i<k;i++) a[i]=mul(a[i],inv);
    }
}
inline void solve(int l,int r) {
    if(l==r) {
        if(!l) A[l]=1;
        else A[l]=add(A[l],((l%3==1) ? mul(2,A[l/3]) : 0)), A[l]=mul(A[l],inv6);
        return;
    } 
    int mid=(l+r)>>1, len=r-l;
    solve(l,mid); init(len*2+mid-l);
    memset(tp,0,sizeof(int)*k); 
    memset(tp2,0,sizeof(int)*k);
    memset(tp3,0,sizeof(int)*k);
    memcpy(tp,A+l,sizeof(int)*(mid-l+1));
    memcpy(tp2,A,sizeof(int)*len);
    for(int i=0,j;(j=i*2)<=len;i++) tp3[j]=A[i];

    dft(tp); dft(tp2); dft(tp3);
    for(int i=0;i<k;i++) tp2[i]=mul(tp2[i],mul(tp2[i],tp[i]));
    dft(tp2,-1);
    if(!l) {
        for(int i=mid+1;i<=r;i++) A[i]=add(A[i],tp2[i-l-1]);
    } else {
        for(int i=mid+1;i<=r;i++) A[i]=add(A[i],mul(tp2[i-l-1],3));
    } 
    for(int i=0;i<k;i++) tp[i]=mul(tp[i],tp3[i]);
    dft(tp,-1);
    for(int i=mid+1;i<=r;i++) A[i]=add(A[i],mul(tp[i-l-1],3));
    solve(mid+1,r);
}
const int L=1e5;
int main() {
    solve(0,n=L); init(L*4);
    memset(tp,0,sizeof(int)*k);
    memset(tp2,0,sizeof(int)*k);
    memset(tp3,0,sizeof(int)*k);
    for(int i=0;i<=n;i++) tp[i]=A[i];
    for(int i=0;i*2<=n;i++) tp2[i*2]=A[i];
    for(int i=0;i*3<=n;i++) tp3[i*3]=A[i];
    dft(tp); dft(tp2); dft(tp3);
    for(int i=0;i<k;i++) {
        int s=0;
        s=add(s,power(tp[i],4));
        s=add(s,mul(6,mul(tp2[i],power(tp[i],2))));
        s=add(s,mul(3,power(tp2[i],2)));
        s=add(s,mul(8,mul(tp3[i],tp[i])));
        tp[i]=s;
    } dft(tp,-1);
    for(int i=0;i<=n;i++) 
        B[i]=add(tp[i],(!(i%4)) ? mul(6,A[i/4]) : 0), B[i]=mul(B[i],inv24);
    for(int i=n;i;i--) B[i]=B[i-1]; B[0]=0;
    for(int i=0;i<=n;i+=2) B[i]=add(B[i],A[i/2]);
    memset(tp,0,sizeof(int)*k);
    for(int i=1;i<=n;i++) tp[i]=A[i];
    dft(tp); 
    for(int i=0;i<k;i++) tp[i]=mul(tp[i],tp[i]);
    dft(tp,-1);
    for(int i=1;i<=n;i++) B[i]=dec(B[i],mul(tp[i],inv2));
    for(int i=2;i<=n;i+=2) B[i]=dec(B[i],mul(A[i/2],inv2));
    for(int T=rd();T;T--)
    {
        int x=rd();
        W(B[x]),putchar(' '),W(A[x]), putchar('\n');
    }
}
