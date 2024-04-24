#include "Mp3Reader.h"
#include "Mp3Reader.h"
#include <iostream>
#include <utility> // For std::pair

Mp3Reader::Mp3Reader() {}

Mp3Reader::~Mp3Reader() {
    closeFile();
}

void Mp3Reader::setFilePath(const std::string& filePath) {
    this->filePath = filePath;
}

bool Mp3Reader::openFile() {
    fileStream.open(filePath, std::ios::binary);
    if (!fileStream.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return false;
    }

    return true;
}

void Mp3Reader::closeFile() {
    if (fileStream.is_open()) {
        fileStream.close();
    }
}

std::pair<char*, std::streamsize> Mp3Reader::readData(int BUFFER_SIZE) {
    if (!fileStream.is_open()) {
        std::cerr << "File is not open" << std::endl;
        return std::make_pair(nullptr, (std::streamsize)0);
    }

    fileStream.read(buffer, BUFFER_SIZE);
    return std::make_pair(buffer, fileStream.gcount());
}


