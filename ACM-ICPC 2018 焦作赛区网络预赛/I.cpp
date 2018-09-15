#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b, c;
    while (cin >> a >> b >> c) {
        if ((a & 1) and (b & 1) and (c & 1)) {
            cout << "No" << endl;
        } else {
            cout << "Yes" << endl;
        }
    }
    return 0;
}
