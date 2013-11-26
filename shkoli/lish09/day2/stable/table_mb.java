import java.util.*;
import java.math.*;
import java.io.*;

public class table_mb {
    static long howMuch1(long max, int bit) {
        long mask1 = (1L << bit);
        long mask2 = mask1 + (mask1 - 1);
        long nonmask = ~mask2;
        long rv = (max & nonmask) / 2 + ((max & mask1) == 0 ? 0 : 1 + (max & (mask1 - 1)));
        return rv;
    }

    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("table.in"));
        PrintWriter out = new PrintWriter("table.out");

        long n = in.nextLong(), m = in.nextLong();

        BigInteger ans = BigInteger.ZERO;

        for (int i = 0; i < 64; i++) {
            long b1 = howMuch1(n, i), b2 = howMuch1(m, i);
            BigInteger xor = BigInteger.valueOf(b1).multiply(BigInteger.valueOf(m - b2 + 1)).add(
                             BigInteger.valueOf(b2).multiply(BigInteger.valueOf(n - b1 + 1)));
            ans = ans.add(xor.shiftLeft(i));
        }

        out.println(ans);

        out.close();
        in.close(); 
    }
}