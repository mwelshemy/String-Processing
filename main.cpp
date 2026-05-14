#include <iostream>
#include <string>
#include <fstream>
#include <vector>     
#include <algorithm>  
#include <chrono>     

using namespace std;

string globalText = "";

void printHighlightedText(int index, int patternLength) {
    cout << "Output: ";
    for (int i = 0; i < globalText.length(); i++) {
        if (i == index) cout << "[";         
        cout << globalText[i];               
        if (i == index + patternLength - 1) cout << "]"; 
    }
    if (globalText.empty() || globalText.back() != '\n') {
        cout << "\n";
    }
}

void buildBadCharTable(string pattern, vector<int>& badchar) {
    int m = pattern.length();
    // initialize all occurrences as -1
    for (int i = 0; i < 256; i++) {
        badchar[i] = -1; 
    }
    for (int i = 0; i < m; i++) {
        badchar[(unsigned char)pattern[i]] = i; 
    }
}

// Boyer-Moore
void runBoyerMooreCore(string pattern) {
    int m = pattern.length();
    int n = globalText.length();
    int comparisons = 0; 
    int matches = 0;     

    vector<int> badchar(256);
    buildBadCharTable(pattern, badchar);

    int s = 0; // s is the shift of the pattern with respect to text

    // execution timer
    auto start = chrono::high_resolution_clock::now();

    while (s <= (n - m)) {
        int j = m - 1;

        // reducing index j of pattern while characters of pattern and text match
        while (j >= 0) {
            comparisons++; 
            if (pattern[j] == globalText[s + j]) {
                j--; 
            } else {
                break; 
            }
        }

        // if the pattern is present at current shift
        if (j < 0) {
            cout << "Match at index: " << s << "\n";
            printHighlightedText(s, m); 
            matches++; 
            
            if (s + m < n) {
                s += m - badchar[(unsigned char)globalText[s + m]];
            } else {
                s += 1;
            }
        } else {
            // shift the pattern so that the bad character in text aligns with the last occurrence of it in pattern
            s += max(1, j - badchar[(unsigned char)globalText[s + j]]);
        }
    }

    // stop timer
    auto end = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count() * 1e-6;

    cout << "Algorithm used: Boyer-Moore\n";
    cout << "Number of comparisons: " << comparisons << "\n";
    cout << "Number of matches: " << matches << "\n";
    cout << "Execution time: " << time_taken << " ms\n\n";
}

// Rabin-Karp
void runRabinKarpCore(string pattern) {
    int m = pattern.length();
    int n = globalText.length();
    
    int d = 256; // number of characters in the input alphabet
    int q = 101; // prime number

    int p = 0; // hash value for pattern
    int t = 0; // hash value for text
    int h = 1;
    
    int comparisons = 0;
    int matches = 0;

    // start execution timer
    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    for (int i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + globalText[i]) % q;
    }

    for (int i = 0; i <= n - m; i++) {
        if (p == t) {
            bool match = true;
            // if hash values match, check characters one by one
            for (int j = 0; j < m; j++) {
                comparisons++; 
                if (globalText[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }

            if (match) {
                cout << "Match at index: " << i << "\n";
                printHighlightedText(i, m); 
                matches++;
            }
        }

        if (i < n - m) {
            t = (d * (t - globalText[i] * h) + globalText[i + m]) % q;
            if (t < 0) {
                t = (t + q);
            }
        }
    }

    // stop timer
    auto end = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count() * 1e-6;

    cout << "Algorithm used: Rabin-Karp\n";
    cout << "Number of comparisons: " << comparisons << "\n";
    cout << "Number of matches: " << matches << "\n";
    cout << "Execution time: " << time_taken << " ms\n\n";
}

void boyerMooreSearch() {
    if (globalText.empty()) {
        cout << "Error: Please load a file or enter text first.\n";
        return;
    }

    int numPatterns;
    cout << "How many patterns do you want to search for? (Enter 1 for a single pattern): ";
    cin >> numPatterns;
    cin.ignore();

    for (int i = 0; i < numPatterns; i++) {
        string pattern;
        cout << "\nEnter pattern #" << (i + 1) << ": ";
        getline(cin, pattern);

        if (pattern.empty()) {
            cout << "Pattern cannot be empty.\n";
            continue;
        }

        cout << "\nBoyer-Moore Search Results for '" << pattern << "'\n";
        runBoyerMooreCore(pattern);
    }
}

void rabinKarpSearch() {
    if (globalText.empty()) {
        cout << "Error: Please load a file or enter text first.\n";
        return;
    }

    int numPatterns;
    cout << "How many patterns do you want to search for? (Enter 1 for a single pattern): ";
    cin >> numPatterns;
    cin.ignore();

    for (int i = 0; i < numPatterns; i++) {
        string pattern;
        cout << "\nEnter pattern #" << (i + 1) << ": ";
        getline(cin, pattern);

        if (pattern.empty()) {
            cout << "Pattern cannot be empty.\n";
            continue;
        }

        cout << "\nRabin-Karp Search Results for '" << pattern << "'\n";
        runRabinKarpCore(pattern);
    }
}

void compareAlgorithms() {
    if (globalText.empty()) {
        cout << "Error: Please load a file or enter text first.\n";
        return;
    }

    string pattern;
    cout << "Enter the pattern you want to compare between algorithms: ";
    getline(cin, pattern);

    if (pattern.empty()) {
        cout << "Pattern cannot be empty.\n";
        return;
    }

    cout << "\nALGORITHM COMPARISON\n";
    
    cout << "\n[1] Running Boyer-Moore:\n";
    runBoyerMooreCore(pattern);

    cout << "[2] Running Rabin-Karp:\n";
    runRabinKarpCore(pattern);
}

void loadFile() {
    string filename;
    cout << "Enter the name of the file to load: ";
    getline(cin, filename);

    ifstream inFile(filename); 
    if (!inFile) {
        cout << "Error: Could not open file '" << filename << "'.\n";
        return; 
    }

    string line;
    globalText = ""; 
    while (getline(inFile, line)) {
        globalText += line + "\n";
    }
    
    inFile.close(); 
    cout << "File loaded successfully. Your text is saved.\n";
}

void manualInput() {
    cout << "Enter your text manually below:\n";
    getline(cin, globalText);
    cout << "Text saved successfully.\n";
}

int main() {
    int choice = 0;

    while (choice != 6) {
        cout << "\nString Processing Menu\n";
        cout << "1. Load Text File\n";
        cout << "2. Enter Text Manually\n";
        cout << "3. Search Using Boyer-Moore\n";
        cout << "4. Search Using Rabin-Karp\n";
        cout << "5. Compare Algorithms\n";
        cout << "6. Exit\n";
        cout << "Enter your choice (1-6): ";
        
        cin >> choice; 
        cin.ignore(); 

        switch(choice) {
            case 1: loadFile(); break;
            case 2: manualInput(); break;
            case 3: boyerMooreSearch(); break;
            case 4: rabinKarpSearch(); break;
            case 5: compareAlgorithms(); break;
            case 6: cout << "Exiting program.\n"; break;
            default: cout << "Invalid choice. Please enter a number between 1 and 6.\n";
        }
    }

    return 0;
}
