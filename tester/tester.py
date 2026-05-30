#!/usr/bin/env python3
"""
Simple test harness to run a solution against an input file and compare output.

Usage:
  python tester/tester.py --solution path/to/solution.py --input sample.in --expected sample.out

Supports Python solutions (.py) and already-built executables.
"""
import argparse
import subprocess
import sys
from pathlib import Path


def run_solution(solution: Path, stdin_data: bytes) -> subprocess.CompletedProcess:
    if solution.suffix == ".py":
        cmd = [sys.executable, str(solution)]
    else:
        # assume executable
        cmd = [str(solution)]
    return subprocess.run(cmd, input=stdin_data, stdout=subprocess.PIPE, stderr=subprocess.PIPE)


def main():
    p = argparse.ArgumentParser(description="Run a solution against sample input and compare output")
    p.add_argument("--solution", required=True, type=Path, help="Path to solution (python file or executable)")
    p.add_argument("--input", required=True, type=Path, help="Path to sample input file")
    p.add_argument("--expected", required=True, type=Path, help="Path to expected output file")
    p.add_argument("--trim", action="store_true", help="Trim trailing whitespace when comparing")
    args = p.parse_args()

    if not args.solution.exists():
        print(f"Solution not found: {args.solution}")
        sys.exit(2)
    if not args.input.exists() or not args.expected.exists():
        print("Input or expected file not found")
        sys.exit(2)

    stdin_data = args.input.read_bytes()
    proc = run_solution(args.solution, stdin_data)

    if proc.returncode != 0:
        print("--- Runtime Error ---")
        print(proc.stderr.decode(errors="ignore"))
        sys.exit(proc.returncode)

    out = proc.stdout.decode(errors="ignore")
    exp = args.expected.read_text()

    if args.trim:
        out = out.strip()
        exp = exp.strip()

    if out == exp:
        print("OK: output matches expected")
        sys.exit(0)
    else:
        print("FAIL: output differs from expected")
        print("--- Expected ---")
        print(exp)
        print("--- Actual ---")
        print(out)
        sys.exit(1)


if __name__ == "__main__":
    main()
