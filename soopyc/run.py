import sys
import argparse
import importlib

from aoc.tools.console import console

LOGFILE = "run.txt"
parser = argparse.ArgumentParser(description="Run a day of aoc")
parser.add_argument("day", help="day of the aoc solution to run")
parser.add_argument("part", help="part of the aoc solution to run")
parser.epilog = "examples: 'run.py 1 b', 'run.py 2 1'"


def main():
    global LOGFILE

    args = parser.parse_args()
    if args.part not in ("a", "b"):
        if args.part == "1":
            args.part = "a"
        elif args.part == "2":
            args.part = "b"

    if args.part not in "ab12":
        console.log(
            f"invalid part: there are normally only 2 parts in an aoc day. acceptable values for part are: 'a, b, 1, 2'",
            style="yellow",
        )
        console.log(f"debug: current value of part: {args.part}", style="bold black")
        return 1
    console.log(f"attempting to import aoc.day{args.day}.{args.part}")
    try:
        module = importlib.import_module(f"aoc.day{args.day}.{args.part}")
    except ImportError as e:
        console.log(
            f"E: unable to import aoc.day{args.day}.{args.part}: {e}", style="red"
        )
        return 1

    try:
        console.log(f"imported module, running main function")
        LOGFILE = f"day-{args.day}{args.part}.txt"
        return module.main()
    except Exception as e:
        console.log(f"main function errored out", style="red")
        console.print_exception()
        return 2


if __name__ == "__main__":
    exitcode = main()
    console.log(f"saving logs to logs/{LOGFILE}")
    console.save_text(f"logs/{LOGFILE}")
    sys.exit(exitcode)
