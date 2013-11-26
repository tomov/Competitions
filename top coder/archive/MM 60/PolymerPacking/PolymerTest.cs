using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

class PolymerTest
{
    static void PrintDirectionsStatistics(int[] directions)
    {
        int leftCount = 0, rightCount = 0, straightCount = 0;
        foreach (int dir in directions)
        {
            switch (dir)
            {
                case -1:
                    rightCount++;
                    break;
                case 0:
                    straightCount++;
                    break;
                case 1:
                    leftCount++;
                    break;
            }
        }
        Console.Error.WriteLine("{0:F5}% right, {1:F5}% left, {2:F5}% straight",
            (double)rightCount / directions.Length * 100, (double)leftCount / directions.Length * 100,
            (double)straightCount / directions.Length * 100);
    }

    static void VisualizerSingleTest()
    {
        int n = int.Parse(Console.ReadLine());
        int[] directions = new int[n];
        for (int i = 0; i < n; i++)
        {
            directions[i] = int.Parse(Console.ReadLine());
        }
        Console.Error.WriteLine("L = {0}", n + 1);
        PrintDirectionsStatistics(directions);

        PolymerPacking polPack = new PolymerPacking();
        int[] flips = polPack.mirrorSequence(directions);

        Console.WriteLine(flips.Length);
        foreach (int flip in flips)
        {
            Console.WriteLine(flip);
        }
    }

    static void StressTest(int testsCount)
    {
        double totalScore = 0;
        PolymerGenerator gen = new PolymerGenerator(666);
        for (int test = 0; test < testsCount; test++)
        {
            int L = gen.rand.Next(100, 501);
            int[] directions = gen.NextDirections(L);
            PolymerPacking solution = new PolymerPacking();
            solution.mirrorSequence(directions);
            totalScore += solution.score;
            Console.Error.WriteLine("Total score after test {0} (L = {2}): {1}", test, totalScore / (test + 1), L);
            Console.ReadKey();
        }
        totalScore /= testsCount;
        Console.Error.WriteLine("Total score: {0}", totalScore);
    }

    static void Main(string[] args)
    {
        //VisualizerSingleTest();
        StressTest(100);
    }
}

