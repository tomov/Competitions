using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

class SimulatedAnnealing
{
    private Random rand;
    private Polymer initial;

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

    private Polymer Neighbor(Polymer current)
    {
        Polymer next = (Polymer)initial.Clone();
        double random = Math.Abs(NextGaussianDouble()) / 3.0;
        if (random > 1.0)
        {
            random = 1.0;
        }
        random = 1.0 - random;
        int flipId = (int)(random * (current.flips.Count + 2));
        if (flipId > current.flips.Count)
        {
            flipId = current.flips.Count;
        }
        for (int i = 0; i < flipId; i++)
        {
            next.TryFlipAt(current.flips[i]);
        }
        while (!next.TryFlipAt(rand.Next(2, next.nodes.Length - 1)))
        {
        }
        return next;
    }

    private double Temperature(double coefficient)
    {
        return (1 - coefficient) * 1000;
    }

    private double Probability(int currentArea, int nextArea, double temperature)
    {
        double probability;
        if (currentArea > nextArea)
        {
            probability = 1;
        }
        else
        {
            //Console.WriteLine(currentArea - nextArea + " / " + temperature);
            probability = Math.Exp((currentArea - nextArea) / temperature);
        }
        return probability;
    }

    public Polymer Search(Polymer initial)
    {
        this.initial = initial;
        Polymer best = (Polymer)initial.Clone();
        Polymer current = (Polymer)initial.Clone();

        int steps = 10000;
        rand = new Random(6661313);
        Console.WriteLine(initial.FlipsMaxCount);
        for (int step = 0; step < steps; step++)
        {
            Polymer neighbor = Neighbor(current);
            if (neighbor.CompareTo(best) == -1)
            {
                best = neighbor;
            }
            double temperature = Temperature((double)step / steps);
            double probability = Probability(current.Area, neighbor.Area, temperature);
            // Console.Error.WriteLine(current.Area + " " + neighbor.Area + " " + probability);
            Console.WriteLine(current.flips.Count + " " + current.Area + " " + (current.xMax - current.xMin) + " " + (current.yMax - current.yMin) + " " +
                temperature + " " + probability);
            if (probability > rand.NextDouble())
            {
                    Console.Error.WriteLine("             YES ");
                current = neighbor;
            }
            //Console.ReadKey();
        }

        return best;
    }
}

