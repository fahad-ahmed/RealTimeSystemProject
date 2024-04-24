#pragma once
#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include "tinyxml2.h"
#include <string>

class ConfigReader {
public:
    static ConfigReader& getInstance();
    bool loadConfig(const std::string& filepath);

    std::string getServerAddress() const;
    int getServerPort() const;
    std::string getMountPoint() const;
    std::string getMountPassword() const;
    float getRmsThreshold() const;
    bool isEdfEnabled() const;
    bool isPreemptionEnabled() const;

    int aperiodicPriority()const;
    int aperiodicExectionTime() const;
    int aperiodicDeadline() const;

    int periodicPriority()const;
    int periodicExectionTime() const;
    int periodicDeadline() const;
    int periodicTaskPeriod() const;

    int sporadicPriority()const;
    int sporadicExectionTime() const;
    int sporadicDeadline() const;

    std::string getLocalMusicFileName() const;



private:
    ConfigReader() = default; // Private Constructor
    ConfigReader(const ConfigReader&) = delete; // Prevent copying
    ConfigReader& operator=(const ConfigReader&) = delete; // Prevent assignment

    tinyxml2::XMLDocument doc;
};

#endif // CONFIGREADER_H

