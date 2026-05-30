#!/usr/bin/env python3
"""
Run the solution for a problem against its samples using the tester.

Usage:
  python scripts/run.py <problem-name>

Assumes `problems/<problem-name>/solution.py`, `sample.in`, `sample.out` exist.
"""
import sys
from pathlib import Path
import subprocess


def main():
    if len(sys.argv) < 2:
        print("Usage: run.py <problem-name>")
        sys.exit(2)
    name = sys.argv[1]
    base = Path('problems') / name
    sol = base / 'solution.py'
    sin = base / 'sample.in'
    sout = base / 'sample.out'

    if not sol.exists():
        print('solution.py not found in', base)
        sys.exit(2)
    if not sin.exists() or not sout.exists():
        print('sample.in or sample.out not found in', base)
        sys.exit(2)

    tester = Path('tester') / 'tester.py'
    if not tester.exists():
        print('tester not found at', tester)
        sys.exit(2)

    cmd = [sys.executable, str(tester), '--solution', str(sol), '--input', str(sin), '--expected', str(sout), '--trim']
    proc = subprocess.run(cmd)
    sys.exit(proc.returncode)


if __name__ == '__main__':
    main()
