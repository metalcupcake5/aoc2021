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
        private static Target _target = new (0, 0, 0);
        
        public static void Start()
        {
            var inp = File.ReadAllLines(Path);
            foreach (var line in inp)
            {
                var values = line.Split(' ');
                var dir = Enum.Parse<Direction>(values[0], true);

                switch (dir)
                {
                    case Direction.Forward:
                        _target.X += int.Parse(values[1]);
                        _target.Y += _target.Aim * int.Parse(values[1]);
                        break;
                    case Direction.Up:
                        _target.Aim -= int.Parse(values[1]);
                        break;
                    case Direction.Down:
                        _target.Aim += int.Parse(values[1]);
                        break;
                }
            }
            
            Console.WriteLine(_target.X * _target.Y);
        }
    }
}