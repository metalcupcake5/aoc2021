using System;
using System.IO;

namespace puzzles
{
    public class two
    {
        private enum Direction
        {
            Forward,
            Up,
            Down
        }

        private struct Target
        {
            public int X { get; set; }
            public int Y { get; set; }
            public int Aim { get; set; }

            public Target(int x, int y, int aim)
            {
                X = x;
                Y = y;
                Aim = aim;
            }
        }

        private const string Path = @"C:\Users\yawmd\Documents\GitHub\aoc2021\yawm\puzzles\2\input.txt";

        private static void A()
        {
            var target = new Target(0, 0, 0);
            var inp = File.ReadAllLines(Path);
            foreach (var line in inp)
            {
                var values = line.Split(' ');
                var dir = Enum.Parse<Direction>(values[0], true);

                switch (dir)
                {
                    case Direction.Forward:
                        target.X += int.Parse(values[1]);
                        break;
                    case Direction.Up:
                        target.Y -= int.Parse(values[1]);
                        break;
                    case Direction.Down:
                        target.Y += int.Parse(values[1]);
                        break;
                }
            }
            
            Console.WriteLine(target.X * target.Y);
        }
        
        private static void B()
        {
            var target = new Target(0, 0, 0);
            var inp = File.ReadAllLines(Path);
            foreach (var line in inp)
            {
                var values = line.Split(' ');
                var dir = Enum.Parse<Direction>(values[0], true);

                switch (dir)
                {
                    case Direction.Forward:
                        target.X += int.Parse(values[1]);
                        target.Y += target.Aim * int.Parse(values[1]);
                        break;
                    case Direction.Up:
                        target.Aim -= int.Parse(values[1]);
                        break;
                    case Direction.Down:
                        target.Aim += int.Parse(values[1]);
                        break;
                }
            }
            
            Console.WriteLine(target.X * target.Y);
        }
        
        public static void Start()
        {
            A();
            B();
        }
    }
}