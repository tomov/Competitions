using System;
using System.Collections.Generic;
using System.Text;

class PriorityRandomSearch
{
    const int generationMaxSize = 200;

    public Polymer Search(Polymer initial)
    {
        List<Polymer> dummy = new List<Polymer>();
        return Search(initial, out dummy);
    }

    public Polymer Search(Polymer initial, out List<Polymer> nicePolymers)
    {
        Polymer best = (Polymer)initial.Clone();
        nicePolymers = new List<Polymer>();
        List<Polymer> curPolymers = new List<Polymer>();
        curPolymers.Add(initial);

        int neighborMaxCount;
        Random rand = new Random(6661313);
        int generationsCount = initial.FlipsMaxCount / 2;
        for (int generation = 0; generation < generationsCount; generation++)
        {
            /*if (DateTime.Now - PolymerPacking.StartTime > PolymerPacking.TimeLimit)
            {
                goto end;
            }*/
            Console.Error.WriteLine("-- generation {0} --- best {1}", generation, curPolymers[0].Area);
            List<Polymer> nextPolymers = new List<Polymer>();
            if (generation < 5) neighborMaxCount = 30;
            else if (generation < 10) neighborMaxCount = 15;
            else neighborMaxCount = 10;
            foreach (Polymer polymer in curPolymers)
            {
                //Console.Error.WriteLine("  from {0}", polymer);
                Polymer neighbor = (Polymer)polymer.Clone();
                //Dictionary<int, bool> usedFlipNodes = new Dictionary<int,bool>();
                for (int neighborCount = 0, attempts = 0;
                    neighborCount < neighborMaxCount && attempts < neighborMaxCount;
                    attempts++)
                {
                    int nodeId = rand.Next(2, initial.nodes.Length - 1);
                    if (neighbor.TryFlipAt(nodeId))
                    {
                        //Console.Error.WriteLine("           to {0}", neighbor);
                        if (neighbor.CompareTo(best) == -1)
                        {
                            best = neighbor;
                        }
                        nextPolymers.Add((Polymer)neighbor.Clone());
                        neighbor = (Polymer)polymer.Clone();
                        neighborCount++;
                    }
                }
            }
            nextPolymers.Sort();
            if (nextPolymers.Count > generationMaxSize)
            {
                nextPolymers.RemoveRange(generationMaxSize, nextPolymers.Count - generationMaxSize);
            }
            if (generation > 5)
            {
                for (int i = 0; i * generationsCount < Genetic.GenerationSize; i++)
                {
                    nicePolymers.Add(nextPolymers[i]);
                }
            }
            curPolymers = nextPolymers;
        }

    end: ;
        TimeSpan timePassed = DateTime.Now - PolymerPacking.StartTime;
        Console.Error.WriteLine("Time elapsed: {0}", timePassed);

        return best;
    }
}

