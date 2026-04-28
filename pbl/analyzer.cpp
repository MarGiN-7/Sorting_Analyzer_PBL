#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

#include "analyzer.h"
#include "metrics.h"
#include "timer.h"

#include "bubble_sort.h"
#include "selection_sort.h"
#include "insertion_sort.h"
#include "merge_sort.h"
#include "quick_sort.h"
#include "count_sort.h"

using namespace std;

// ANSI color codes (disabled for Windows compatibility)
const string RESET = "";
const string BOLD = "";
const string CYAN = "";
const string GREEN = "";
const string YELLOW = "";
const string RED = "";
const string MAGENTA = "";
const string BLUE = "";

struct AlgoResult {
    string name;
    double time;
    long long comparisons;
    long long swaps;
};

string getAlgoName(int id) {
    switch (id) {
        case 1: return "Bubble Sort";
        case 2: return "Selection Sort";
        case 3: return "Insertion Sort";
        case 4: return "Merge Sort";
        case 5: return "Quick Sort";
        case 6: return "Count Sort";
        default: return "Unknown";
    }
}

void runAnalysis(const vector<int>& arr,
                 const vector<int>& algos) {

    vector<AlgoResult> results;

    for (int id : algos) {
        vector<int> temp = arr;
        Metrics m;
        double t = 0;

        switch (id) {
            case 1:
                t = measureTime(bubbleSort, temp, m);
                break;
            case 2:
                t = measureTime(selectionSort, temp, m);
                break;
            case 3:
                t = measureTime(insertionSort, temp, m);
                break;
            case 4:
                t = measureTime(mergeSort, temp, m);
                break;
            case 5:
                t = measureTime(quickSort, temp, m);
                break;
            case 6:
                t = measureTime(countSort, temp, m);
                break;
            default:
                continue;
        }

        results.push_back({getAlgoName(id), t, m.comparisons, m.swaps});
    }

    // Print beautiful table header
    cout << "\n\n";
    cout << CYAN << BOLD;
    cout << "=====================================================================\n";
    cout << "| " << setw(18) << left << "Algorithm" << " | "
         << setw(14) << left << "Time (ms)" << " | "
         << setw(14) << left << "Comparisons" << " | "
         << setw(14) << left << "Swaps" << " |\n";
    cout << "=====================================================================\n";
    cout << RESET;

    // Print rows with alternating colors
    for (size_t i = 0; i < results.size(); i++) {
        const AlgoResult& res = results[i];
        string color;

        if (i % 2 == 0) {
            color = GREEN;
        } else {
            color = BLUE;
        }

        cout << color << BOLD << "| ";
        cout << setw(18) << left << res.name << " | ";
        cout << RESET << color;
        cout << setw(14) << fixed << setprecision(4) << left << res.time << " | ";
        cout << setw(14) << left << res.comparisons << " | ";
        cout << setw(14) << left << res.swaps << " |";
        cout << RESET << "\n";
    }

    // Print table footer
    cout << CYAN << BOLD;
    cout << "=====================================================================\n";
    cout << RESET;

    // Print performance summary
    if (!results.empty()) {
        double minTime = results[0].time;
        double maxTime = results[0].time;
        int fastestIdx = 0, slowestIdx = 0;

        for (size_t i = 1; i < results.size(); i++) {
            if (results[i].time < minTime) {
                minTime = results[i].time;
                fastestIdx = i;
            }
            if (results[i].time > maxTime) {
                maxTime = results[i].time;
                slowestIdx = i;
            }
        }

        cout << "\n" << MAGENTA << BOLD << "--- PERFORMANCE SUMMARY ---" << RESET << "\n";
        cout << GREEN << "FASTEST: " << RESET << results[fastestIdx].name
             << " (" << fixed << setprecision(4) << results[fastestIdx].time << " ms)\n";
        cout << RED << "SLOWEST: " << RESET << results[slowestIdx].name
             << " (" << fixed << setprecision(4) << results[slowestIdx].time << " ms)\n";
        cout << YELLOW << "DIFFERENCE: " << RESET
             << fixed << setprecision(4) << (maxTime - minTime) << " ms\n";
    }

    cout << "\n" << CYAN << BOLD << "=====================================================================\n" << RESET;
}