import java.io.*;
import java.math.BigInteger;
import java.util.*;

public class table_rs implements Runnable {
    private Scanner in;
    private PrintWriter out;
    
    private int calcSetBit(int n, int k) {
        if (n < (1 << k))
            return 0;
        
        if (n < (1 << (k + 1))) {
            return n - (1 << k) + 1;
        }
        
        int z = n >> (k + 1);
        return (z << k) + calcSetBit(n - (z << (k + 1)), k);
    }

    private int calcNotSetBit(int n, int k) {
        return (n + 1) - calcSetBit(n, k);
    }

    private void solve() throws IOException {
        in = new Scanner(new File("table.in"));
        out = new PrintWriter(new File("table.out"));
        
        int n = in.nextInt();
        int m = in.nextInt();
        BigInteger answer = BigInteger.ZERO;
        for (int i = 0; i < 31; i++) {
            long u1 = calcSetBit(n, i);
            long v1 = calcNotSetBit(n, i);
            long u2 = calcSetBit(m, i);
            long v2 = calcNotSetBit(m, i);
            
            long cur = u1 * v2 + u2 * v1;
            answer = answer.add(BigInteger.valueOf(cur).shiftLeft(i));
        }
        
        out.println(answer);
        in.close();
        out.close();
    }

    public static void main(String[] args) {
        new Thread(new table_rs()).start();
    }

    public void run() {
        try {
            solve();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
