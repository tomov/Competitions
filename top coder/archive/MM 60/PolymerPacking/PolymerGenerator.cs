using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

class PolymerGenerator
{
    public Random rand;

    public PolymerGenerator()
    {
        rand = new Random();
    }

    public PolymerGenerator(int seed)
    {
        rand = new Random(seed);
    }

    private void SetNodeCoordinates(Polymer.Node curNode, out Polymer.Node nextNode)
    {
        nextNode.x = curNode.x + Polymer.dX[(int)curNode.nextDirection];
        nextNode.y = curNode.y + Polymer.dY[(int)curNode.nextDirection];
        nextNode.nextDirection = default(Polymer.Directions);
    }

    public int[] NextDirections(int L)
    {
        if (L < 3 || L > 500)
        {
            throw new ArgumentException("L is outside [3, 500]");
        }
        int[] directions = new int[L - 1];

        bool success;
        do
        {
            Polymer.Node[] nodes = new Polymer.Node[L + 1];
            nodes[0] = new Polymer.Node(0, 0, Polymer.Directions.East);
            nodes[1] = new Polymer.Node(1, 0, Polymer.Directions.East);
            HashSet<Polymer.Node> usedNodes = new HashSet<Polymer.Node>();
            usedNodes.Add(nodes[0]);
            usedNodes.Add(nodes[1]);
            Polymer.Node nodeLeft = new Polymer.Node();
            Polymer.Node nodeRight = new Polymer.Node();
            Polymer.Node nodeStraight = new Polymer.Node();
            success = true;
            for (int i = 2; i < L + 1; i++)
            {
                double probLeft = 0, probRight = 0, probStraight = 0;

                nodes[i - 1].nextDirection = Polymer.RotateDirectionRight(nodes[i - 2].nextDirection);
                SetNodeCoordinates(nodes[i - 1], out nodeRight);
                if (!usedNodes.Contains(nodeRight))
                {
                    probRight = 4.5;
                }

                nodes[i - 1].nextDirection = Polymer.RotateDirectionLeft(nodes[i - 2].nextDirection);
                SetNodeCoordinates(nodes[i - 1], out nodeLeft);
                if (!usedNodes.Contains(nodeLeft))
                {
                    probLeft = 4.5;
                }

                nodes[i - 1].nextDirection = nodes[i - 2].nextDirection;
                SetNodeCoordinates(nodes[i - 1], out nodeStraight);
                if (!usedNodes.Contains(nodeStraight))
                {
                    probStraight = 0.2 + rand.NextDouble();
                }

                if (probLeft + probRight + probStraight < 1e-9)
                {
                    success = false;
                    break;
                }

                if (probLeft + probRight == 4.5)
                {
                    if (probLeft == 0)
                    {
                        probRight *= 2;
                    }
                    else
                    {
                        probLeft *= 2;
                    }
                }

                double probAll = probLeft + probRight + probStraight;
                probLeft /= probAll;
                probRight /= probAll;
                probStraight /= probAll;
                double chooseDirection = rand.NextDouble();
                if (chooseDirection < probRight)
                {
                    directions[i - 2] = -1;
                    nodes[i] = nodeRight;
                    nodes[i - 1].nextDirection = Polymer.RotateDirectionRight(nodes[i - 2].nextDirection);
                }
                else
                {
                    if (chooseDirection < probLeft + probRight)
                    {
                        directions[i - 2] = 1;
                        nodes[i] = nodeLeft;
                        nodes[i - 1].nextDirection = Polymer.RotateDirectionLeft(nodes[i - 2].nextDirection);
                    }
                    else
                    {
                        directions[i - 2] = 0;
                        nodes[i] = nodeStraight;
                        nodes[i - 1].nextDirection = nodes[i - 2].nextDirection;
                    }
                }
                usedNodes.Add(nodes[i]);
            }
        } while (!success);

        return directions;
    }
}

