using System;
using System.Collections.Generic;
using System.IO;

namespace puzzles
{
    public class one
    {
        private class Number
        {
            public Number Previous { get; set; }
            public int Value { get; set; }

            public Number(Number prev, int value)
            {
                Previous = prev;
                Value = value;
            }
        }

        private const string Path = @"C:\Users\yawmd\Documents\GitHub\aoc2021\yawm\puzzles\1\input.txt";
        private static readonly List<Number> Numbers = new ();
        private static int _increases;
        
        public static void Start()
        {
            var inp = File.ReadAllLines(Path);
            Number previous = null;

            foreach (var line in inp)
            {
                var num = new Number(previous, int.Parse(line));
                Numbers.Add(num);

                previous = num;
            }

            var prev = int.MaxValue;
            foreach (var num in Numbers)
            {
                if (num.Previous?.Previous == null) continue;
                
                var sum = num.Value + num.Previous.Value + num.Previous.Previous.Value;
                if (sum > prev)
                    _increases++;
                prev = sum;
            }

            Console.WriteLine(_increases);
        }
    }
}