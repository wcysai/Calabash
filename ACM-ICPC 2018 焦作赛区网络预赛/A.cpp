#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        string str; cin >> str;
        for (char& ch : str) ch = tolower(ch);
        if (str == "jessie") cout << "Good guy!" << endl;
        else cout << "Dare you say that again?" << endl;
    }
    return 0;
}
