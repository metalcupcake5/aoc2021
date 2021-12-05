namespace puzzles
{
    class Program
    {
        private const string Path = @"C:\Users\yawmd\Documents\GitHub\aoc2021\yawm\puzzles\${day}\input.txt";

        private static void Main(string[] args)
        {
            one.Start(Path);
            two.Start(Path);
            three.Start(Path);
            four.Start(Path);
            five.Start(Path);
        }
    }
}