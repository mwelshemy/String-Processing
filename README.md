# Assignment 4: String Processing

## Overview
This project implements and analyzes two advanced string matching algorithms: the **Boyer-Moore Algorithm** and the **Rabin-Karp Algorithm**. String matching is essential for search engines, DNA sequence analysis, and data processing systems. This C++ program allows users to load text, search for single or multiple patterns, and compare the performance of these algorithms based on execution time and character comparisons.

## Features
* **Interactive Menu:** A user-friendly CLI to navigate through text loading and searching options.
* **Flexible Text Input:**
  * Load text from an external file (e.g., `input.txt`).
  * Enter text manually via the console.
* **Advanced Search Algorithms:**
  * **Boyer-Moore:** Compares from right to left, utilizing the "bad character rule" to efficiently skip unnecessary text.
  * **Rabin-Karp:** Uses a rolling hash technique to quickly compare pattern hashes with text substring hashes .
* **Multiple Pattern Search:** Allows searching for consecutive patterns in a single execution run.
* **Visual Pattern Highlighting:** Highlights found matches within the text using brackets (e.g., `DATA [STRUCTURE] COURSE`).
* **Overlapping Matches:** Correctly detects and counts overlapping patterns (e.g., finding `AAA` multiple times in `AAAAAA`).
* **Algorithm Comparison & Statistics:** Outputs the number of matches, total character comparisons, and execution time (in milliseconds) for side-by-side performance analysis.

## Complexity Analysis
The algorithms implemented in this project have the following time and space complexities:

| Algorithm | Time Complexity | Space Complexity |
| :--- | :--- | :--- |
| **Boyer-Moore** | O(n/m) best case | O(1) |
| **Rabin-Karp** | O(n+m) average case | O(1) |

*(Where n is the length of the text and m is the length of the pattern)*

## How to Compile and Run
This project requires a standard C++ compiler (like `g++`).

**1. Compile the code:**
```bash
g++ main.cpp -o main
```

**2. Run the executable:**
* **Windows:** `.\main`
* **Mac/Linux:** `./main`

## Input File Specification
To use the file loading feature, ensure an `input.txt` file is located in the same directory as the executable. 

**Example `input.txt` content:**
```text
DATA STRUCTURE AND ALGORITHMS COURSE
THIS COURSE TEACHES DATA HANDLING AND TREE STRUCTURES
RABIN KARP AND BOYER MOORE ARE STRING MATCHING ALGORITHMS DATA DATA DATA STRUCTURE STRUCTURE
AAAAAA TEST FOR OVERLAPPING AAA PATTERN
```

## Validated Test Cases
This program has been tested and validated against the following scenarios:
1. **Multiple Overlapping Matches:** Text `AAAAAAAAA`, Pattern `AAA`
2. **Standard Match:** Text `DATA STRUCTURE`, Pattern `STRUCTURE`
3. **No Match:** Text `HELLO WORLD`, Pattern `TEST`
4. **Multiple Matches:** Text `MISSISSIPPI`, Pattern `ISSI`
5. **Partial but No Match:** Text `ALGORITHM`, Pattern `RITH`