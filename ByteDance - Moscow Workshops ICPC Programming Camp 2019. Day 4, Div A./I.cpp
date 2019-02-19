#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, \
    ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif

#define norm afueohf

typedef long long LL;

struct pt {
    double x, y, z;
    
    void read() {
        int xx, yy, zz; scanf("%d%d%d", &xx, &yy, &zz);
        x = xx; y = yy; z = zz;
    } 
    void negate() { x = -x; y = -y; z = -z; }
    pt operator - (pt a) { return {x - a.x, y - a.y, z - a.z}; }
    pt operator * (double k) { return {x * k, y * k, z * k}; }
    pt operator * (pt a) {
        return {
            y * a.z - z * a.y, 
            z * a.x - x * a.z,
            x * a.y - y * a.x
        };
    }
    double operator , (pt a) { return x * a.x + y * a.y + z * a.z; }
    double length() { return sqrt((*this, *this)); }
    void unit() { 
        double len = length();
        x /= len; y /= len; z /= len;
    }
};

const double pi = acos(-1);
pt vx, vy, vz;

pt proj(pt plane, pt point) {
    double l = (plane, point) / plane.length();
    return point - plane * l;
}

double angle(pt point) {
//    point = proj(vz, point);
//    double lx = (point * vx).length(), ly = (point * vy).length();
//    if ((point, vx) < 0) lx = -lx;
//    if ((point, vy) < 0) ly = -ly;
    double lx = (point, vx), ly = (point, vy);
    return atan2(ly, lx);
}

int n, ans = 0;
pt norm[2048], pos[2048];
vector<double> ang;

void work() {
    sort(range(ang));
    int num = ang.size(); assert(num == n - 1);
    rep (i, num) ang.push_back(ang[i] + pi + pi); 

    int lptr = 0, rptr = lptr;
    while (lptr < num) {
        while (rptr < ang.size() and ang[rptr] - ang[lptr] < pi) 
            rptr++;
        ans = max(ans, rptr - lptr);
        lptr++;
    }
}

int main() {
    scanf("%d", &n);
    rep (i, n) {
        pos[i].read();
        norm[i].read();
        if ((norm[i], pos[i]) < 0) norm[i].negate();
    }
    rep (i, n) {
        ang.clear();
        vz = norm[i]; vx = norm[i] * norm[(i+1)%n];
        vy = vz * vx;
        vx.unit(); vy.unit(); vz.unit();
        rep (j, n) if (j != i) ang.push_back(angle(norm[j])); 
        work();
    }
    printf("%d\n", ans + 1);
    return 0;
}
