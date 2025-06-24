#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <set>
#include <QString>
#include "keywords.h"

using namespace std;

bool search_word_in_keywords(const string &str) {
    for(int it = 0; it < KEY_WORDS.size(); it++) {
        if(KEY_WORDS[it] == str){
            return true;
        }
    }

    return false;
}

QString convert_in_QString(const std::string &str) {
    return QString::fromUtf8(str.c_str());
}

vector<QString> search_id(const string &str) {
    regex id(R"([_a-zA-Z][a-zA-Z0-9_\.]*)");

    auto begin = sregex_iterator(str.begin(), str.end(), id);
    auto end = sregex_iterator();

    vector<QString> ids;
    for (auto it = begin; it != end; ++it) {
        if(!search_word_in_keywords(it->str()))
            ids.push_back(convert_in_QString(it->str()));
    }

    return ids;
}

vector<string> vector_append(vector<string> arr1, vector<string> arr2) {

    for(int i = 0; i < arr2.size(); i++) {
        arr1.push_back(arr2[i]);
    }

    return arr1;
}

set<QString> create_set(vector<QString> code) {
    set<QString> result;
    for (int i = 0; i < code.size(); i++) {
        result.insert(code[i]);
    }
    return result;
}
