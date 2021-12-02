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

        private static void A()
        {
            var increases = 0;
            var inp = File.ReadAllLines(Path);
            var prev = int.MaxValue;

            foreach (var line in inp)
            {
                var num = int.Parse(line);
                if (num > prev)
                    increases++;
                
                prev = num;
            }
            
            Console.WriteLine(increases);
        }

        private static void B()
        {
            var increases = 0;
            var numbers = GetNumbers();
            var prev = int.MaxValue;
            
            foreach (var num in numbers)
            {
                if (num.Previous?.Previous == null) 
                    continue;
                
                var sum = num.Value + num.Previous.Value + num.Previous.Previous.Value;
                if (sum > prev)
                    increases++;
                
                prev = sum;
            }

            Console.WriteLine(increases);
        }

        private static List<Number> GetNumbers()
        {
            var inp = File.ReadAllLines(Path);
            var numbers = new List<Number>();
            Number previous = null;
            
            foreach (var line in inp)
            {
                var num = new Number(previous, int.Parse(line));
                numbers.Add(num);

                previous = num;
            }

            return numbers;
        }

        public static void Start()
        {
            A();
            B();
        }
    }
}