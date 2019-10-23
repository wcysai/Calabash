import java.math.BigInteger;
import java.util.Scanner;
 
public class Main {
    static Scanner input = new Scanner(System.in);
    static int get_dig(char ch){
        if (ch >= '0' && ch <='9') return ch - '0';
        if (ch >= 'A' && ch <= 'Z')return ch - 'A' + 10;
        if (ch >= 'a' && ch <= 'z')return ch - 'a' + 36;
        return -1;
    }
    static char get_ch(int dig){
        if (dig >= 0 && dig <= 9)return (char)('0' + dig);
        if (dig >= 10 && dig <= 35) return (char)('A' + dig - 10);
        if (dig >= 36 && dig <= 62)return (char)('a' + dig - 36);
        return '\0';
    }
    public static void main(String [] args){
        int x = input.nextInt();
        int y = input.nextInt();
        String num = input.nextLine();
        BigInteger num10 = BigInteger.ZERO;
        for (int i=1; i < num.length();i++){
            int dig = get_dig(num.charAt(i));
         //   System.out.println(dig);
            num10 = num10.multiply(BigInteger.valueOf(x)).add(BigInteger.valueOf(dig));
        }
       // System.out.println(num10);
        String ans = "";
        if (num10.compareTo(BigInteger.ZERO) == 0){
            System.out.print("0");
            return;
        }
        while (num10.compareTo(BigInteger.ZERO) > 0){
            BigInteger dig = num10.mod(BigInteger.valueOf(y));
            int digg = (int)dig.longValue();
            ans  = get_ch(digg) + ans;
            num10 = num10.divide(BigInteger.valueOf(y));
        }
        System.out.println(ans);
    }
}