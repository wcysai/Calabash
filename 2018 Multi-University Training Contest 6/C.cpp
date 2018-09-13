//
// Created by calabash_boy on 18-8-8.
//
#pragma GCC optimize(3)

#define FI(n) FastIO::read(n)
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXBUF = 10000;
char buf[MAXBUF], *ps = buf, *pe = buf+1;
inline void rnext()
{
    if(++ps == pe)
        pe = (ps = buf)+fread(buf,sizeof(char),sizeof(buf)/sizeof(char),stdin);
}

template <class T>
inline bool in(T &ans)
{
    ans = 0;
    T f = 1;
    if(ps == pe) return false;//EOF
    do{
        rnext();
        if('-' == *ps) f = -1;
    }while(!isdigit(*ps) && ps != pe);
    if(ps == pe) return false;//EOF
    do
    {
        ans = (ans<<1)+(ans<<3)+*ps-48;
        rnext();
    }while(isdigit(*ps) && ps != pe);
    ans *= f;
    return true;
}
const int  MAXOUT=10000;
char bufout[MAXOUT], outtmp[50],*pout = bufout, *pend = bufout+MAXOUT;
inline void write()
{
    fwrite(bufout,sizeof(char),pout-bufout,stdout);
    pout = bufout;
}
inline void out_char(char c){ *(pout++) = c;if(pout == pend) write();}
inline void out_str(char *s)
{
    while(*s)
    {
        *(pout++) = *(s++);
        if(pout == pend) write();
    }
}
template <class T>
inline void out_int(T x) {
    if(!x)
    {
        out_char('0');
        return;
    }
    if(x < 0) x = -x,out_char('-');
    int len = 0;
    while(x)
    {
        outtmp[len++] = x%10+48;
        x /= 10;
    }
    outtmp[len] = 0;
    for(int i = 0, j = len-1; i < j; i++,j--) swap(outtmp[i],outtmp[j]);
    out_str(outtmp);
}
const int maxn = 5e5+100;
int a[maxn],b[maxn*3];
int T,n,L;
LL calc(int st){
    LL ret =0;
    for (int i=1;i<=n;i++){
        ret +=abs(1LL*a[i]-1LL*b[st+i-1]);
    }
    return ret;
}
void solve(){
//    n = read();
//    L = read();
    in(n);
    in(L);
    for (int i=1;i<=n;i++){
        //a[i] = read();
        in(a[i]);
    }
    for (int i=1;i<=n;i++){
        //b[n+i] = read();
        in(b[n+i]);
    }
    for (int i=1;i<=n;i++){
        b[i] = b[n+i]-L;
        b[2*n+i] = b[n+i]+ L;
    }
    int l = 1,r = 2*n+1;
    while (r-l>=3){
        int lmid = l+(r-l)/3;
        int rmid = r-(r-l)/3;
        LL ansl = calc(lmid);
        LL ansr = calc(rmid);
        if (ansl<ansr){
            r = rmid;
        }else{
            l = lmid;
        }
    }
    LL ans = 0x3f3f3f3f3f3f3f3fLL;
    for (int i=l;i<=r;i++){
        ans = min(ans,calc(i));
    }
    out_int(ans);
    out_char('\n');
    //printf("%lld\n",ans);
}
int main(){
    for (in(T);T;T--){
        solve();
    }
    write();
    return 0;
}
