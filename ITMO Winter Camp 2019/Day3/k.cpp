// Gauss-Jordan elimination with full pivoting.
// Uses:
//   (1) solving systems of linear equations (AX=B)
//   (2) inverting matrices (AX=I)
//   (3) computing determinants of square matrices
//
// Running time: O(n^3)
//
// INPUT:    a[][] = an nxn matrix
//           b[][] = an nxm matrix
//           A MUST BE INVERTIBLE!
//
// OUTPUT:   X      = an nxm matrix (stored in b[][])
//           A^{-1} = an nxn matrix (stored in a[][])
//           returns determinant of a[][]

#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x)  begin(x), end(x)
typedef long long LL;
typedef unsigned long long ULL;

struct frac {
    LL x, y;
    frac(LL x = 0, LL y = 1) {
        LL g = __gcd(x, y);
        x /= g; y /= g;
        this->x = x;
        this->y = y;
    }
    
    friend frac operator + (frac lhs, frac rhs) {
        return {lhs.x * rhs.y + lhs.y * rhs.x, lhs.y * rhs.y};
    }
    
    friend frac operator - (frac lhs, frac rhs) {
        return {lhs.x * rhs.y - lhs.y * rhs.x, lhs.y * rhs.y};
    }
    
    friend frac operator * (frac lhs, frac rhs) {
        return {lhs.x * rhs.x, lhs.y * rhs.y};
    }
    
    friend frac operator / (frac lhs, frac rhs) {
        return {lhs.x * rhs.y, lhs.y * rhs.x};
    }

    int sgn() {
        if (x == 0) return 0;
        if ((x < 0) ^ (y < 0)) return -1;
        return 1;
    }

    friend bool operator < (frac lhs, frac rhs) {
        return (lhs - rhs).sgn() < 0;
    }

    friend bool operator > (frac lhs, frac rhs) {
        return (lhs - rhs).sgn() > 0;
    }
    
    friend bool operator == (frac lhs, frac rhs) {
        return (lhs - rhs).sgn() == 0;
    }
    
    friend bool operator != (frac lhs, frac rhs) {
        return (lhs - rhs).sgn() != 0;
    }
};

typedef vector<int> VI;
typedef frac T;
typedef vector<T> VT;
typedef vector<VT> VVT;

int rref(VVT &a) {
    int n = a.size();
    int m = a[0].size();
    int r = 0;
    rep (c, m) {
        int j = r;
        for (int i = r + 1; i < n; i++)
            if (a[i][c] > 0) j = i;
        if (a[j][c] == 0) continue;
        swap(a[j], a[r]);
        T s = 1 / a[r][c];
        rep (j, m) a[r][j] = a[r][j] * s;
        rep (i, n) if (i != r) {
            T t = a[i][c];
            rep (j, m) a[i][j] = a[i][j] - t * a[r][j];
        }
        r++;
    }
    return r;
}

int n, m;
string str[128];
VVT mat;
vector<char> chs;

int main() {
    while (cin >> n, n) {
        rep (i, n) cin >> str[i];
        chs.clear();
        rep (i, n) for (char ch : str[i])
            if (count(range(chs), ch) == 0)
                chs.push_back(ch);
        m = chs.size();
        mat.clear();
        rep (i, m) {
            mat.emplace_back(n + 1);
            rep (j, n) mat.back()[j] = count(range(str[i]), chs[j]);
        }

        VVT tmp;
        rep (i, n) {
            LL mult = 1;
            tmp = mat;
            tmp.emplace_back(n + 1);
            tmp.back()[i] = 1; tmp.back().back() = 1;
            int rank = rref(tmp), ru;
            vector<frac> sol(n);
            for (auto& v : tmp) {
                rep (i, n) if (v[i] != 0) {
                    sol[i] = v.back();
                    ru++;
                    goto cont;
                }
                if (v.back() != 0) goto fail;
cont:;
            }
            rep (i, n) mult *= sol[i].y;
            puts("yes");
            rep (i, n) {
                LL num = sol[i].x * (mult / sol[i].y);
                cout << str[i] << ' ';
                if (num == 0) cout << 'N' << endl;
                else {
                    if (num < 0) {
                        cout << 'R' << ' ' << -num << endl;
                        num = -num;
                    } else cout << 'L' << ' ' << num << endl;
                }
            }
            goto done;
fail:;
        }
        cout << "no" << endl;
done:;
    }
    return 0;
}
