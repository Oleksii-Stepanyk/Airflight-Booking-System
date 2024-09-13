#include "FileReader.h"

FileReader::FileReader(const string* filename)
{
    file = fopen(filename->c_str(), "r");
    if (file == nullptr)
    {
        throw "File not found";
    }
}

string FileReader::getData()
{
    string result;
    while (!feof(file))
    {
        char buffer[256];
        fgets(buffer, 256, file);
        result += buffer;
    }
    return result;
}

FileReader::~FileReader()
{
    fclose(file);
}
