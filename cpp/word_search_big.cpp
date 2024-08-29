#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <fstream>
std::ofstream file;

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

int main() {
    std::string word = "pianissimo"; // Replace with the word you want to search
    file.open("cpp-results.csv");
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }
    file << "end,middle,start"<<std::endl;
    for (int i = 0; i < 100; ++i) {
        file << searchWordInFile("../text/big-end.txt", word) << ",";
        file << searchWordInFile("../text/big-middle.txt", word) << ",";
        file << searchWordInFile("../text/big-start.txt", word) << std::endl;
    }
    file.close();
    std::cout << "Data written to output.txt successfully." << std::endl;

    return 0;
}
