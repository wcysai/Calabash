#include <bits/stdc++.h>
using namespace std; 

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x)  begin(x), end(x)
#define PROBLEM "sum"

string a, b, c, aa, bb, cc;
int n, m, k;

void ok() {
    cout << "YES" << endl;
    cout << a.size() - n << ' ' << b.size() - m << ' ' << c.size() - k 
        << endl;
    exit(0);
}

string dup0(int x) {
    string str;
    while (x--) str.push_back('0');
    return str;
}

string sub(string a, string b) {
    b = dup0(a.size() - b.size()) + b;
    int n = a.size();
    rep (i, n) a[i] -= b[i] - '0';
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] < '0') {
            a[i] += 10;
            a[i-1] --;
        }
    }
    int ptr = 0;
    while (a[ptr] == '0') ptr++;
    a = a.substr(ptr);
    return a;
}

bool iszero(const string &str) {
    for (char ch : str) if (ch != '0') return false;
    return true;
}

int main() {
    freopen("sum.in", "r", stdin);
    freopen("sum.out", "w", stdout);
    cin >> a  >> b >> c;
    aa = a, bb = b, cc = c;
    n = a.size(), m = b.size(), k = c.size();
    c += dup0(100005);
    a += dup0(c.size() - a.size());
    if (a > c) a.pop_back();
    string bp = sub(c, a);
    if (bp.size() >= b.size() and bp.substr(0, b.size()) == b and
            iszero(bp.substr(b.size()))) {
        b = bp;
        ok();
    }

    a = aa; b = bb;
    b += dup0(c.size() - b.size());
    if (b > c) b.pop_back();
    string ap =  sub(c, b);
    if (ap.size() >= a.size() and ap.substr(0, a.size()) == a and 
    	iszero(ap.substr(a.size()))) {
 		a = ap;
 		ok();
 	}   	
	cout << "NO" << endl;
    return 0;
}
