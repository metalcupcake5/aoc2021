import os
import shutil

from .console import console

print = console.print


def initialize_day(day):
    if not os.path.exists(f"skel"):
        console.log(
            "cannot find skel directory. please make sure you are on the root directory and try again."
        )

    if os.path.exists(f"./aoc/day{day}"):
        console.log(
            f"directory of day {day} (./aoc/day{day}) already exists, not creating.",
            style="yellow",
        )
        return

    console.log(f"initializing day {day}")
    console.log(f"copying skel to ./aoc/day{day}")
    copy_ignore = shutil.ignore_patterns("__pycache__")
    shutil.copytree("skel", f"aoc/day{day}", ignore=copy_ignore)

    console.log(f"finished initializing.")


def _usage():
    import sys

    filename = sys.argv[0]
    usage = f"Usage: {filename} \[day]\n\n"
    usage += "Arguments:\n"
    usage += "    day ([green]int[/green]): the day that you want to initialize"

    print(usage)


if __name__ == "__main__":
    import sys

    if len(sys.argv) < 2:
        _usage()
        print("Not enough arguments.", style="red")
        sys.exit(1)

    try:
        day = int(sys.argv[1])
    except ValueError:
        _usage()
        print(
            "\nType of \[day] must be convertible to type [green]int[/green]",
            style="red",
        )
        sys.exit(1)

    initialize_day(day)
