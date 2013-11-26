using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

class Genetic
{
    public const int GenerationsCount = 40;
    public const int GenerationSize = 500;
    public const int SelectionSize = 200;
    const double MutationProbability = 0.05;

    private Polymer initial;
    private Random rand;

    private double NextGaussianDouble()
    {
        double x1, x2, w, y1, y2;
        do
        {
            x1 = 2.0 * rand.NextDouble() - 1.0;
            x2 = 2.0 * rand.NextDouble() - 1.0;
            w = x1 * x1 + x2 * x2;
        } while (w >= 1.0);
        w = Math.Sqrt((-2.0 * Math.Log(w)) / w);
        y1 = x1 * w;
        y2 = x2 * w;
        return y1;
    }

    private Polymer Crossover(Polymer mother, Polymer father)
    {
        Polymer child = (Polymer)initial.Clone();
        for (int i = 0; i < mother.flips.Count; i++)
        {
            if (MutationProbability > rand.NextDouble())
            {
                while (!child.TryFlipAt(rand.Next(0, child.nodes.Length)))
                {
                }
            }
            else
            {
                bool flipIsFromFather = false;
                if (rand.NextDouble() > 0.5 && i < father.flips.Count)
                {
                    if (child.TryFlipAt(father.flips[i]))
                    {
                        flipIsFromFather = true;
                    }
                }
                if (!flipIsFromFather)
                {
                    child.TryFlipAt(mother.flips[i]);
                }
            }// break if unsuccessful mother flip; different probability
        }
        if (child.flips.Count < child.FlipsMaxCount && MutationProbability > rand.NextDouble())
        {
            while (!child.TryFlipAt(rand.Next(0, child.nodes.Length)))
            {
            }
        }
        if (child.Area < mother.Area || child.Area < father.Area || 10 > rand.Next(0, 20))
        {
            /*
            Console.Write("Mother: ");
            foreach (int node in mother.flips)
            {
                Console.Write("{0} ", node);
            }
            Console.WriteLine(": {0}", mother.Area);
            Console.Write("Father: ");
            foreach (int node in father.flips)
            {
                Console.Write("{0} ", node);
            }
            Console.WriteLine(": {0}", father.Area);
            Console.Write("Child: ");
            foreach (int node in child.flips)
            {
                Console.Write("{0} ", node);
            }
            Console.WriteLine(": {0}", child.Area);
            Console.ReadKey();*/
            return child;
        }
        return null;
    }

    private List<Polymer> NextGeneration(List<Polymer> generation)
    {
        generation.Sort();
        List<int> selection = new List<int>(); // hashset
        while (selection.Count < SelectionSize)
        {
            int individualId = (int)(NextGaussianDouble() * generation.Count); // too slow? roulette wheel?
            selection.Add(individualId);
        }
        List<Polymer> nextGeneration = new List<Polymer>();
        while (nextGeneration.Count < GenerationSize)
        {
            int motherId = rand.Next(0, selection.Count);
            int fatherId = rand.Next(0, selection.Count); // do not repeat
            Polymer child = Crossover(generation[motherId], generation[fatherId]);
            if (child != null)
            {
                nextGeneration.Add(child);
                Console.Write(child.Area + " ");
            }
        }
        return nextGeneration;
    }

    public Polymer Search(Polymer initial)
    {
        this.initial = initial;
        rand = new Random(6661313);

        List<Polymer> generation;
        Polymer best = new PriorityRandomSearch().Search(initial, out generation);

        for (int g = 0; g < GenerationsCount; g++)
        {
            double averageArea = 0;
            foreach (Polymer individual in generation)
            {
                averageArea += individual.Area;
                if (individual.CompareTo(best) == -1)
                {
                    best = individual;
                }
            }
            averageArea /= generation.Count;
            Console.WriteLine(" generation {0}: avg area {1}; best {2}", g, averageArea, best.Area);
            generation = NextGeneration(generation);
        }

        return best;
    }
}

