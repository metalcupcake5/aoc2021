import os
import sys
from datetime import datetime

import requests
from dotenv import load_dotenv

from .console import console, input_console
from .init_day import initialize_day

print = console.print


def input_range(q, b, e=None, d=None):
    range_text = f"0-{b-1}" if not e else f"{b}-{e-1}"
    while True:
        i = input_console.input(
            q + f" [{range_text}]" + (f" [bold]default: {d}[/bold]" if d else "") + ": "
        )
        if d and len(i) == 0:
            return d
        elif len(i) == 0:
            input_console.log("Input must not be empty.")
            continue

        try:
            i = int(i)
        except ValueError:
            input_console.log("Input must be a number.")
            if d:
                input_console.log(f"defaulting to {d}")
                return d
            else:
                continue

        if i not in range(b, e):
            input_console.log(
                f'Invalid value "{i}", value must be in the range of {range_text}'
            )
            if d:
                input_console.log(f"defaulting to {d}")
                return d
        else:
            return i


def main():
    url = "https://adventofcode.com/{year}/day/{day}/input"
    load_dotenv()
    current_datetime = datetime.now()
    default_day = current_datetime.day if current_datetime.day in range(1, 26) else None

    if os.environ.get("SESSION") is None:
        console.log(
            "You do not have the `SESSION` environment set. Please check if you have a .env file or the variable is correctly set.",
            style="red",
        )
        return 99

    console.log("Loading...")
    cookies = {"session": os.environ.get("SESSION")}
    year = input_range("Which year?", 2015, 2022, 2021)
    day = input_range("Which day?", 1, 26, default_day)

    console.log(f"Fetching input from day {day} of {year}")
    res = requests.get(url.format(year=year, day=day), cookies=cookies)
    try:
        res.raise_for_status()
    except requests.HTTPError as e:
        console.log(f"Unable to fetch data: {e}", style="yellow")
        console.log(f"HTTP response code: [red]{res.status_code}[/red]", style="yellow")
        return 1

    result = res.text
    console.log(
        f"got {len(res.content)} bytes of content, totalling {len(result.splitlines())} lines"
    )
    console.log(
        f"perf: time elapsed waiting for request result {res.elapsed}", style="blue"
    )

    initialize_day(day)

    with open(f"./aoc/day{day}/input", "w+") as f:
        f.write(result)
        console.log(f"wrote input to `./aoc/day{day}/input`")


if __name__ == "__main__":
    exit_code = main()
    console.log("saving log output to logs/log-fetch_input.html")
    console.save_html("logs/log-fetch_input.html")
    sys.exit(exit_code)
