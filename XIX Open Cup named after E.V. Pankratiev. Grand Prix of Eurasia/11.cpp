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

const double PI = acos(-1);


int main(){
    int t; scanf("%d", &t);
    while (t--) {
        double alpha, phi;
        int h, m, s;
        scanf("%lf%lf", &alpha, &phi);
        scanf("%d:%d:%d", &h, &m, &s);
        /*
        phi *= Pi / 180; alpha *= PI / 180;
        cout << gao(phi, alpha) << endl;
        continue;
        */
        if (phi >= alpha) h += 6;
        else {
            double theta = asin(tan(phi / 180 * PI) / tan(alpha / 180 * PI));
            // printf("%f\n", theta);
            theta /= PI / 2;
            theta *= 6 * 3600;
            s += theta;
        }
        m += s / 60; s %= 60;
        h += m / 60; m %= 60;
        h %= 24;
        printf("%02d:%02d:%02d\n", h, m, s);
    }

    return 0;
}
