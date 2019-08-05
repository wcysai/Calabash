#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 100;
int n;
int a[maxn];int b[maxn];
int c[maxn];
struct Trie{
    int nxt[maxn * 30][2];
    int fa[maxn*30];
    int num[maxn*30];
    int root = 1;
    int cnt = 1;
    void clear(){
        root = cnt = 1;
        memset(nxt[1],0,sizeof nxt[1]);
        num[1] = 0;
    }
    int newnode(int father){
        cnt ++;
        fa[cnt] = father;
        memset(nxt[cnt],0,sizeof nxt[cnt]);
        num[cnt] = 0;
        return cnt;
    }
    void ins(ll val){
        int now = root;
        for (int i=29;i>=0;i--){
            num[now] ++;
            int dig = (val & (1<< i)) != 0;
            if (!nxt[now][dig])nxt[now][dig] = newnode(now);
            now = nxt[now][dig];
        }
        num[now] ++;
    }
    void gao(int x){
        while (x){
            num[x] --;
            x = fa[x];
        }
    }
    pair<int,int> run(pair<ll,int> pr){
        int now = 1;
        int number = pr.first;
        int count = pr.second;
        int answer = 0;
        for (int i=29;i>=0;i--){
            int dig = (number & (1<< i)) != 0;
            if (nxt[now][dig] && num[nxt[now][dig]]){
                now = nxt[now][dig];
            }else if (nxt[now][!dig] && num[nxt[now][!dig]]){
                now = nxt[now][!dig];
                answer += 1ll << i;
            }else assert(0);
        }
        return make_pair(answer,now);
    }
}trie;
struct Node{
    int answer;
    int ori_val;
    int trie_node;
    int number;
    bool operator < (const Node &other)const{
        return other.answer < answer;
    }
};
map<int,int> Cnt;
priority_queue < Node> pq;
void solve(){
    scanf("%d",&n);
    trie.clear();
    for (int i=1;i<=n;i++){
        scanf("%d",a+i);
        trie.ins(a[i]);
    }
    Cnt.clear();
    while (!pq.empty())pq.pop();
    for (int i=1;i<=n;i++){
        scanf("%d",b+i);
        Cnt[b[i]] ++;
    }
    for (auto pr : Cnt){
        auto p = trie.run(pr);
        pq.push((Node){p.first,pr.first,p.second,pr.second});
    }
    for (int i=1;i<=n;i++){
        while (trie.num[pq.top().trie_node] == 0){
            auto node = pq.top();
            pq.pop();
            int ori_num = node.ori_val;
            int number = node.number;
            auto p = trie.run(make_pair(ori_num,number));
            pq.push((Node){p.first,ori_num,p.second,number});
        }
        c[i] = pq.top().answer;
        trie.gao(pq.top().trie_node);
        Node node = pq.top();
        if (node.number == 1)pq.pop();
        else{
            pq.pop();
            node.number --;
            pq.push(node);
        }

    }
    for (int i=1;i<=n;i++){
        printf("%d%c",c[i],i == n?'\n':' ');
    }
}
int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        solve();
    }
    return 0;
}
/*
 2
 3
 3 2 1
 4 5 6
 3
 3 2 1
 4 5 6
 */
