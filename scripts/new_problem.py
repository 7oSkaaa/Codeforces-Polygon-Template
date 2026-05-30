#!/usr/bin/env python3
"""
Scaffold a new problem directory with a Python solution template and sample files.

Usage:
  python scripts/new_problem.py <problem-name>

Creates `problems/<problem-name>/solution.py`, `sample.in`, `sample.out`.
"""
import sys
from pathlib import Path


TEMPLATE = '''# Solution template
import sys

def main():
    data = sys.stdin.read().strip().split()
    if not data:
        return
    # TODO: implement solution
    print("Hello")


if __name__ == '__main__':
    main()
'''


def main():
    if len(sys.argv) < 2:
        print("Usage: new_problem.py <name>")
        sys.exit(2)
    name = sys.argv[1]
    base = Path('problems') / name
    base.mkdir(parents=True, exist_ok=True)

    sol = base / 'solution.py'
    sample_in = base / 'sample.in'
    sample_out = base / 'sample.out'

    if sol.exists():
        print(f"Problem already exists: {base}")
        sys.exit(1)

    sol.write_text(TEMPLATE)
    sample_in.write_text('')
    sample_out.write_text('')

    print(f"Created problem scaffold at: {base}")


if __name__ == '__main__':
    main()
