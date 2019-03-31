#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+100;
int a[maxn];
int p[maxn],q[maxn];
struct Node{
    int ddl,id,low_val;
    bool operator < (const Node& other)const{
        return other.ddl < ddl;
    }
};
int n,k;
int cnt[maxn];
inline int calc_ddl(int id,int value){
    return (1ll * q[id] * value + p[id] -1)/p[id];
}
void output(int ans){
    printf("%d\n",ans);
    exit(0);
}
void forever(){
    puts("forever");
    exit(0);
}
inline void _debug(Node node,char * message){
    cout<<message<<" ";
    cout<<"ddl = "<<node.ddl <<" id = "<<node.id<<" "<<" now_val = "<<node.low_val<<endl;
}
int main(){
    scanf("%d%d",&n,&k);
    int tot = 0;
    for (int i=0;i<n;i++){
        scanf("%d",a+i);
        tot += a[i];
    }
    for (int i=0;i<n;i++){
        int P = a[i];
        int Q = tot;
        int gcd = __gcd(P,Q);
        P /= gcd;
        Q /= gcd;
        p[i] = P;
        q[i] = Q;
    }
    for (int i=0;i<k;i++){
        int type;
        scanf("%d",&type);
        type --;
        cnt[type] ++;
    }
    priority_queue<Node> to_add;
    priority_queue<Node> waiting;
    for (int i=0;i<n;i++){
        int now_val = cnt[i];
        int ddl = calc_ddl(i,now_val+1);
        int ddl_now = calc_ddl(i,now_val);
//        cout<<"id = "<<i<<" fi = "<<p[i]<<"/"<<q[i]<<endl;
//        cout<<"id = "<<i<<" now_cnt = "<<cnt[i]<<endl;
//        cout << "id = "<<i <<" ddl_now = "<<ddl_now<<" ddl_nxt = "<< ddl<<endl;
        if (ddl_now > k){
            waiting.push((Node){ddl_now,i,now_val});
        }else{
            to_add.push((Node){ddl,i,now_val});
        }
    }
    int cnt = 0;
    int now_n = k;
    while (1){
        now_n ++;
  //      cout<<"now_n = "<<now_n<<endl;
        vector<Node> two_val(0),single_val(0);
        while (!waiting.empty() && waiting.top().ddl <= now_n){
            auto tmp = waiting.top();
            Node nxt = (Node){calc_ddl(tmp.id,tmp.low_val+1),tmp.id,tmp.low_val};
            if (now_n % q[tmp.id] == 0){
                //single_val
                single_val.push_back(nxt);
            }else{
                //double_val
                two_val.push_back(nxt);
            }
            //_debug(tmp,"waiting -> to_add");
            //to_add.push((Node){calc_ddl(tmp.id,tmp.low_val + 1),tmp.id,tmp.low_val});
            waiting.pop();
        }
        for (auto node : two_val){
            to_add.push(node);
        }
        if (to_add.empty()){
//            cout<<"to_add is empty"<<endl;
            output(now_n - k - 1);
        }
        int flag = false;
        while (!to_add.empty()){
            auto tmp = to_add.top();
//            _debug(tmp,"to_add -> add");
            if (flag && tmp.ddl > now_n)break;
            if (tmp.ddl < now_n){
                output(now_n - k - 1);
            }else if (tmp.ddl == now_n){
                if (flag == true){
                    output(now_n - k - 1);
                }else{
                    flag = true;
                    to_add.pop(); 
                    to_add.push((Node){calc_ddl(tmp.id,tmp.low_val+2),tmp.id,tmp.low_val+1});
                }
            }else if (tmp.ddl > now_n){
                to_add.pop();
                waiting.push((Node){calc_ddl(tmp.id,tmp.low_val+1),tmp.id,tmp.low_val+1});
                break;
            }
        }
        for (Node node : single_val){
            to_add.push(node);
        }
        if (now_n % tot== 0) forever();
    }
    
    return 0;
}
/*
id = 0 fi = 1/10
id = 0 now_cnt = 1
id = 0 ddl_now = 20 ddl_nxt = 30
id = 1 fi = 1/20
id = 1 now_cnt = 1
id = 1 ddl_now = 20 ddl_nxt = 40
id = 2 fi = 3/10
id = 2 now_cnt = 1
id = 2 ddl_now = 20 ddl_nxt = 24
id = 3 fi = 3/20
id = 3 now_cnt = 0
id = 3 ddl_now = 20 ddl_nxt = 27
id = 4 fi = 1/4
id = 4 now_cnt = 2
id = 4 ddl_now = 20 ddl_nxt = 24
id = 5 fi = 3/20
id = 5 now_cnt = 0
id = 5 ddl_now = 20 ddl_nxt = 27
now_n = 6
to_add is empty
0
*/
