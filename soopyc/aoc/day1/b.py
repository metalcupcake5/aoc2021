from types import SimpleNamespace
from collections import deque

from rich.table import Table

from .input import _string
from ..tools.console import console
print = console.log


class Changes(SimpleNamespace):
    pass


def main():
    counter = Changes(inc=0, dec=0, nc=0)
    queue = deque(maxlen=2)
    input_ = _string.decode()
    data = input_.splitlines()
    queue.append(int(data.pop(0)))
    sign = ""

    for count, i in enumerate(range(len(data), 4)):
        ...
        # use indexes, i, i+1, i+2 = a; i+2, i+3, i+4 = b

        if count % 5 == 0:
            print(f'#{count}: {queue[1]} {sign} {queue[0]}; {counter}; {round((count+1)/len(data)*100, 2)}%; dq={queue}')

    print(f'#{count}: {queue[1]} {sign} {queue[0]}; {counter}; {round((count+1)/len(data)*100, 2)}%')
    # Summing up
    table = Table("", "", title="Summary table")
    table.add_row("Increases", str(counter.inc), style="green")
    table.add_row("Decreases", str(counter.dec), style="red")
    table.add_row("No Change", str(counter.nc), style="bold black")
    table.add_row()
    table.add_row("Grand Total", str(counter.inc + counter.dec + counter.nc), style="bold blue")
    print(table)
