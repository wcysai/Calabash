import java.math.BigInteger;
import java.util.Scanner;
 
public class Main{
    static Scanner input = new Scanner(System.in);
    static int n;
    static final int maxn = 4005;
    static int[][] mask = new int[maxn][16];
    static int[] fa = new int[maxn],d = new int[maxn];
    static String s;
    static int[] queue = new int[maxn];
    static int[][] son = new int[maxn][2];
    static int l,r;
    static int[] sz = new int[maxn];
    static BigInteger[] bas = new BigInteger[maxn];
    static BigInteger[][] dp = new BigInteger[maxn][2];
    static int[][] opt = new int[2][2];
    static BigInteger[] L = new BigInteger[2];
    static BigInteger[] R = new BigInteger[2];
    static BigInteger[] temp_res = new BigInteger[2];
    static int Cas =1;
    public static void update(int u,int k){
        int lson = son[u][0];
        int rson = son[u][1];
        opt[0][0] = k&1;
        opt[0][1] = (k&2)>>1;
        opt[1][0] = (k&4)>>2;
        opt[1][1] = (k&8)>>3;
        for (int i=0;i<2;i++){
            for (int j=0;j<2;j++){
                BigInteger L1,L0,R1,R0;
                if (i==0){
                    L[0] = dp[lson][0];
                    L[1] = bas[sz[lson]].add(L[0].multiply(BigInteger.valueOf(-1)));
                }else{
                    L[1] = dp[lson][1];
                    L[0] = bas[sz[lson]].add(L[1].multiply(BigInteger.valueOf(-1)));
                }
                if (j==0){
                    R[0] = dp[rson][0];
                    R[1] = bas[sz[rson]].add(R[0].multiply(BigInteger.valueOf(-1)));
                }else{
                    R[1] = dp[rson][1];
                    R[0] = bas[sz[rson]].add(R[1].multiply(BigInteger.valueOf(-1)));
                }
                temp_res[0] = BigInteger.ZERO;
                temp_res[1] = BigInteger.ZERO;
                for (int ii=0;ii<2;ii++){
                    for (int jj=0;jj<2;jj++){
                        temp_res[opt[ii][jj]] = temp_res[opt[ii][jj]].add(L[ii].multiply(R[jj]));
                    }
                }
                for (int ii =0;ii<2;ii++){
                    if (dp[u][ii].compareTo(temp_res[ii])==-1){
                        dp[u][ii] = temp_res[ii].add(BigInteger.ZERO);
                    }
                }
            }
        }
    }
    public static void solve(){
        n = input.nextInt();
        s = input.nextLine();
        for (int i=1;i<n;i++){
 
            s = input.nextLine();
            for (int j =0;j<16;j++){
                mask[i][j] = (int)s.charAt(j)-'0';
            }
        }
        for (int i=1;i<=2*n-1;i++){
            d[i] = 0;
            sz[i] =0;
            son[i][0] = 0;
            son[i][1] = 0;
            dp[i][0] = BigInteger.ZERO;
            dp[i][1] = BigInteger.ZERO;
        }
        for (int i=1;i<=2*n-2;i++){
            fa[i+1] = input.nextInt();
            d[fa[i+1]]++;
            son[fa[i+1]][d[fa[i+1]]-1] = i+1;
        }
        l =0;r=0;
        for (int i=1;i<=2*n-1;i++){
            if (d[i]==0){
                queue[r] = i;
                r++;
                sz[i]=1;
                dp[i][0] = BigInteger.ONE;
                dp[i][1] = BigInteger.ONE;
            }
        }
        while (r>l){
            int head = queue[l];
            l++;
            if (fa[head]!=0){
                sz[fa[head]]+= sz[head];
                d[fa[head]]--;
                if (d[fa[head]]==0){
                    for (int i=0;i<16;i++){
                        if (mask[fa[head]][i]==1){
                            update(fa[head],i);
                        }
                    }
                    queue[r] = fa[head];
                    r++;
                }
            }
 
        }
        System.out.println("Case #"+Cas+": "+dp[1][1]);
        Cas++;
    }
    static void init(){
        bas[0] = BigInteger.ONE;
        for (int i=1;i<maxn;i++){
            bas[i] = bas[i-1].multiply(BigInteger.valueOf(2));
        }
    }
    public static void main(String args[]){
        init();
        int T = input.nextInt();
        while ((T--)!=0){
            solve();
        }
    }
}
/*
2
2
0000000010000010
1 1
3
0000000010000010
0000000010000011
1 1 2 2
 
 
1
3
0000000010000010
0000000010000011
1 1 2 2
 
 */
