#pragma once
#include <cstdio>
#include <string>
using namespace std;

class FileReader {
FILE* file;
public:
    FileReader(const string*);
    ~FileReader();
    string getData();
    bool isOpen() const { return file != nullptr; }
};
