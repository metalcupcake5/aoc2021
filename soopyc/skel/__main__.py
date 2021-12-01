import sys

from .a import main as main_a
from .b import main as main_b

if len(sys.argv) < 2:
    print("you must specify the part of day to use. append a or b to your command.")
    print("a runs part 1 while b runs part 2.")
    sys.exit(1)

if sys.argv[1].lower() == "a" or sys.argv[1].lower() == "1":
    print("running part 1")
    sys.exit(main_a())
elif sys.argv[1].lower() == "b" or sys.argv[1].lower() == "2":
    print("running part 2")
    sys.exit(main_b())
else:
    print(f"unknown part {sys.argv[1]}. available options: a, b")
