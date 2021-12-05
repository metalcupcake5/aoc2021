using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace puzzles
{
    public class five
    {
        private record Vector(int X, int Y)
        {
            public int X { get; } = X;
            public int Y { get; } = Y;

            public static Vector Parse(string input)
            {
                var points = input.Split(",");
                var x = int.Parse(points[0]);
                var y = int.Parse(points[1]);
                
                return new Vector(x, y);
            }
        }

        private class Line
        {
            private Vector Start { get; }
            private Vector End { get; }

            private Line(Vector start, Vector end)
            {
                Start = start;
                End = end;
            }

            public List<Vector> GetOverlapping(bool diagonals)
            {
                var overlapping = new List<Vector> { Start, End };
                if (Start.X == End.X && Start.Y == End.Y) 
                    return overlapping;

                if (Start.X == End.X)
                {
                    var lowest = Start.Y > End.Y ? End.Y : Start.Y;
                    var highest = lowest == Start.Y ? End.Y : Start.Y;
                    for (var i = lowest + 1; i < highest; i++)
                    {
                        var vec = new Vector(Start.X, i);
                        if (vec != Start && vec != End) overlapping.Add(vec);
                    }
                }
                else if (Start.Y == End.Y)
                {
                    var lowest = Start.X > End.X ? End.X : Start.X;
                    var highest = lowest == Start.X ? End.X : Start.X;
                    
                    for (var i = lowest + 1; i < highest; i++)
                    {
                        var vec = new Vector(i, Start.Y);
                        if (vec != Start && vec != End) overlapping.Add(vec);
                    }
                }
                else if (diagonals)
                {
                    var diff = Math.Abs(Start.X - End.X);
                    var ay = Start.Y > End.Y ? -1 : 1;
                    var ax = Start.X > End.X ? -1 : 1;

                    for (var i = 0; i < diff - 1; i++)
                    {
                        var vec = new Vector(Start.X + (i + 1) * ax, Start.Y + (i + 1) * ay);
                        overlapping.Add(vec);
                    }
                }
                else return null;

                return overlapping;     
            }

            public static Line Parse(string input)
            {
                var points = input.Split(" -> ");
                return new Line(Vector.Parse(points[0]), Vector.Parse(points[1]));
            }
        }

        private class Grid
        {
            public Dictionary<Vector, int> Vectors { get; } = new ();
            public int Overlapping { get; set; }
        }

        private static void A(string[] input)
        {
            var grid = FillGrid(input, false);
            Console.WriteLine(grid.Overlapping);
        }
        
        private static void B(string[] input)
        {
            var grid = FillGrid(input, true);
            Console.WriteLine(grid.Overlapping);
        }

        private static Grid FillGrid(string[] input, bool diagonals)
        {
            var grid = new Grid();
            
            foreach (var inpLine in input)
            {
                var line = Line.Parse(inpLine);
                var overlapping = line.GetOverlapping(diagonals);
                
                if (overlapping is null) continue;

                foreach (var vector in overlapping)
                {
                    if (grid.Vectors.TryAdd(vector, 1)) continue;
                    
                    grid.Vectors[vector]++;
                    grid.Overlapping++;
                }
            }

            return grid;
        }

        public static void Start(string path)
        {
            var input = File.ReadAllLines(path.Replace("${day}", "5"));
            A(input);
            B(input);
        }
    }
}