#pragma once

#include<unordered_map>
#include<unordered_set>
#include<vector>

using namespace std;

class KeywordsInFile {
private:
    //hash table that stores all keyword occurances
    unordered_map<string, int> keywordOccurances;
    //vector of hashtable that store occurances by line
    vector<unordered_map<string, int>> keywordOccurancesByLine;
public:
    //disabling the default constructor
    KeywordsInFile() = delete;
    //parameterized constructor
    KeywordsInFile(const string& filename_with_keywords, const string& filename_with_text);
    //returns true if the specificed keyword was found
    bool KeywordFound(const string& keyword) const;
    //returns the number of specificed keyward in the given line
    int KeywordInLine(const string& keyword, const int& line_number) const;
    //return the total occurances of specificed word
    int TotalOccurrences(const string& keyword) const;
    //return keyword occurances as a string
    string DisplayKeywordOccurances() const;
};

//stream insertion overloading
ostream &operator<<(ostream &output, const KeywordsInFile& rhs);
