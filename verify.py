"""Compile and check all ten HW2 programs; remove executables afterward."""

from decimal import Decimal
from math import isqrt
from pathlib import Path
import re
import shutil
import subprocess
import tempfile


ROOT = Path(__file__).resolve().parent
QUESTIONS = ("3.17", "3.18", "3.19", "3.20", "3.33",
             "4.15", "4.16", "4.27", "4.28", "4.31")


def main():
    compiler = shutil.which("gcc")
    if compiler is None:
        raise SystemExit("GCC is required. Install GCC and add it to PATH.")

    checks = 0
    with tempfile.TemporaryDirectory(prefix="hw2-check-") as directory:
        executables = {}
        for question in QUESTIONS:
            executable = Path(directory) / (question + ".exe")
            result = subprocess.run(
                [compiler, "-std=c11", "-Wall", "-Wextra", "-Wpedantic",
                 "-Werror", "-O2", str(ROOT / question / "main.c"),
                 "-o", str(executable), "-lm"],
                capture_output=True, text=True, timeout=30,
            )
            assert result.returncode == 0, (question, result.stderr)
            executables[question] = executable

        def run(question, data="", valid=True):
            nonlocal checks
            result = subprocess.run(
                [str(executables[question])], input=data,
                capture_output=True, text=True, timeout=15,
            )
            if valid:
                assert result.returncode == 0, (question, data, result.stderr)
                assert not result.stderr, (question, result.stderr)
            else:
                assert result.returncode != 0, (question, data)
                assert result.stderr.strip(), (question, data)
            checks += 1
            return result.stdout

        # Examples from the homework and exact credit-limit boundaries.
        output = run("3.17", "100\n5394.78\n1000\n500\n5500\n"
                            "200\n1000\n123.45\n321\n1500\n"
                            "300\n500\n274.73\n100\n800\n-1\n")
        assert re.findall(r"Account:\s+(\d+)", output) == ["100"]
        assert "5894.78" in output and output.count("Credit limit exceeded.") == 1
        for data, exceeded in (("1\n100\n20\n10\n110\n-1\n", False),
                               ("1\n0.1\n0.2\n0\n0.3\n-1\n", False),
                               ("1\n100\n20.01\n10\n110\n-1\n", True)):
            assert ("Credit limit exceeded." in run("3.17", data)) == exceeded

        output = run("3.18", "5000\n1234.56\n0\n-1\n")
        assert re.findall(r"Salary is: \$(\d+\.\d{2})", output) == [
            "650.00", "311.11", "200.00"]
        output = run("3.19", "1000\n0.1\n365\n1000\n0.08375\n224\n"
                            "1000\n0.1\n0\n-1\n")
        assert re.findall(r"charge is \$(\d+\.\d{2})", output) == [
            "100.00", "51.40", "0.00"]
        output = run("3.20", "39\n10\n40\n10\n41\n10\n0\n10\n-1\n")
        assert re.findall(r"Salary is \$(\d+\.\d{2})", output) == [
            "390.00", "400.00", "415.00", "0.00"]

        # Check every character, including spaces, for small rectangles.
        for rows, columns in [(3, 12)] + [(r, c) for r in range(1, 6)
                                                        for c in range(1, 6)]:
            output = run("3.33", f"{rows} {columns}\n").split(": ", 1)[1]
            lines = output.splitlines()
            expected = ["+" * columns]
            if rows > 1:
                middle = "+" if columns == 1 else "+" + " " * (columns - 2) + "+"
                expected += [middle] * (rows - 2) + ["+" * columns]
            assert lines == expected, (rows, columns, lines)

        output = run("4.15")
        blocks = output.strip().split("\n\n")
        assert len(blocks) == 5
        for step, block in zip(range(20, 25), blocks):
            lines = block.splitlines()
            rate = Decimal(step) / Decimal(200)
            assert lines[0] == f"Interest rate: {rate * 100:.1f}%"
            assert len(lines[2:]) == 15
            for year, line in enumerate(lines[2:], start=1):
                expected = Decimal(5000) * (1 + rate) ** year
                actual_year, amount = line.split()
                assert int(actual_year) == year and re.fullmatch(r"\d+\.\d{2}", amount)
                # At exact half cents, binary pow/printf can round either way.
                assert abs(Decimal(amount) - expected) <= Decimal("0.005000000001")

        triangle_lines = run("4.16").splitlines()
        counts = list(range(1, 11))
        expected = [
            ["*" * n for n in counts],
            ["*" * n for n in reversed(counts)],
            [" " * (10 - n) + "*" * n for n in reversed(counts)],
            [" " * (10 - n) + "*" * n for n in counts],
        ]
        assert triangle_lines[0] == f"{'(A)':<13}{'(B)':<13}{'(C)':<13}(D)"
        assert triangle_lines[1:] == [
            "   ".join(pattern[row].ljust(10) for pattern in expected)
            for row in range(10)
        ]

        # An independent integer-square-root oracle checks all triples.
        lines = run("4.27").splitlines()[1:]
        triples = [tuple(map(int, line.split())) for line in lines]
        expected_triples = set()
        for hypotenuse in range(1, 501):
            for side1 in range(1, hypotenuse):
                remainder = hypotenuse ** 2 - side1 ** 2
                side2 = isqrt(remainder)
                if side1 <= side2 and side2 ** 2 == remainder:
                    expected_triples.add((side1, side2, hypotenuse))
        assert len(triples) == len(set(triples))
        assert set(triples) == expected_triples
        assert (3, 4, 5) in triples and (300, 400, 500) in triples

        output = run("4.28", "1\n1000\n2\n39\n10\n2\n40\n10\n"
                            "2\n41\n10\n2\n40.5\n10\n3\n5000\n"
                            "3\n0\n4\n2.5\n100\n4\n2.5\n0\n9\n-1\n")
        assert re.findall(r"Weekly pay is \$(\d+\.\d{2})", output) == [
            "1000.00", "390.00", "400.00", "415.00", "407.50", "535.00",
            "250.00", "250.00", "0.00"]
        assert "Invalid paycode." in output

        diamond = run("4.31").splitlines()
        assert diamond == ["    *", "   ***", "  *****", " *******",
                           "*********", " *******", "  *****", "   ***", "    *"]

        for question in ("3.17", "3.18", "3.19", "3.20", "4.28"):
            run(question, "-1\n")
        for question, data in (
            ("3.17", "0\n"), ("3.17", "1\n0\n-2\n"),
            ("3.18", "-2\n"), ("3.19", "1\n0.1\n-2\n"),
            ("3.20", "1\n-2\n"), ("3.33", "0 3\n"),
            ("3.33", "3 -1\n"), ("4.28", "2\n-2\n"),
            ("4.28", "4\n1\n-2\n"), ("4.28", "1\n-2\n"),
            ("4.28", "3\nnan\n"), ("3.18", "inf\n"),
        ):
            run(question, data, valid=False)
        for question in ("3.17", "3.18", "3.19", "3.20", "3.33", "4.28"):
            run(question, "abc\n", valid=False)
            run(question, "", valid=False)

        print(f"PASS: {len(QUESTIONS)} programs compiled without warnings; "
              f"{checks} execution checks passed.")
        print(f"4.27: {len(triples)} unique Pythagorean triples verified.")

    assert not Path(directory).exists(), "Temporary build directory was not removed."
    print("Temporary executables removed.")


if __name__ == "__main__":
    main()
