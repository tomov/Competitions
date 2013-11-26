using System;
using System.Collections.Generic;
using System.Text;

public class PolymerPacking
{
    public static readonly TimeSpan TimeLimit = new TimeSpan(0, 0, 0, 9, 500);
    public static readonly DateTime StartTime = DateTime.Now;

    public double score;

    public int[] mirrorSequence(int[] directions)
    {
        Polymer state = new Polymer(directions);
        //Polymer best = new PriorityRandomSearch().Search(state);
        //Polymer best = new SimulatedAnnealing().Search(state);
        Polymer best = new Genetic().Search(state);

        //Console.Error.WriteLine(best + " flips " + best.FlipsCount + " max " + best.flipsMaxCount);

        score = (double)(best.nodes.Length - 1) / best.Area;
        int[] result = best.flips.ToArray();
        for (int i = 0; i < result.Length; i++)
        {
            result[i]--;
        }

        //Console.WriteLine("time: {0}", DateTime.Now - StartTime);
        return result;
    }
}

