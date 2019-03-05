#include <bits/stdc++.h>
using namespace std;
const int maxn = 60;
char s[maxn];
int n;
vector<pair<int,int> > blocks;
const int STEPP = 1000;
int STEP =1000;
inline int get_step(){
    return STEP + rand() % 15;
}
pair<int,int> get_nxt(pair<int,int> now,char ori){
    if (ori == 'L'){
        pair<int,int> nxt = make_pair(-0x3f3f3f3f,now.second);
        for (pair<int,int> b : blocks){
            if (b.second == now.second && b.first < now.first){
                nxt.first = max(nxt.first,b.first+ 1);
            }
        }
        return nxt;
    }else if (ori == 'R'){
        pair<int,int> nxt = make_pair(0x3f3f3f3f,now.second);
        for (pair<int,int> b : blocks){
            if (b.second == now.second && b.first > now.first){
                nxt.first = min(nxt.first,b.first- 1);
            }
        }
        return nxt;
    }else if (ori == 'U'){
        pair<int,int> nxt = make_pair(now.first,0x3f3f3f3f);
        for (pair<int,int> b : blocks){
            if (b.first == now.first && b.second > now.second){
                //cout<<"here" << b.first<<","<<b.second<<endl;
                nxt.second = min(nxt.second,b.second - 1);
            }
        }
        return nxt;
    }else if (ori == 'D'){
        pair<int,int> nxt = make_pair(now.first,-0x3f3f3f3f);
        for (pair<int,int> b : blocks){
            if (b.first == now.first && b.second < now.second){
                nxt.second = max(nxt.second,b.second + 1);
            }
        }
        return nxt;
    }else assert(0);
}
bool ok(pair<int,int> start_pos){
    return true;
}
bool check(){
    STEP = STEPP;
    blocks.clear();
    pair<int,int> now = make_pair(0,0);
    for (int i=0;i<n;i++){
        //cout<<"now = "<<now.first <<","<<now.second<<endl;
        pair<int,int> nxt = now;
        if (s[i] == 'L'){
            nxt.first -= get_step();
        }else if (s[i] == 'R'){
            nxt.first += get_step();
        }else if (s[i] == 'U'){
            nxt.second += get_step();
        }else if (s[i] == 'D'){
            nxt.second -= get_step();
        }else assert(0);
        //cout<<"add "<<nxt.first<<","<<nxt.second<<endl;
        blocks.push_back(nxt);
        now = get_nxt(now,s[i]);
        
        STEP += STEPP * 2;
    }
    if (ok(make_pair(0,0))){
        //for (pair<int,int> b : blocks){
        //    printf("[debug] %d %d\n",b.first,b.second);
        //}
        //cout<<now.first<<" "<<now.second<<endl;
        pair<int,int> endpos = blocks.back();
        blocks.pop_back();
        printf("%d %d\n",-endpos.first,-endpos.second);
        printf("%d\n",blocks.size());
        for (pair<int,int> b : blocks){
//            printf("[debug] %d %d\n",b.first,b.second);
            printf("%d %d\n",b.first - endpos.first,b.second - endpos.second);
        }
        return true;
    }
    return false;
}
char get_op(char ori){
    if (ori =='L')return 'R';
    if (ori == 'R')return 'L';
    if (ori == 'U')return 'D';
    if (ori == 'D')return 'U';
    assert(0);
}
int main(){
    scanf("%s",s);
    n = strlen(s);
    if (n >= 3){
        if (s[n-1] == s[n-3] && s[n-2] == get_op(s[n-1])){
            puts("impossible");
            return 0;
        }
    }
    for (int i=1;i<n;i++){
        if (s[i] == s[i-1]){
            puts("impossible");
            return 0;
        }
    }
    for (int i=0;i<100;i++){
        if (check())return 0;
    }

    puts("impossible");
    return 0;
}
