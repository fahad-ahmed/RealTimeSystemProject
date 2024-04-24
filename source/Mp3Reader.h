#pragma once
#ifndef MP3READER_H
#define MP3READER_H

#include <string>
#include <fstream>


class Mp3Reader {
public:
    Mp3Reader();
    ~Mp3Reader();

    void setFilePath(const std::string& filePath);
    bool openFile();
    void closeFile();
    std::pair<char*, std::streamsize> readData(int BUFFER_SIZE);


private:
    std::string filePath;
    std::ifstream fileStream;
    char buffer[4096];
};

#endif // MP3READER_H
