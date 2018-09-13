//
// Created by calabash_boy on 18-7-6.
//
#include<bits/stdc++.h>
#define F first
#define S second
#define PB(x) push_back(x)
#define debug(x) cout<<"[debug] "<<#x<<":"<<x<<endl;
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef long long ll;
const int maxn = -1;
const int MOD = -1;
const int N = 2e6+100;
char s[N], t[N];
unordered_map<ll, int> idx;
const int Seed = 146527;
vector<vector<int> > ans;
int id[N];
ll bas[N];
int n;
void print(){
    printf("%d\n", (int)ans.size());
    for (int i = 0; i < n; i ++) {
        if (id[i]){
            printf("%d", (int)ans[id[i] - 1].size());
            for (int & j : ans[id[i] - 1]){
                printf(" %d", j);
            }
            puts("");
        }
    }
}
int main() {
    scanf("%s",s);
    n = strlen(s);
    ll pw = 1;
    bas[0]=1;
    for (int i = 1; i < n; i ++){
        bas[i] = bas[i-1]*Seed;
        pw *= Seed;
    }
    strcpy(t, s);
    strcat(s, t);
    ll val = 0;
    for (int i = 0, l = 0, r = 0; i < n; i ++) {
        while (l < i) val -= pw * s[l++];
        while (r < i + n) val = val * Seed + s[r++];
        if (!idx.count(val)) {
            idx[val] = ans.size();
            ans.push_back(vector<int>());
        }
        ans[idx[val]].push_back(i);
    }
    for (int i = 0; i < (int)ans.size(); i ++){
        id[ans[i][0]] = i + 1;
    }
    print();
    return 0;
}
