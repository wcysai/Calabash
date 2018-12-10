//package main;
import java.math.BigInteger;
import java.util.Scanner;

import static java.lang.Math.min;

public class Main {
    public static Scanner input = new Scanner(System.in);
    public static long mod = 998244353;
    public static boolean check(int bas,BigInteger top){
        BigInteger biggest = BigInteger.ZERO;
        for (int i=bas-1;i>=0;i--){
            biggest = biggest.multiply(BigInteger.valueOf(bas)).add(BigInteger.valueOf(i));
        }
        if (biggest.compareTo(top)<=0)return true;
        else return false;
    }

    public static long fac[] = new long [1700];
    public static boolean used[] = new boolean[1700];
    public static int dig[] = new int [1700];
    public static int calc(int now,long base){
        if (now == 0)return 1;
        long ans =0;
        long top= dig[now];
        for (int i=0;i<top;i++){
            if (used[i] || (now == base && i == 0))continue;
            ans = ans + fac[now-1];
        }
        if (top < base && used[(int)top] == false && (now == base && top !=0 || now != base)){
            used[(int)top] = true;
            ans = ans + calc(now-1,base);
        }
        return (int)(ans%mod);
    }
    public static BigInteger BASE;
    public static void basInit(BigInteger n,int base){
        BASE = BigInteger.valueOf(base);
        for (int i=1;i<=base;i++){
            dig[i] = (int)n.mod(BASE).longValue();
            n = n.divide(BASE);
        }
    }
    public static int calc(BigInteger n){
        if (n.compareTo(BigInteger.ONE) <= 0)return 0;
        int l = 2,r = 1600;
        while (r-l>1){
            int mid = (l+r )>>1;
            if (check(mid,n)){
                l = mid;
            }else{
                r = mid;
            }
        }
        int fullbase = -1;
        for (int i=l;i<=r;i++)if (check(i,n))fullbase = i;
        long ans = 0;
        for (int i=2;i<=fullbase;i++){
            ans = ans + (i-1) * fac[i-1];
        }
        fullbase ++;
        for (int i=0;i<fullbase;i++)used[i] = false;
        basInit(n,fullbase);
        ans =  ans + calc(fullbase,fullbase);
        return (int)(ans%mod);
    }
    public static void main(String args[]){
        BigInteger L = input.nextBigInteger(),R = input.nextBigInteger();
        fac[0] = 1;
        for (int i=1;i<1600;i++){
            fac[i] = fac[i-1] * i % mod;
        }
        System.out.println((calc(R) - calc(L.add(BigInteger.valueOf(-1)) )+mod)%mod);
    }
}
/*
340546051
 */
