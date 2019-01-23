#include <bits/stdc++.h>
using namespace std;
 
#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x)  begin(x), end(x)
 
int n, k;
vector<string> strs, sel;
 
int main() {
    freopen("codes.in","r",stdin);
    freopen("codes.out","w",stdout);
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> k; k++;
    for (int i = 0; i < n; i++) {
        string str; cin >> str;
        strs.push_back(str);
    }
    sort(range(strs));
    for (string& str : strs) {
        if (sel.empty() or str.size() < k or sel.back().size() < k or 
                str.substr(0, k) != sel.back().substr(0, k))
            sel.push_back(str);
    }
    cout << sel.size() << endl;
    for (string& str : sel)
        cout << str << endl;
    return 0;
}
