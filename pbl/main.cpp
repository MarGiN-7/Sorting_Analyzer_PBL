#include <iostream>
#include <vector>
#include <string>

#include "input_handler.h"
#include "data_generator.h"
#include "analyzer.h"

using namespace std;

// ANSI color codes (disabled for Windows compatibility)
const string RESET = "";
const string BOLD = "";
const string CYAN = "";
const string GREEN = "";
const string YELLOW = "";
const string MAGENTA = "";

void printTitle() {
    cout << CYAN << BOLD;
    cout << "====================================================\n";
    cout << "                                                    \n";
    cout << "   SORTING PERFORMANCE ANALYZER                    \n";
    cout << "                                                    \n";
    cout << "====================================================\n";
    cout << RESET;
}

int main() {
    printTitle();

    vector<int> arr;
    int method = getInputMethod();

    cout << "\n" << YELLOW << "────────────────────────────────────────────────────\n" << RESET;

    if (method == 1) {
        cout << GREEN << "✓ Data Generation Mode Selected\n" << RESET;
        int n = getArraySize();
        int type = getDataType();
        arr = generateData(n, type);
        cout << GREEN << "✓ Data generated successfully.\n" << RESET;
        cout << CYAN << "\nGenerated Array (" << arr.size() << " elements):\n" << RESET;
        cout << YELLOW << "[ ";
        for (size_t i = 0; i < arr.size() && i < 20; i++) {
            cout << arr[i] << " ";
        }
        if (arr.size() > 20) cout << "... ";
        cout << "]\n" << RESET;
    }
    else if (method == 2) {
        cout << GREEN << "✓ Manual Input Mode Selected\n" << RESET;
        arr = getManualArray();
        cout << GREEN << "✓ Array captured successfully.\n" << RESET;
        cout << CYAN << "\nInput Array:\n" << RESET;
        cout << YELLOW << "[ ";
        for (int x : arr) {
            cout << x << " ";
        }
        cout << "]\n" << RESET;
    }
    else {
        cout << "\033[31m" << BOLD << "✗ Invalid choice. Exiting...\n" << RESET;
        return 0;
    }

    cout << YELLOW << "────────────────────────────────────────────────────\n" << RESET;

    vector<int> algos = getAlgorithmChoices();

    if (algos.empty()) {
        cout << "\033[31m" << BOLD << "✗ No algorithms selected. Exiting...\n" << RESET;
        return 0;
    }

    runAnalysis(arr, algos);

    cout << "\n" << MAGENTA << BOLD;
    cout << "====================================================\n";
    cout << "                                                    \n";
    cout << "          ANALYSIS COMPLETE                         \n";
    cout << "                                                    \n";
    cout << "====================================================\n";
    cout << RESET;

    return 0;
}