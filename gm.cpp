#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <windows.h>
using namespace std;
string lowerText(string a)
{
    for (int i = 0; i < a.length(); i++)
    {
        a[i] = tolower(a[i]);
    }
    return a;
}
// Simple brute force approach - checks every position one by one it will shift one by one charachter
void bruteForce(const string &text, const string &pattern)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    int comparisons = 0;
    int matches = 0;
    int n = text.length();
    int m = pattern.length();
    auto start = chrono::high_resolution_clock::now();
    // Go through each position in text from 0 to the final one it checks it all
    for (int i = 0; i <= n - m; i++)
    {
        int j = 0;
        // we have to reset 0 with every iteration of outer loop as j is measure of
        // how many consecutive characters of the pattern have currently matched the text starting at a given position
        // Trying to match pattern starting at position i(0)
        while (j < m)
        {
            comparisons++;
            if (text[i + j] == pattern[j])
            {
                j++;
            }
            else
            {
                break;
            }
        }
        // If we matched the whole pattern
        if (j == m)
        {
            matches++;
            if (n < 1000) // practical output-control condition added for usability and performance
            {
                SetConsoleTextAttribute(h, 10);
                cout << "   Match found at position: " << i << endl;
                SetConsoleTextAttribute(h, 7);
            }
        }
    }
    auto end = chrono::high_resolution_clock::now();
    double timeTaken = chrono::duration<double, milli>(end - start).count();
    SetConsoleTextAttribute(h, 11);
    cout << "   Brute Force Results:" << endl;
    SetConsoleTextAttribute(h, 7);
    cout << "   - Comparisons made: " << comparisons << endl;
    cout << "   - Matches found: " << matches << endl;
    cout << "   - Time taken: " << timeTaken << " ms" << endl;
}
// Boyer-Moore algorithm - smarter searching from right to left
void boyerMoore(const string &text, const string &pattern)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    int comparisons = 0;
    int matches = 0;
    int n = text.length();
    int m = pattern.length();
    // Build bad character table
    int badChar[256];
    for (int i = 0; i < 256; i++)
    {
        badChar[i] = -1;
    }
    for (int i = 0; i < m; i++)
    {
        badChar[(int)pattern[i]] = i;
    }
    auto start = chrono::high_resolution_clock::now();
    int shift = 0;
    // Keep searching until we reach the end
    while (shift <= n - m)
    {
        int j = m - 1;
        // Match from right to left
        while (j >= 0)
        {
            comparisons++;
            if (pattern[j] == text[shift + j])
            {
                j--;
            }
            else
            {
                break;
            }
        }
        // Found a complete match
        if (j < 0)
        {
            matches++;
            if (n < 1000)
            {
                SetConsoleTextAttribute(h, 10);
                cout << "   Match found at position: " << shift << endl;
                SetConsoleTextAttribute(h, 7);
            }

            // Correct shift calculation after finding a match
            if (shift + m < n)
            {
                shift += m - badChar[(unsigned char)text[shift + m]];
            }
            else
            {
                shift += 1;
            }

            // Ensure shift is always positive
            if (shift <= 0)
            {
                shift = 1;
            }
        }
        else
        {
            int badIndex = badChar[(unsigned char)text[shift + j]];

            if (j > badIndex)
            {
                shift += j - badIndex;
            }
            else
            {
                shift += 1;
            }
        }
    }
    auto end = chrono::high_resolution_clock::now();
    double timeTaken = chrono::duration<double, milli>(end - start).count();
    SetConsoleTextAttribute(h, 13);
    cout << "   Boyer-Moore Results:" << endl;
    SetConsoleTextAttribute(h, 7);
    cout << "   - Comparisons made: " << comparisons << endl;
    cout << "   - Matches found: " << matches << endl;
    cout << "   - Time taken: " << timeTaken << " ms" << endl;
}
// KMP algorithm - uses pattern preprocessing to avoid redundant comparisons
void kmpSearch(const string &text, const string &pattern)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    int n = text.length();
    int m = pattern.length();
    int comparisons = 0;
    int matches = 0;
    // Build LPS array (Longest Prefix Suffix)
    int lps[m];
    for (int i = 0; i < m; i++)
    {
        lps[i] = 0;
    }
    int j = 0;
    for (int i = 1; i < m; i++)
    {
        while (j > 0 && pattern[i] != pattern[j])
        {
            j = lps[j - 1];
        }
        if (pattern[i] == pattern[j])
        {
            j++;
        }
        lps[i] = j;
    }
    auto start = chrono::high_resolution_clock::now();
    j = 0;
    // Search through the text
    for (int i = 0; i < n; i++)
    {
        comparisons++;
        while (j > 0 && text[i] != pattern[j])
        {
            j = lps[j - 1];
        }
        if (text[i] == pattern[j])
        {
            j++;
        }
        // Pattern found
        if (j == m)
        {
            matches++;
            if (n < 1000)
            {
                SetConsoleTextAttribute(h, 10);
                cout << "   Match found at position: " << i - m + 1 << endl;
                SetConsoleTextAttribute(h, 7);
            }
            j = lps[j - 1];
        }
    }
    auto end = chrono::high_resolution_clock::now();
    double timeTaken = chrono::duration<double, milli>(end - start).count();
    SetConsoleTextAttribute(h, 14);
    cout << "   KMP Results:" << endl;
    SetConsoleTextAttribute(h, 7);
    cout << "   - Comparisons made: " << comparisons << endl;
    cout << "   - Matches found: " << matches << endl;
    cout << "   - Time taken: " << timeTaken << " ms" << endl;
}
// Read content from a file
string readFromFile(const string &filename)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    ifstream file(filename);
    if (!file.is_open())
    {
        SetConsoleTextAttribute(h, 12);
        cout << "   Error: Could not open file " << filename << endl;
        SetConsoleTextAttribute(h, 7);
        return "";
    }
    string content, line;
    while (getline(file, line))
    {
        content += line + "\n";
    }
    file.close();
    return content;
}
// Run all three algorithms on the same input
void runTestCase(const string &text, const string &pattern, const string &name)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    cout << endl;
    SetConsoleTextAttribute(h, 9);
    cout << "+========================================+" << endl;
    cout << "   " << name << endl;
    cout << "+========================================+" << endl;
    SetConsoleTextAttribute(h, 7);
    cout << "   Text length: " << text.length() << " characters" << endl;
    cout << "   Pattern length: " << pattern.length() << " characters" << endl;
    cout << endl;
    bruteForce(text, pattern);
    cout << endl;
    boyerMoore(text, pattern);
    cout << endl;
    kmpSearch(text, pattern);
}
// Run some pre-made test cases
void predefinedTests()
{
    // Test 1: Small simple case
    string smallText = "";
    for (int i = 0; i < 50000; i++)
    {
        smallText += "ABCD";
    }
    smallText += "ABABCABAB";
    string smallPattern = "ABABCABAB";
    runTestCase(smallText, smallPattern, "Test 1: Small Pattern Search");
    // Test 2: Pattern at the beginning
    string bestText = "ABABCABAB";
    for (int i = 0; i < 500000; i++)
    {
        bestText += char('A' + i % 26);
    }
    string bestPattern = "ABABCABAB";
    runTestCase(bestText, bestPattern, "Test 2: Pattern at Start");
    // Test 3: Lots of false matches (worst case scenario)
    string worstText = "";
    for (int i = 0; i < 100000; i++)
    {
        worstText += "AAAA";
    }
    worstText += "AAAB";
    string worstPattern = "AAAAAAAB";
    runTestCase(worstText, worstPattern, "Test 3: Many Partial Matches");
    // Test 4: Multiple occurrences of pattern
    string multiText = "";
    for (int i = 0; i < 100000; i++)
    {
        multiText += "ABCDEFGH";
    }
    string multiPattern = "ABCDEFGH";
    runTestCase(multiText, multiPattern, "Test 4: Multiple Matches");
}
// Let user type their own text and pattern
void customInput()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    string text, pattern;
    cin.ignore();
    SetConsoleTextAttribute(h, 11);
    cout << "   Enter your text: ";
    SetConsoleTextAttribute(h, 7);
    getline(cin, text);
    SetConsoleTextAttribute(h, 11);
    cout << "   Enter pattern to search: ";
    SetConsoleTextAttribute(h, 7);
    getline(cin, pattern);
    text = lowerText(text);
    pattern = lowerText(pattern);
    if (text.empty() || pattern.empty())
    {
        SetConsoleTextAttribute(h, 12);
        cout << "   Error: Both text and pattern are required!" << endl;
        SetConsoleTextAttribute(h, 7);
        return;
    }
    if (pattern.length() > text.length())
    {
        SetConsoleTextAttribute(h, 12);
        cout << "   Error: Pattern is longer than text!" << endl;
        SetConsoleTextAttribute(h, 7);
        return;
    }
    runTestCase(text, pattern, "Custom Input Test");
}
// Read text and pattern from files
void fileInput()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    string textFile, patternFile;
    SetConsoleTextAttribute(h, 11);
    cout << "   Enter text filename: ";
    SetConsoleTextAttribute(h, 7);
    cin >> textFile;
    SetConsoleTextAttribute(h, 11);
    cout << "   Enter pattern filename: ";
    SetConsoleTextAttribute(h, 7);
    cin >> patternFile;
    string text = lowerText(readFromFile(textFile));
    string pattern = lowerText(readFromFile(patternFile));
    if (!text.empty() && !pattern.empty())
    {
        runTestCase(text, pattern, "File Input Test");
    }
    if (pattern.length() > text.length())
    {
        SetConsoleTextAttribute(h, 12);
        cout << "   Error: Pattern is longer than text!" << endl;
        SetConsoleTextAttribute(h, 7);
        return;
    }
}
void simplePlagiarismCheck()
{
    string file1, file2;
    cout << endl << "   Enter first document filename: ";
    cin >> file1;
    cout << "   Enter second document filename: ";
    cin >> file2;

    string text1 = lowerText(readFromFile(file1));
    string text2 = lowerText(readFromFile(file2));

    if (text1 == "" || text2 == "")
    {
        cout << "   Error reading files!" << endl;
        return;
    }

    const int MAX = 10000;
    string w1[MAX], w2[MAX];
    int n1 = 0, n2 = 0;
    string word = "";

    for (int i = 0; i < text1.length(); i++)
    {
        if (text1[i] == ' ' || text1[i] == '\n' || text1[i] == '\t')
        {
            if (word != "")
            {
                w1[n1++] = word;
            }
            word = "";
        }
        else
        {
            word += text1[i];
        }
    }
    if (word != "")
    {
        w1[n1++] = word;
    }

    word = "";
    for (int i = 0; i < text2.length(); i++)
    {
        if (text2[i] == ' ' || text2[i] == '\n' || text2[i] == '\t')
        {
            if (word != "")
            {
                w2[n2++] = word;
            }
            word = "";
        }
        else
        {
            word += text2[i];
        }
    }
    if (word != "")
    {
        w2[n2++] = word;
    }

    int matches = 0;

    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            int k = 0;
            while (i + k < n1 && j + k < n2 && w1[i + k] == w2[j + k])
            {
                k++;
            }
            if (k >= 3) // 3-word sequence match
            {
                matches += k;
                i += k - 1;
                break;
            }
        }
    }

    int total = (n1 < n2) ? n1 : n2;
    double similarity = (matches * 100.0) / total;

    cout << endl;
    cout << "   Words in document 1: " << n1 << endl;
    cout << "   Words in document 2: " << n2 << endl;
    cout << "   Sequential matches: " << matches << endl;
    cout << "   Similarity: " << similarity << "%" << endl;

    if (similarity > 70)
    {
        cout << "   Result: HIGH plagiarism risk" << endl;
    }
    else if (similarity > 40)
    {
        cout << "   Result: MEDIUM plagiarism risk" << endl;
    }
    else
    {
        cout << "   Result: LOW plagiarism risk" << endl;
    }
}
main()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    int choice;
    do
    {
        // Display menu
        cout << endl;
        SetConsoleTextAttribute(h, 14);
        cout << "+===========================================+" << endl;
        cout << "|   STRING MATCHING ALGORITHMS PROGRAM       |" << endl;
        cout << "+===========================================+" << endl;
        SetConsoleTextAttribute(h, 10);
        cout << "|   1. Run Predefined Test Cases             |" << endl;
        cout << "|   2. Enter Custom Text & Pattern           |" << endl;
        cout << "|   3. Load from Files                       |" << endl;
        cout << "|   4 Plagiarism Detection(Compare txt files)|" << endl;
        cout << "|   5. Exit Program                          |" << endl;
        SetConsoleTextAttribute(h, 14);
        cout << "+============================================+" << endl;
        SetConsoleTextAttribute(h, 11);
        cout << "   Enter your choice (1-5): ";
        SetConsoleTextAttribute(h, 7);
        cin >> choice;
        if (choice == 1)
        {
            system("cls");
            predefinedTests();
        }
        else if (choice == 2)
        {
            system("cls");
            customInput();
        }
        else if (choice == 3)
        {
            system("cls");
            fileInput();
        }
        else if (choice == 4)
        {
            system("cls");
            simplePlagiarismCheck();
        }
        else if (choice == 5)
        {
            SetConsoleTextAttribute(h, 10);
            cout << endl
                 << "   Thanks for using the program. Goodbye!" << endl
                 << endl;
            SetConsoleTextAttribute(h, 7);
        }
        else
        {
            SetConsoleTextAttribute(h, 12);
            cout << "   Invalid choice! Please enter 1, 2, 3, 4, or 5." << endl;
            SetConsoleTextAttribute(h, 7);
        }
    } while (choice != 5);
}