using System;
using System.Collections.Generic;
using System.IO;

namespace puzzles
{
    public class one
    {
        private class Number
        {
            public Number Previous { get; }
            public int Value { get; }

            public Number(Number prev, int value)
            {
                Previous = prev;
                Value = value;
            }
        }

        private static void A(string[] input)
        {
            var increases = 0;
            var prev = int.MaxValue;

            foreach (var line in input)
            {
                var num = int.Parse(line);
                if (num > prev)
                    increases++;
                
                prev = num;
            }
            
            Console.WriteLine(increases);
        }

        private static void B(string[] input)
        {
            var increases = 0;
            var numbers = GetNumbers(input);
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

        private static List<Number> GetNumbers(string[] input)
        {
            var numbers = new List<Number>();
            Number previous = null;
            
            foreach (var line in input)
            {
                var num = new Number(previous, int.Parse(line));
                numbers.Add(num);

                previous = num;
            }

            return numbers;
        }

        public static void Start(string path)
        {
            var input = File.ReadAllLines(path.Replace("${day}", "1"));
            A(input);
            B(input);
        }
    }
}