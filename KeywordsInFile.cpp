#include<unordered_map>
#include<unordered_set>
#include<vector>
#include<fstream>
#include<iostream>

#include "KeywordsInFile.hpp"

using namespace std;

//paramaterized constructor
KeywordsInFile::KeywordsInFile(const string& filename_with_keywords, const string& filename_with_text) {
    //read the keyword file
    ifstream keywordFile(filename_with_keywords);
    if (keywordFile.fail()) {
        cerr << "Failed to open keyword file!" << endl;
        exit(1);
    }
    //initialize all the keywords to be 0
    char a;
    string word = "";
    while (keywordFile.get(a)) {
        if (keywordFile.eof()) {
            cout << "end of file";
        }
        else if (isalpha(a)) {
            word += a;
        } else {
            if (!word.empty()) {
                keywordOccurances.insert({word, 0});
            }
            word = "";
        }
    }
    //storing the last word (only needed when the file ends with a keyword)
    if (!word.empty()) {
        keywordOccurances.insert({word, 0});
        word = "";
    }
    //close the keyword file
    keywordFile.close();
    //read the text file
    ifstream textFile(filename_with_text);
    if (textFile.fail()) {
        cerr << "Failed to open text file!" << endl;
        exit(1);
    }
    //store words into both containers
    int line = 0;
    keywordOccurancesByLine.push_back({});
    while (textFile.get(a)) {
        if (isalpha(a)) {
            word += a;
        } else if (keywordOccurances.count(word) == 1){
            keywordOccurances.at(word)++;
            if (keywordOccurancesByLine[line].count(word) == 0) {
                keywordOccurancesByLine[line].insert({word, 1});
            } else {
                keywordOccurancesByLine[line].at(word)++;
            }
            word = "";
        } else {
            word = "";
        }
        if (a == '\n'){
            keywordOccurancesByLine.push_back({});
            line++;
        }
    }
    //storing the last word (only needed when the file ends with a keyword)
    if (!word.empty() && keywordOccurances.count(word) == 1) {
        keywordOccurances.at(word)++;
        if (keywordOccurancesByLine[line].count(word) == 0) {
            keywordOccurancesByLine[line].insert({word, 1});
        } else {
            keywordOccurancesByLine[line].at(word)++;
        }
    }
    //close the text file
    textFile.close();
}

//returns true if the specificed keyword was found
bool KeywordsInFile::KeywordFound(const string& keyword) const {
    return keywordOccurances.count(keyword) == 1;
}

//returns the number of specificed keyword in the given line
int KeywordsInFile::KeywordInLine(const string& keyword, const int& line_number) const {
    if (line_number-1 >= keywordOccurancesByLine.size() || line_number-1 < 0) {
        return 0;
    }
    return (keywordOccurancesByLine[line_number-1].count(keyword) == 0) ? 0
    : keywordOccurancesByLine[line_number-1].at(keyword);
}

//return the total occurances of specificed word
int KeywordsInFile::TotalOccurrences(const string& keyword) const {
    return keywordOccurances.count(keyword) == 0 ? 0 : keywordOccurances.at(keyword);
}

//return keyword occurances as a string
string KeywordsInFile::DisplayKeywordOccurances() const {
    string occurances = "";
    for (const auto& word: keywordOccurances) {
        occurances += word.first;
        occurances += " : ";
        occurances += to_string(word.second);
        occurances += "\n";
    }
    return occurances;
}

//stream insertion overloading
ostream &operator<<(ostream& output, const KeywordsInFile& rhs) {
    output << rhs.DisplayKeywordOccurances();
    return output;
}