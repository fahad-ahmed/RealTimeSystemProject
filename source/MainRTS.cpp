#include <iostream>
#include "TaskScheduler.h"
#include "ShoutCast.h"
#include "MicrophoneListener.h"
#include "Mp3Reader.h"
#include "Util.h"
#include "PriorityDrivenScheduler.h"
#include "EDFScheduler.h"
using namespace std;

const int BUFFER_SIZE = 4096;

std::shared_ptr<TaskScheduler> scheduler;
std::shared_ptr<ShoutCast> musicCastObject;
//std::shared_ptr<ShoutCast> voiceCastObject;
std::shared_ptr<Mp3Reader> mp3ReaderObject;
bool isEDFenabled = false;



// Action For Periodic Task
void periodicTaskAction() {
    std::cout << "--------> Periodic Task Running <------------\n";
    //Read Mp3 Streaming
    std::pair<char*, std::streamsize> pair = mp3ReaderObject->readData(BUFFER_SIZE);

    //Send Information to Server
    musicCastObject->Send(reinterpret_cast<unsigned char*> (pair.first), pair.second);
}


//Action for Sporadic Task
void sporadicTaskAction() {
    std::cout << "======= Sporadic Task Running ===========\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(ConfigReader::getInstance().sporadicExectionTime()));

}

//Action for Aperiodic Task
void aperiodicTaskAction() {

    //[TODO] Receive the Data from Callback function and Send it to Server
    std::cout << "###### Aperiodic Task Running ##########\n";
    //voiceCastObject->Send(buff, size);
}



int main() {

    bool isPreemptionAllowed = true;
    ConfigReader& config = ConfigReader::getInstance();

    if (!config.loadConfig("config.xml")) {
        std::cerr << "Failed to load config" << std::endl;
        return -1;
    }

    if (ConfigReader::getInstance().isEdfEnabled())
    {
        scheduler = std::make_shared <EDFScheduler>(isPreemptionAllowed);
    }
    else
    {
        scheduler = std::make_shared <PriorityDrivenScheduler>(isPreemptionAllowed);
    }
    

    musicCastObject = std::make_shared <ShoutCast>();
    musicCastObject->SetServerInformation(ConfigReader::getInstance().getServerAddress(), ConfigReader::getInstance().getServerPort(),
        ConfigReader::getInstance().getMountPoint(), ConfigReader::getInstance().getMountPassword(), true);
    musicCastObject->Configure();
    musicCastObject->Open();

    /*
    voiceCastObject = std::make_shared <ShoutCast>();
    voiceCastObject->SetServerInformation("192.168.0.53", 8000, "voice", "hackme", true);
    voiceCastObject->Configure();
    voiceCastObject->Open();
    */


    mp3ReaderObject = std::make_shared <Mp3Reader>();
    mp3ReaderObject->setFilePath(getExecutableDir() + "/" + ConfigReader::getInstance().getLocalMusicFileName());
    mp3ReaderObject->openFile();

    
    


    std::atomic<bool> running{ true };

    // Launch a thread to execute simulatePeriodicTask every 5 seconds
    std::thread periodicThread([&running]() {
        while (running) {


            scheduler->addTask(ConstructTask(periodic, periodicTaskAction));
            std::this_thread::sleep_for(std::chrono::milliseconds(ConfigReader::getInstance().periodicTaskPeriod()));
        }
        });




    MicrophoneListener microphoneDataListener;
    microphoneDataListener.startCapturing([](char* data, size_t size)
        {
        //this a Event Drivent function. It will Execute when certain amount of Data is found in microphone
        //std::cout << "-----> Micrpone Audio Detected <--------" << std::endl;

            scheduler->addTask(ConstructTask(aperiodic, aperiodicTaskAction));
        });

    

    //blocking the execution here
    while (getchar()) {
        //Schedule Sporadic task here
        scheduler->addTask(ConstructTask(sporadic, sporadicTaskAction));
    }




    running = false;
    if (periodicThread.joinable()) {
        periodicThread.join();
    }

    

    return 0;
}