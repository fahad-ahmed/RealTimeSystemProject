#pragma once
#include <iostream>
#include <fstream>
#include <shout/shout.h>
#include <cstring>
using namespace std;

class ShoutCast
{

private: 
	shout_t* shout;
	string serverAdress, mountpoint, password;
	bool ismp3format;
	int port;
public:
	ShoutCast();
	void SetServerInformation(string ServerAdress, int serverPort, string mountPoint, string moutPassword, bool isMP3ShoutFormat);
	void Configure();
	int Open();
	int Send(const unsigned char* data, size_t len);
	void Close();
	void ShutDown();
};

