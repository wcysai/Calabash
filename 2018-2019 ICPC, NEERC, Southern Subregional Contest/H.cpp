#pragma  GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef long double db;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int inf = 0x3f3f3f3f;

#define PB(x) push_back(x)
#define rep(i,l,r) for (ll i = l,_ = r;i< _;i++)
#define REP(i,l,r) for (ll i=l,_=r;i<=_;i++)
#define leave(x) do {cout<<#x<<endl;fflush(stdout);return 0;}while (0);
#define untie do{ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);}while (0)

/************* header ******************/

const int maxn = 6e4*16;
inline int get_id(char ch){
    if (ch == '.')return 26;
    if (ch >='a' && ch <= 'z')return ch - 'a';
    return 27 + ch - '0';
}
struct Aho_Corasick_Automaton{
    //basic
    int nxt[maxn][37],fail[maxn];
    int root,tot;
    //special
    int flag[maxn];
    int len[maxn];
    int cnt[maxn];
    int label[maxn];
    void clear(){
        memset(nxt[0],0,sizeof nxt[0]);
        root = tot=0;
    }
    int newnode(){
        tot++;
        memset(nxt[tot],0,sizeof nxt[tot]);
        flag[tot] = len[tot]=0;
        return tot;
    }
    void insert(string str,int Label){
        int now = root;
        for (int i=0;i<str.size();i++){
            int id = get_id(str[i]);
            if(!nxt[now][id]){
                nxt[now][id] = newnode();
            }
            len[nxt[now][id]] = len[now]+1;
            now = nxt[now][id];
        }
    }
    void build(){
        fail[root] = root;
        queue<int>Q;
        Q.push(root);
        while (!Q.empty()){
            int head = Q.front();Q.pop();
            for (int i=0;i<37;i++){
                if(!nxt[head][i])continue;
                int temp = nxt[head][i];
                fail[temp] = fail[head];
                while (fail[temp]&&!nxt[fail[temp]][i]){
                    fail[temp] = fail[fail[temp]];
                }
                if(head&&nxt[fail[temp]][i])fail[temp] = nxt[fail[temp]][i];
                Q.push(temp);
            }
        }
    }
    void search(string &str,int QID);
    pair<int,string> query(string &str);
}acam;
int n;
int q;
string query[50005];
string s[10005];
void Aho_Corasick_Automaton::search(string &str, int QID) {
    int now = root;
    for (int i=0;i< str.size();i++){
        int id = get_id(str[i]);
        now = nxt[now][id];
        int temp = now;
        while (temp != root && flag[temp] != QID){
            //cerr<<temp<<" +1"<<endl;
            flag[temp] = QID;
            cnt[temp] ++;
            label[temp] = QID;
            temp = fail[temp];
        }
    }
}
pair<int,string> Aho_Corasick_Automaton::query(string &str){
    int now = root;
    for (int i=0;i<str.size();i++){
        int id = get_id(str[i]);
        now = nxt[now][id];
        //cerr<<now<<endl;
    }
    //cerr<<endl;
    pair<int,string> res;
    res.first = cnt[now];
    if (label[now]){
        res.second = s[label[now]-1];
    }else{
        res.second = "-";
    }
    return res;
}
