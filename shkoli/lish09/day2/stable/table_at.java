/**
 * Created by IntelliJ IDEA.
 * User: Toropov Alexander
 * Date: 26.10.2006
 * Time: 20:23:46
 * To change this template use File | Settings | File Templates.
 */

/**
 * Problem: "Странная таблица"
 * Fifth Internet olympiad 2006 - 2007, advanced level
 * Problem's author: Toropov Alexander, toropov@rain.ifmo.ru
 * Solution's author: Toropov Alexander, toropov@rain.ifmo.ru
 */

import java.io.*;
import java.util.*;
import java.math.BigInteger;

public class table_at
{
    private static BigInteger count(BigInteger n, BigInteger l)
    {
        BigInteger m = n.divide(l.multiply(BigInteger.valueOf(2)));
        m = m.multiply(l);
        if ((n.subtract(m.multiply(BigInteger.valueOf(2))).compareTo(l)) == -1)
            return m;
        else
            return n.subtract(m.add(l)); 
    }

    public static void main (String[] args) throws FileNotFoundException
    {
        Scanner in = new Scanner(new File("table.in"));
        PrintWriter out = new PrintWriter(new File("table.out"));

        BigInteger n = in.nextBigInteger();
        n = n.add(BigInteger.ONE);
        BigInteger m = in.nextBigInteger();
        m = m.add(BigInteger.ONE);

        BigInteger l = BigInteger.ONE;
        BigInteger c1 = BigInteger.ZERO;
        BigInteger c2 = BigInteger.ZERO;
        BigInteger answer = BigInteger.ZERO;

        for(int i = 1; i <= 64; ++i)
        {
            c1 = count(n, l);
            c2 = count(m, l);
            answer = answer.add( (c1.multiply(m.subtract(c2))).multiply(l) );
            answer = answer.add( (c2.multiply(n.subtract(c1))).multiply(l) );
            l = l.multiply(BigInteger.valueOf(2));
        }
        out.print(answer);
        in.close();
        out.close();
    }
}