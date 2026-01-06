String Matching Algorithms & Plagiarism Detection (C++)
Overview

This C++ console-based application demonstrates and compares three fundamental string matching algorithms—Brute Force, Boyer–Moore, and Knuth–Morris–Pratt (KMP)—along with a basic plagiarism detection module.
The program is designed for educational and analytical purposes, allowing users to observe algorithm behavior, performance, and comparison counts on different types of input.

The application also supports file-based input, custom user input, and predefined stress test cases, making it suitable for coursework, demonstrations, and experimentation.

Features

Implementation of three classic string matching algorithms:

Brute Force

Boyer–Moore (Bad Character Heuristic)

Knuth–Morris–Pratt (KMP)

Side-by-side comparison of:

Number of character comparisons

Number of matches

Execution time (milliseconds)

Predefined best-case, worst-case, and average-case test scenarios

Custom text and pattern input from the console

File-based text and pattern searching

Simple plagiarism detection using sequential word matching

Case-insensitive matching

Color-coded Windows console output for readability

Algorithms Implemented
1. Brute Force Algorithm

Checks the pattern at every possible position in the text

Time Complexity: O(n × m)

Used as a baseline for comparison

no the exact github style one with ## and stuff

Understood. Below is a proper GitHub-style README.md, fully structured with headings, sections, and Markdown formatting. You can copy-paste this directly into README.md.

String Matching Algorithms & Plagiarism Detection (C++)
Overview

This project is a C++ console-based application that demonstrates and compares three classical string matching algorithms:

Brute Force

Boyer–Moore

Knuth–Morris–Pratt (KMP)

In addition, it includes a basic plagiarism detection module that compares two text files based on sequential word matching.

The primary goal of this project is academic learning—to analyze algorithm behavior, performance, and efficiency under different input conditions.

Features

Implementation of three core string searching algorithms

Comparison of:

Number of character comparisons

Number of matches found

Execution time (in milliseconds)

Predefined test cases (best, worst, and average scenarios)

Custom user input (text and pattern)

File-based input support

Simple plagiarism detection using sequential word matching

Case-insensitive matching

Colored output using Windows Console API

Algorithms Used
Brute Force Algorithm

Compares the pattern at every possible position in the text

Time Complexity: O(n × m)

Simple but inefficient for large inputs

Boyer–Moore Algorithm

Compares characters from right to left

Uses the Bad Character Heuristic to skip unnecessary comparisons

Average Time Complexity: O(n / m)

Worst Case: O(n × m)

Knuth–Morris–Pratt (KMP) Algorithm

Uses preprocessing of the pattern via the LPS (Longest Prefix Suffix) array

Avoids redundant comparisons

Time Complexity: O(n + m)

Plagiarism Detection Module

Reads two .txt files

Converts text to lowercase for fairness

Splits content into words

Detects sequential word matches (3 or more words)

Calculates similarity percentage

Categorizes plagiarism risk:

LOW

MEDIUM

HIGH

This is a basic implementation and not intended to replace professional plagiarism detection systems.

Program Menu
1. Run Predefined Test Cases
2. Enter Custom Text & Pattern
3. Load from Files
4. Plagiarism Detection (Compare txt files)
5. Exit Program

🧪 Predefined Test Cases

The program includes:

Pattern at the start of text

Large repeated text sequences

Worst-case partial matches

Multiple pattern occurrences

These cases help visualize algorithm performance differences.

File Input Format

Plain text files (.txt)

Any length of text

Newlines and spaces are handled correctly

Case-insensitive processing

Compilation & Execution
Requirements

Windows OS

C++ compiler (GCC / MinGW / MSVC)

Console supporting Windows API (windows.h)

Compile
g++ main.cpp -o string_matching

Run
string_matching

Limitations

Windows-only (uses windows.h)

Plagiarism detection is heuristic-based

Fixed maximum word limit in plagiarism module

Not optimized for very large documents

Educational Use

This project is ideal for:

Data Structures & Algorithms courses

Algorithm analysis demonstrations

Performance comparison studies

Beginner-to-intermediate C++ practice

License

This project is provided for educational purposes only.
You are free to modify and use it for learning or academic submissions.