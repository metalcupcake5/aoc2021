using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace puzzles
{
    public class four
    {
        private class Board
        {
            private int[,] Values { get; } = new int[5, 5];
            private bool[,] Marked { get; } = new bool[5, 5];
            
            public Board (string[] input, int index, int boardSize)
            {
                for (var i = 0; i < boardSize; i++)
                {
                    var row = input[index + i];
                    for (var j = 0; j < row.Length; j += 3)
                    {
                        var num = row[j] + row[j + 1].ToString().Trim();
                        Values[i, j / 3] = int.Parse(num);
                    }
                }
            }

            public void Guess(int num)
            {
                for (var i = 0; i < Values.GetLength(0); i++)
                    for (var j = 0; j < Values.GetLength(1); j++)
                        if (Values[i, j] == num)
                            Marked[i, j] = true;
            }
            
            public int Sum(bool marked)
            {
                var sum = 0;
                for (var i = 0; i < Values.GetLength(0); i++)
                    for (var j = 0; j < Values.GetLength(1); j++)
                        if (marked || !Marked[i, j])
                            sum += Values[i, j];

                return sum;
            }
            
            public bool CheckWin()
            {
                var result = CheckLines(false);
                result = CheckLines(true) || result;
                
                return result;
            }

            private bool CheckLines(bool vertical)
            {
                for (var i = 0; i < Marked.GetLength(0); i++)
                {
                    var column = new bool[Marked.GetLength(1)];
                    for (var j = 0; j < Marked.GetLength(1); j++)
                        column[j] = vertical ? Marked[i, j] : Marked[j, i];

                    if (column.All(marked => marked)) return true;
                }
                
                return false;
            }
        }
        
        private static List<int> _numbers = new ();
        private static List<Board> _boards = new ();

        private static void A(string[] input)
        {
            Init(input);

            foreach (var number in _numbers)
            {
                foreach (var board in _boards)
                {
                    board.Guess(number);
                    if (board.CheckWin())
                    {
                        Console.WriteLine($"{board.Sum(false) * number}");
                        return;
                    }
                }
            }
        }

        private static void B(string[] input)
        {
            Init(input);

            var winners = 0;
            var lastNum = 0;
            Board lastWinner = null;
            foreach (var number in _numbers)
            {
                if (winners == _boards.Count) break;
                var removed = new List<Board>();
                
                foreach (var board in _boards)
                {
                    board.Guess(number);
                    if (board.CheckWin())
                    {
                        winners++;
                        lastWinner = board;
                        lastNum = number;
                        removed.Add(board);
                    }
                }
                
                foreach (var b in removed)
                    _boards.Remove(b);
            }

            if (lastWinner is null)
                return;
            
            Console.WriteLine($"{lastWinner.Sum(false) * lastNum}");
        }

        private static void Init(string[] input)
        {
            _numbers = input[0].Split(',').Select(int.Parse).ToList();
            input = input.Where(line => !string.IsNullOrEmpty(line) && !line.Contains(',')).ToArray();

            for (var i = 0; i < input.Length; i += 5)
                _boards.Add(new Board(input, i, 5));
        }

        public static void Start(string path)
        {
            var input = File.ReadAllLines(path.Replace("${day}", "4"));
            A(input);
            B(input);
        }
    }
}