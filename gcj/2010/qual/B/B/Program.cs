/*
 * Using BigInteger class that can be found at
 * http://www.codeproject.com/KB/cs/biginteger.aspx
 */

using System;
using System.Collections.Generic;
using System.Text;

namespace B
{
    class Program
    {
        static BigInteger parseBigInteger(string s)
        {
            BigInteger res = new BigInteger();
            foreach (char c in s)
            {
                res = res * 10 + (c - '0');
            }
            return res;
        }

        static void Main(string[] args)
        {
            int T = int.Parse(Console.ReadLine());
            for (int test = 1; test <= T; test++)
            {
                string[] line = Console.ReadLine().Split(' ');
                int N = int.Parse(line[0]);
                BigInteger[] events = new BigInteger[N];
                for (int i = 1; i <= N; i++)
                {
                    events[i - 1] = parseBigInteger(line[i]);
                }
                Array.Sort(events);
                BigInteger gcd = events[1] - events[0];
                for (int i = 2; i < N; i++)
                {
                    gcd = gcd.gcd(events[i] - events[0]);
                }
                BigInteger answer = gcd - (events[0] % gcd);
                if (answer == gcd)
                {
                    answer = 0;
                }
                Console.WriteLine("Case #{0}: {1}", test, answer);
            }
        }
    }
}
