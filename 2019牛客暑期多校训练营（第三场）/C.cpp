#include <bits/stdc++.h>
using namespace std ;
#define ll long long
#define f(i, x, n) for (int i = x; i < (int)(n); ++i)
  
int const N = 600000;
int x[N << 1], lst[N + 2], n, m, nxt[N << 1];
vector<int> fr;
bool vis[N + 1];
  
void no() { assert(1); }
  
int getFr(){
    if (fr.empty())no();
    int an = fr.back();
    fr.pop_back();
    return an;
}
  
bool fix(vector<int> &v){
    if (v.size() < 3)return false;
    int a = v[v.size() - 3], b = v[v.size() - 2], c = v.back();
    if (x[b] == 0)return false;
    if (x[a] == 0 && x[c] == 0)return false;
    if (x[a] != 0 && x[c] != 0 && x[a] != x[c])return false;
    x[a] = x[c] = max(x[a], x[c]);
    v.pop_back();
    v.pop_back();
    return true;
}
  
bool fixy(vector<int> &v){
    if (fix(v))return true;
    if (v.size() < 3)return false;
    int a = v[v.size() - 3], b = v[v.size() - 2], c = v.back();
    if (x[a] != 0 || x[b] != 0 || x[c] == 0)return false;
    x[a] = x[c];
    x[b] = getFr();
    v.pop_back();
    v.pop_back();
    return true;
}
  
pair<int, int> getOdd(vector<int> const &v){
    for (int i = v.size() - 2; i >= 0; i -= 2)if (x[v[i]] != 0)return make_pair(x[v[i]], i);
    return make_pair(getFr(), -1);
}
  
void pl(){
    f(i, 1, n + 1)lst[i] = 0;
    f(i, 0, m)if (x[i]){
        nxt[i] = i;
        int t = lst[x[i]] - 1;
        lst[x[i]] = i + 1;
        if (t == -1)continue;
        nxt[t] = i;
    }
}
  
void go(int l, int r){
    vector<int> v(1, l);
    int i = l + 1;
    while (i <= r){
        if (i != r && nxt[i] > r)no();
        if (i != r && nxt[i] > i)go(i, nxt[i]), i = nxt[i];
        else {
            v.push_back(i);
            while (fix(v));
            ++i;
        }
    }
    while (v.size() > 1){
        while (fixy(v));
        if (v.size() == 1)break;
        if (x[v.back()] == n + 1){
            f(i, 0, m)if (x[i] == n + 1)x[i] = x[v[v.size() - 3]];
            if (x[v[v.size() - 2]] == 0)x[v[v.size() - 2]] = getFr();
            fix(v);
            continue;
        }
        if (x[v[v.size() - 2]] != 0)no();
        pair<int, int> od = getOdd(v);
        if (od.second == -1)od.second = v.size() - 2;
        for (int i = od.second; i < (int)v.size(); i += 2)x[v[i]] = od.first;
        int t = v.back();
        v.pop_back();
        while ((int)v.size() > od.second + 1){
            if (x[v.back()] == 0)x[v.back()] = getFr();
            v.pop_back();
        }
        while (fix(v));
        v.push_back(t);
    }
}
int T;
int main(){
    scanf("%d",&T);
    while(T--) {
    scanf("%d", &n);
    m = (n << 1) - 1;
    fr.clear();
    f(i, 0, m)
    {
        scanf("%d", x + i);
        if(x[i]==-1) x[i]=0;
    }
    x[0]=1;
    if (x[0] != 0 || x[m - 1] != 0){
        int z = max(x[0], x[m - 1]);
        if (x[0] == 0)x[0] = z;
        if (x[m - 1] == 0)x[m - 1] = z;
        if (x[0] != x[m - 1])no();
    }
    f(i,0,m+1) vis[i]=false;
         
    f(i,0,m+1) nxt[i]=0;
    f(i, 0, m)vis[x[i]] = true;
    f(i, 1, n + 1)if (!vis[i])fr.push_back(i);
    if (x[0] == 0)x[0] = x[m - 1] = n + 1;
    pl();
    int i = 0;
    while (nxt[i] != i)go(i, nxt[i]), i = nxt[i];
    f(i, 0, m)if (x[i] == n + 1){
        int t = getFr();
        f(i, 0, m)if (x[i] == n + 1)x[i] = t;
        break;
    }
    printf("%d", x[0]);
    f(i, 1, m)printf(" %d", x[i]);
    printf("\n");
    }
}
