#include <bits/stdc++.h>
using namespace std;

string s, ss, t;
map<char, char> mp = {
    {'A', 'T'},
    {'G', 'C'},
    {'C', 'G'},
    {'T', 'A'}
};

int main() {
    freopen("dna.in", "r", stdin);
    freopen("dna.out", "w", stdout);
    cin >> s >> t;
    for (char ch : s) ss.push_back(mp[ch]);
    reverse(ss.begin(),  ss.end());
    puts((strstr(s.c_str(), t.c_str()) != NULL or strstr(ss.c_str(), t.c_str()) != NULL) ? 
            "Yes" : "No");
    return 0;
}
