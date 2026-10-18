/*
 * Name: Caitlin Rucker
 * Course: CSC450
 * Assignment: Module 5 Critical Thinking
 * Purpose: Append user input to an existing file and reverse
 *          its complete contents into a separate output file.
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

// Reverse all characters in the updated source file.
bool reverseFile(const std::string& sourceName,
                 const std::string& destinationName) {
    std::ifstream source(sourceName);

    if (!source) {
        std::cerr << "Error: Unable to open the source file.\n";
        return false;
    }

    // Read the entire file, including spaces and line breaks.
    std::string contents{
        std::istreambuf_iterator<char>(source),
        std::istreambuf_iterator<char>()
    };

    if (source.bad()) {
        std::cerr << "Error: Unable to read the source file.\n";
        return false;
    }

    source.close();

    // Reverse the complete contents, not just individual lines.
    std::reverse(contents.begin(), contents.end());

    std::ofstream destination(destinationName);

    if (!destination) {
        std::cerr << "Error: Unable to open the reversed file.\n";
        return false;
    }

    destination << contents;
    destination.close();

    if (!destination) {
        std::cerr << "Error: Unable to save the reversed file.\n";
        return false;
    }

    return true;
}

int main() {
    const std::string sourceName = "CSC450_CT5_mod5.txt";
    const std::string reversedName = "CSC450-mod5-reverse.txt";

    // Verify that the provided file exists before appending.
    std::ifstream existingFile(sourceName);

    if (!existingFile) {
        std::cerr << "Error: Place " << sourceName
                  << " in the program's working directory.\n";
        return 1;
    }

    existingFile.close();

    std::string userInput;

    std::cout << "Enter a line of text to append: ";

    if (!std::getline(std::cin, userInput)) {
        std::cerr << "Error: Unable to read user input.\n";
        return 1;
    }

    // Append mode preserves the file's existing contents.
    std::ofstream output(sourceName, std::ios::app);

    if (!output) {
        std::cerr << "Error: Unable to open the file for appending.\n";
        return 1;
    }

    output << userInput << '\n';
    output.close();

    if (!output) {
        std::cerr << "Error: Unable to save user input.\n";
        return 1;
    }

    std::cout << "Input appended to " << sourceName << '\n';

    if (!reverseFile(sourceName, reversedName)) {
        return 1;
    }

    std::cout << "Reversed contents saved to "
              << reversedName << '\n';

    return 0;
}
