//
// Created by calabash on 10/29/18.
//
#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;
const int maxn = 180000;
int word[maxn];

//typedef array<short, 26> Node;

struct Node{
    short cnt[26];
    bool operator < (const Node& other)const{
        return lexicographical_compare(cnt, cnt + 26, other.cnt, other.cnt + 26);
    }
};


int d[maxn];
vector<int> E[maxn];
map<Node, int> ID;
int cnt;
pair<int, int> nxt[maxn];
char s[maxn][50];
int len[maxn];
char query[maxn][50];

Node str2Node(const char *s){
    Node node;
    memset(node.cnt,0,sizeof node.cnt);
    int len = strlen(s);
    for (int i=0;i<len;i++){
        int id = s[i] - 'a';
        node.cnt[id] ++;
    }
    return node;
}
void solve(const char * s){
    int Len = strlen(s);
    if (Len == 1){
        printf("2\n%s -> .\n",s);
        return;
    }
    Node node = str2Node(s);
    int now = ID[node];
    assert(now !=0);
    now = nxt[now].second;
    int cnt =1;
    int Now = now;
    while (now){
        cnt ++;
        if (len[word[now]] == 1){
            cnt++;
        }
        now = nxt[now].second;
    }
    printf("%d\n",cnt);
    now = Now;
    printf("%s",s);
    while (now){
        printf(" -> %s",::s[word[now]]);
        if (len[word[now]] == 1){
            printf(" -> .");
        }
        now = nxt[now].second;
    }
    puts("");
}

int main(){
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
        scanf("%s",&query[i][0]);
    }
    int m;
    scanf("%d",&m);
    //int max_len = 0;
    for (int i=1;i<=m;i++){
        scanf("%s",&s[i][0]);
        len[i] = strlen(s[i]);
        //max_len = max(max_len,len[i]);
        Node node = str2Node(s[i]);
        if (ID.find(node) == ID.end()){
            ID[node] = ++cnt;
            word[cnt] = i;
        }
    }
    //cout<<"max_len = "<<max_len<<endl;
    for (auto pr : ID){
        Node node = pr.first;
        int u = pr.second;
        for (int i=0;i<26;i++){
            node.cnt[i] ++;
            if (ID.find(node) == ID.end()){
                node.cnt[i] --;
                continue;
            }
            int id = ID[node];
            node.cnt[i] --;
            E[u].push_back(id);
            d[id]++;
        }
    }
    queue<int>Q;
    for (int i=1;i<=cnt;i++){
        if (d[i] == 0){
            Q.push(i);
        }
    }
    while (!Q.empty()){
        int head = Q.front();
        Q.pop();
        for (int v : E[head]){
            d[v] --;
            if (nxt[v].first < nxt[head].first +1){
                nxt[v] = {nxt[head].first+1,head};
            }
            if (d[v] == 0){
                Q.push(v);
            }
        }
    }
    for (int i=1;i<=n;i++){
        solve(query[i]);
    }
    return 0;
}
/*
 1
aba
3
a
aa
aah
 */
