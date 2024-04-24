#include "ConfigReader.h"

ConfigReader& ConfigReader::getInstance() {
    static ConfigReader instance;
    return instance;
}

bool ConfigReader::loadConfig(const std::string& filepath) {
    return doc.LoadFile(filepath.c_str()) == tinyxml2::XML_SUCCESS;
}

std::string ConfigReader::getServerAddress() const {
    return doc.FirstChildElement("Configuration")
        ->FirstChildElement("ShoutCastServer")
        ->FirstChildElement("ServerAddress")
        ->GetText();
}

int ConfigReader::getServerPort() const {
    int port;
    doc.FirstChildElement("Configuration")
        ->FirstChildElement("ShoutCastServer")
        ->FirstChildElement("ServerPort")
        ->QueryIntText(&port);
    return port;
}

std::string ConfigReader::getMountPoint() const {
    return doc.FirstChildElement("Configuration")
        ->FirstChildElement("ShoutCastServer")
        ->FirstChildElement("MountPoint")
        ->GetText();
}

std::string ConfigReader::getMountPassword() const {
    return doc.FirstChildElement("Configuration")
        ->FirstChildElement("ShoutCastServer")
        ->FirstChildElement("MountPassword")
        ->GetText();
}

float ConfigReader::getRmsThreshold() const {
    float threshold;
    doc.FirstChildElement("Configuration")
        ->FirstChildElement("Microphone")
        ->FirstChildElement("RmsThreshold")
        ->QueryFloatText(&threshold);
    return threshold;
}

bool ConfigReader::isEdfEnabled() const {
    int isEdfEnabled;
    doc.FirstChildElement("Configuration")
        ->FirstChildElement("IsEdfEnabled")
        ->QueryIntText(&isEdfEnabled);
    
    if (isEdfEnabled == 1) return true;
    return false;
}

bool ConfigReader::isPreemptionEnabled() const
{
    int isPreemptionEnabled;
    isPreemptionEnabled = doc.FirstChildElement("Configuration")
        ->FirstChildElement("IsPreemptionEnabled")
        ->QueryIntText(&isPreemptionEnabled);

    if (isPreemptionEnabled == 1) return true;
    return false;
}

int ConfigReader::aperiodicPriority() const
{
    int priority;
    doc.FirstChildElement("Configuration")
        ->FirstChildElement("AperiodicTask")
        ->FirstChildElement("Priority")
        ->QueryIntText(&priority);
    return priority;

}

int ConfigReader::aperiodicDeadline() const
{
    int deadline;
    doc.FirstChildElement("Configuration")
        ->FirstChildElement("AperiodicTask")
        ->FirstChildElement("Deadline")
        ->QueryIntText(&deadline);
    return deadline;

}



int ConfigReader::aperiodicExectionTime() const
{
    int executionTime;
    doc.FirstChildElement("Configuration")
        ->FirstChildElement("AperiodicTask")
        ->FirstChildElement("ExecutionTime")
        ->QueryIntText(&executionTime);
    return executionTime;
    return 0;
}


int ConfigReader::periodicPriority() const
{
    int priority;
    doc.FirstChildElement("Configuration")
        ->FirstChildElement("PeriodicTask")
        ->FirstChildElement("Priority")
        ->QueryIntText(&priority);
    return priority;

}

int ConfigReader::periodicDeadline() const
{
    int deadline;
    doc.FirstChildElement("Configuration")
        ->FirstChildElement("PeriodicTask")
        ->FirstChildElement("Deadline")
        ->QueryIntText(&deadline);
    return deadline;

}

int ConfigReader::periodicTaskPeriod() const
{
    int period;
    doc.FirstChildElement("Configuration")
        ->FirstChildElement("PeriodicTask")
        ->FirstChildElement("Period")
        ->QueryIntText(&period);
    return period;
    return 0;
}



int ConfigReader::periodicExectionTime() const
{
    int executionTime;
    doc.FirstChildElement("Configuration")
        ->FirstChildElement("PeriodicTask")
        ->FirstChildElement("ExecutionTime")
        ->QueryIntText(&executionTime);
    return executionTime;
    return 0;
}

int ConfigReader::sporadicPriority() const
{
    int priority;
    doc.FirstChildElement("Configuration")
        ->FirstChildElement("SporadicTask")
        ->FirstChildElement("Priority")
        ->QueryIntText(&priority);
    return priority;

}

int ConfigReader::sporadicDeadline() const
{
    int deadline;
    doc.FirstChildElement("Configuration")
        ->FirstChildElement("SporadicTask")
        ->FirstChildElement("Deadline")
        ->QueryIntText(&deadline);
    return deadline;

}

std::string ConfigReader::getLocalMusicFileName() const
{
    return doc.FirstChildElement("Configuration")
        ->FirstChildElement("LocalMusicFileName")
        ->GetText();
}



int ConfigReader::sporadicExectionTime() const
{
    int executionTime;
    doc.FirstChildElement("Configuration")
        ->FirstChildElement("SporadicTask")
        ->FirstChildElement("ExecutionTime")
        ->QueryIntText(&executionTime);
    return executionTime;
    return 0;
}
