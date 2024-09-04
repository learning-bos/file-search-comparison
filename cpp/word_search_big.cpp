#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <algorithm>
#include <functional>

using namespace std;
using namespace std::chrono;
std::ofstream file;

const int d = 256;  // Number of characters in the input alphabet (ASCII)
const int q = 101;  // A prime number for hashing

enum class SearchMethod {
    RabinKarp,
    BoyerMoore,
    StdSearch
};


long long rabinKarpSearch(const string& filePath, const string& word) {
    ifstream file(filePath, ios::in | ios::binary);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filePath << endl;
        return -1;  // Indicate an error with a negative value
    }

    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    int n = text.length();
    int m = word.length();

    if (m > n) {
        return -1;  // If the pattern is longer than the text, return immediately
    }

    int h = 1;
    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    int p = 0; // Hash value for the pattern (word)
    int t = 0; // Hash value for the text

    // Precompute the hash value for the pattern and the first window of text
    for (int i = 0; i < m; i++) {
        p = (d * p + word[i]) % q;
        t = (d * t + text[i]) % q;
    }

    auto start = high_resolution_clock::now();  // Start timing

    // Slide the pattern over the text one by one
    for (int i = 0; i <= n - m; i++) {
        // Check the hash values of the current window of text and the pattern
        if (p == t) {
            bool match = true;
            // Check characters one by one if hash values match
            for (int j = 0; j < m; j++) {
                if (text[i + j] != word[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                auto end = high_resolution_clock::now();
                return duration_cast<milliseconds>(end - start).count();
            }
        }

        // Calculate hash value for the next window of text
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;
            if (t < 0) {
                t = (t + q);  // Make sure t is positive
            }
        }
    }

    auto end = high_resolution_clock::now();
    return duration_cast<milliseconds>(end - start).count();
}

auto searchInFileBoyerMoore(ifstream& file, const string& word) {
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    auto start = high_resolution_clock::now();

    auto it = search(content.begin(), content.end(), 
                     boyer_moore_searcher(word.begin(), word.end()));

    auto end = high_resolution_clock::now();
    long long elapsedMilliseconds = duration_cast<milliseconds>(end - start).count();

    return elapsedMilliseconds;
}

double searchWordInFile(const std::string& filePath, const std::string& word) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return 0;
    }

    std::string line;
    bool found = false;
    auto start = std::chrono::high_resolution_clock::now();

    while (std::getline(file, line)) {
        if (line.find(word) != std::string::npos) {
            found = true;
            break;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    /*if (found) {
        //std::cout << "Word \"" << word << "\" found in file." << std::endl;
    } else {
        //std::cout << "Word \"" << word << "\" not found in file." << std::endl;
    }

    //std::cout << "Time taken: " << duration.count() * 1000 << " milliseconds." << std::endl;
    */
    return duration.count() * 1000;
}

void printCSV(SearchMethod method, string filePath="cpp-results.csv") {
    string word = "pianissimo";
    file.open("cpp-results.csv");
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
    }
    file << "end,middle,start"<<std::endl;
    long long elapsedMilliseconds = 0;

    switch(method){
        case SearchMethod::RabinKarp:
            for (int i = 0; i < 100; ++i) {
                elapsedMilliseconds = rabinKarpSearch("../text/big-end.txt", word);
                file << elapsedMilliseconds << ",";
                elapsedMilliseconds = rabinKarpSearch("../text/big-middle.txt", word);
                file << elapsedMilliseconds << ",";
                elapsedMilliseconds = rabinKarpSearch("../text/big-start.txt", word);
                file << elapsedMilliseconds << std::endl;
            }
            break;
        case SearchMethod::BoyerMoore:
            for (int i = 0; i < 100; ++i) {
                string filePath = "../text/big-end.txt";
                ifstream filea(filePath, ios::in | ios::binary);
                elapsedMilliseconds = searchInFileBoyerMoore(filea, word);
                file << elapsedMilliseconds << ",";
                filePath = "../text/big-middle.txt";
                ifstream fileb(filePath, ios::in | ios::binary);
                elapsedMilliseconds = searchInFileBoyerMoore(fileb, word);
                file << elapsedMilliseconds << ",";
                filePath = "../text/big-start.txt";
                ifstream filec(filePath, ios::in | ios::binary);
                elapsedMilliseconds = searchInFileBoyerMoore(filec, word);
                file << elapsedMilliseconds << std::endl;
            }
            break;
        case SearchMethod::StdSearch:
            // TODO: implement std::search
            
             for (int i = 0; i < 100; ++i) {
                string filePath = "../text/big-end.txt";
                elapsedMilliseconds = searchWordInFile(filePath, word);
                file << elapsedMilliseconds << ",";
                filePath = "../text/big-middle.txt";
                elapsedMilliseconds = searchWordInFile(filePath, word);
                file << elapsedMilliseconds << ",";
                filePath = "../text/big-start.txt";
                elapsedMilliseconds = searchWordInFile(filePath, word);
                file << elapsedMilliseconds << std::endl;
            }
            break;
    }
    file.close();
    std::cout << "Data written to output.txt successfully." << std::endl;
}

int main() {
    //printCSV(SearchMethod::RabinKarp);
    //printCSV(SearchMethod::BoyerMoore, "boyermoore-cpp-results.csv");
    //printCSV(SearchMethod::StdSearch, "stdsearch-cpp-results.csv");
    return 0;
}
