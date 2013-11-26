using System;
using System.Collections.Generic;
using System.Text;

class Polymer : ICloneable, IComparable
{
    /*
     * Constants
     */

    public static readonly int[] dX = { 1, 0, -1, 0 };
    public static readonly int[] dY = { 0, 1, 0, -1 };

    /* 
     * Inner types
     */

    public enum Directions { East, North, West, South };

    public struct Node
    {
        public int x, y;
        public Directions nextDirection;

        public Node(int x, int y, Directions nextDirection)
        {
            this.x = x;
            this.y = y;
            this.nextDirection = nextDirection;
        }

        public override bool Equals(object obj)
        {
            if (!(obj is Node))
            {
                return false;
            }
            Node node = (Node)obj;
            return this.x == node.x && this.y == node.y;
        }

        public override int GetHashCode()
        {
            return (x << 9) + y;
        }
    }

    /* 
     * Fields
     */

    public readonly int FlipsMaxCount;
    public Node[] nodes;
    public List<int> flips;
    public int xMin, xMax, yMin, yMax;

    /*
     * Properties
     */

    public int Area
    {
        get
        {
            int area = (xMax - xMin) * (yMax - yMin);
            return area;
        }
    }

    /*
     * Constructors
     */

    public Polymer(int[] directions)
    {
        int L = directions.Length + 1;
        FlipsMaxCount = L / 8;
        nodes = new Node[L + 1];
        nodes[0] = new Node(0, 0, Directions.East);
        Dictionary<Node, int> usedNodes = new Dictionary<Node, int>();
        usedNodes.Add(nodes[0], 0);
        for (int i = 1, dirId = 0; i < L + 1; i++, dirId++)
        {
            nodes[i] = new Node();
            nodes[i].x = nodes[i - 1].x + dX[(int)nodes[i - 1].nextDirection];
            nodes[i].y = nodes[i - 1].y + dY[(int)nodes[i - 1].nextDirection];
            if (dirId < directions.Length)
            {
                switch (directions[dirId])
                {
                    case -1:
                        nodes[i].nextDirection = RotateDirectionRight(nodes[i - 1].nextDirection);
                        break;
                    case 0:
                        nodes[i].nextDirection = nodes[i - 1].nextDirection;
                        break;
                    case 1:
                        nodes[i].nextDirection = RotateDirectionLeft(nodes[i - 1].nextDirection);
                        break;
                }
            }
            if (usedNodes.ContainsKey(nodes[i]))
            {
                throw new ArgumentException(string.Format("Invalid directions: overlapping nodes {0} and {1}", usedNodes[nodes[i]], i));
            }
            usedNodes.Add(nodes[i], i);
        }
        GetBorders();
        flips = new List<int>();
    }

    public Polymer(Node[] nodes, List<int> flips, int flipsMaxCount, int xMin, int xMax, int yMin, int yMax)
    {
        this.nodes = new Node[nodes.Length];
        Array.Copy(nodes, this.nodes, nodes.Length);
        this.flips = new List<int>(flips);
        this.FlipsMaxCount = flipsMaxCount;
        this.xMin = xMin;
        this.xMax = xMax;
        this.yMin = yMin;
        this.yMax = yMax;
    }

    /*
     * Methods
     */

    private void GetBorders()
    {
        xMax = xMin = 0;
        yMax = yMin = 0;
        foreach (Node node in nodes)
        {
            xMin = Math.Min(xMin, node.x);
            xMax = Math.Max(xMax, node.x);
            yMin = Math.Min(yMin, node.y);
            yMax = Math.Max(yMax, node.y);
        }
    }

    public static Directions FlipHorizontalDirection(Directions dir)
    {
        switch (dir)
        {
            case Directions.East:
                return Directions.West;
            case Directions.West:
                return Directions.East;
            default:
                return dir;
        }
    }

    public static Directions FlipVerticalDirection(Directions dir)
    {
        switch (dir)
        {
            case Directions.North:
                return Directions.South;
            case Directions.South:
                return Directions.North;
            default:
                return dir;
        }
    }

    public static Directions RotateDirectionRight(Directions dir)
    {
        switch (dir)
        {
            case Directions.East:
                return Directions.South;
            case Directions.North:
                return Directions.East;
            case Directions.West:
                return Directions.North;
            case Directions.South:
                return Directions.West;
        }
        throw new ArgumentException("Invalid direction");
    }

    public static Directions RotateDirectionLeft(Directions dir)
    {
        switch (dir)
        {
            case Directions.East:
                return Directions.North;
            case Directions.North:
                return Directions.West;
            case Directions.West:
                return Directions.South;
            case Directions.South:
                return Directions.East;
        }
        throw new ArgumentException("Invalid direction");
    }

    public bool TryFlipAt(int id)
    {
        if (id < 2 || id > nodes.Length - 2)
        {
            return false;
        }
        Dictionary<Node, bool> used = new Dictionary<Node, bool>();
        for (int i = 0; i < id; i++)
        {
            used.Add(nodes[i], true);
        }
        Node[] newRestOfNodes = new Node[nodes.Length - id - 1];
        switch (nodes[id - 1].nextDirection)
        {
            case Directions.East:
            case Directions.West:
                for (int i = id + 1, ni = 0; i < nodes.Length; i++, ni++)
                {
                    newRestOfNodes[ni] =
                        new Node(nodes[i].x, 2 * nodes[id].y - nodes[i].y, nodes[i].nextDirection);
                    if (used.ContainsKey(newRestOfNodes[ni]))
                    {
                        return false;
                    }
                    newRestOfNodes[ni].nextDirection =
                        FlipVerticalDirection(newRestOfNodes[ni].nextDirection);
                }
                nodes[id].nextDirection =
                    FlipVerticalDirection(nodes[id].nextDirection);
                break;
            case Directions.North:
            case Directions.South:
                for (int i = id + 1, ni = 0; i < nodes.Length; i++, ni++)
                {
                    newRestOfNodes[ni] =
                        new Node(2 * nodes[id].x - nodes[i].x, nodes[i].y, nodes[i].nextDirection);
                    if (used.ContainsKey(newRestOfNodes[ni]))
                    {
                        return false;
                    }
                    newRestOfNodes[ni].nextDirection =
                        FlipHorizontalDirection(newRestOfNodes[ni].nextDirection);
                }
                nodes[id].nextDirection =
                    FlipHorizontalDirection(nodes[id].nextDirection);
                break;
        }
        Array.Copy(newRestOfNodes, 0, nodes, id + 1, newRestOfNodes.Length);
        GetBorders();
        bool isFlipped = false;
        int lastFlipIndex = flips.Count - 1;
        if (lastFlipIndex >= 0 && flips[lastFlipIndex] == id)
        {
            flips.RemoveAt(lastFlipIndex);
            isFlipped = true;
        }
        /*for (int i = 0; i < flips.Count; i++)
        {
            if (flips[i] == id)
            {
                flips.RemoveAt(i);
                isFlipped = true;
                break;
            }
        }*/
        if (!isFlipped)
        {
            flips.Add(id);
        }
        return true;
    }

    public override string ToString()
    {
        string s = "";
        /*
        foreach (Node node in nodes)
        {
            s += string.Format("({0}, {1}: {2}), ", node.x, node.y, node.nextDirection, id);
        }*/
        s += "flips ";
        foreach (int flip in flips)
        {
            s += flip + " ";
        }
        s += "area " + Area;
        return s;
    }

    public object Clone()
    {
        Polymer copy = new Polymer(this.nodes, this.flips, this.FlipsMaxCount,
            this.xMin, this.xMax, this.yMin, this.yMax);
        return copy;
    }

    public int CompareTo(Polymer polymer)
    {
        return this.Area.CompareTo(polymer.Area);
    }

    public int CompareTo(object obj)
    {
        Polymer polymer = obj as Polymer;
        if (polymer == null)
        {
            throw new ArgumentException("Invalid polymer");
        }
        return this.CompareTo(polymer);
    }
}

