using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace puzzles
{
    public class three
    {
        private class Pair
        {
            public int Zeros { get; set; }
            public int Ones { get; set; }

            public Pair(int zeros, int ones)
            {
                Zeros = zeros;
                Ones = ones;
            }

            public char Get(bool highest)
            {
                if (highest)
                    return Zeros > Ones ? '0' : '1';
                
                return Zeros > Ones ? '1' : '0';
            }
        }

        private static void A(string[] input)
        {
            var gamma = ToDecimal(GetExtremes(true, input));
            var epsilon = ToDecimal(GetExtremes(false, input));

            Console.WriteLine(gamma * epsilon);
        }

        private static void B(string[] input)
        {
            var generator = GetCriteriaBit(true, input);
            var scrubber = GetCriteriaBit(false, input);

            Console.WriteLine(ToDecimal(generator) * ToDecimal(scrubber));
        }

        private static string GetCriteriaBit(bool highest, string[] input)
        {
            var current = input;
            var i = 0;
            while (current.Length > 1)
            {
                current = GetBitsWithValueAtIndex(i, GetExtreme(highest, i, current), current);
                i++;
            }

            return current[0];
        }

        private static string[] GetBitsWithValueAtIndex(int index, char extreme, string[] input)
        {
            return input.Where(row => row[index] == extreme).ToArray();
        }

        private static int ToDecimal(string binary)
        {
            return Convert.ToInt32(binary, 2);
        }

        private static char GetExtreme(bool highest, int index, string[] input)
        {
            Pair column = null;
            foreach (var row in input)
            {
                for (var i = 0; i < row.Length; i++)
                {
                    if (i != index) continue;
                    
                    var ch = row[i];
                    if (ch == '0')
                    {
                        if (column != null) column.Zeros++;
                        else column = new Pair(1, 0);
                        continue;
                    }
                    
                    if (column != null) column.Ones++;
                    else column = new Pair(0, 1);
                }
            }

            return column?.Get(highest) ?? '0';
        }
        
        private static string GetExtremes(bool highest, string[] input)
        {
            var columns = new List<Pair> ();
            foreach (var row in input)
            {
                for (var i = 0; i < row.Length; i++)
                {
                    var ch = row[i];
                    if (ch == '0')
                    {
                        if (columns.Count > i) columns[i].Zeros++;
                        else columns.Add(new Pair(1, 0));
                        continue;
                    }
                    
                    if (columns.Count > i) columns[i].Ones++;
                    else columns.Add(new Pair(0, 1));
                }
            }

            var endBit = "";
            foreach (var column in columns)
            {
                var num = column.Get(highest);
                endBit += num;
            }

            return endBit;
        }
        
        public static void Start(string path)
        {
            var input = File.ReadAllLines(path.Replace("${day}", "3"));
            A(input);
            B(input);
        }
    }
}