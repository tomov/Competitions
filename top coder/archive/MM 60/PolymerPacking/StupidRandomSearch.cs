using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

class StupidRandomSearch
{
    public Polymer Search(Polymer state)
    {
        Polymer best = (Polymer)state.Clone();
        Random rand = new Random(34534);
        for (int i = 0; i < 300; i++)
        {
            int attempts;
            for (attempts = 0; attempts < 500; attempts++)
            {
                int id = rand.Next(2, state.nodes.Length);
                if (state.TryFlipAt(id))
                {
                    if (state.flips.Count > state.FlipsMaxCount)
                    {
                        state.TryFlipAt(id);
                    }
                    else
                    {
                        break;
                    }
                }
            }
            if (attempts == 500)
            {
                break;
            }
            if (state.Area < best.Area)
            {
                best = (Polymer)state.Clone();
            }
        }
        return best;
    }
}

