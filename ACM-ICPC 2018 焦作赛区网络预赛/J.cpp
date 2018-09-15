#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL;

namespace residue {
    typedef LL ll;
    ll pow_mod(ll a,ll i,ll m)
    {
        ll s=1;
        while(i)
        {
            if(i&1) s=s*a%m;
            a=a*a%m;
            i>>=1;
        }
        return s;
    }
    ll test(ll n,ll p)
    {
        if(p==2) return (n&1)?1:-1;
        if(pow_mod(n,p>>1,p)!=1) return -1;
        if(p&2) return pow_mod(n,(p+1)>>2,p);
        int s=__builtin_ctzll(p^1);
        ll q=p>>s,z=2;
        for(;pow_mod(z,p>>1,p)==1;++z);
        ll c=pow_mod(z,q,p),r=pow_mod(n,(q+1)>>1,p),t=pow_mod(n,q,p),tmp;
        for(int m=s,i;t!=1;)
        {
            for(i=0,tmp=t;tmp!=1;++i) tmp=tmp*tmp%p;
            for(;i<--m;) c=c*c%p;
            r=r*c%p;c=c*c%p;t=t*c%p;
        }
        return r;
    }
}

const LL primes[] = {
    954854573, 967607731, 973215833,
    975831713, 978949117, 980766497,
    983879921, 985918807, 986608921,
    991136977, 991752599, 997137961,
    1003911991, 1009775293, 1012423549,
    1021000537, 1023976897, 1024153643,
    1037027287, 1038812881, 1044754639,
    1045125617, 1047411427, 1047753349,
};

bool testsrc(const char *str) {
    for (LL p : primes) {
        LL r = 0;
        for (int i = 0; str[i]; i++) {
            r = r * 10 + str[i] - '0';
            r %= p;
        }
        if (r == 0) continue;
        if (residue::test(r, p) < 0) return false;
    }
    return true;
}

bool testsum(const char *str) {
    for (LL p : primes) {
        LL r = 0;
        for (int i = 0; str[i]; i++) {
            r = r * 10 + str[i] - '0';
            r %= p;
        }
        r = r * (r - 1 + p) % p;
        r = r * ((p + 1) / 2) % p;
        if (r == 0) continue;
        if (residue::test(r, p) < 0) return false;
    }
    return true;
}

char num[256];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%s", num);
        int res = 0;
        if (testsrc(num)) res |= 1;
        if (testsum(num)) res |= 2;
        switch (res) {
            case 0:
                puts("League of Legends");
                break;
            case 1:
                puts("Hearth Stone");
                break;
            case 2:
                puts("Clash Royale");
                break;
            case 3:
                puts("Arena of Valor");
                break;
        }
    }
    return 0;
}
