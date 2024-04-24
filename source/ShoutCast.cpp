#include "ShoutCast.h"

ShoutCast::ShoutCast()
{

    shout_init();
    shout = shout_new();

    if (shout == nullptr) {
        std::cerr << "Error allocating shout instance" << std::endl;
        //return 1;
    }


}

void ShoutCast::SetServerInformation(string ServerAdress, int serverPort, string mountPoint, string moutPassword, bool isMP3ShoutFormat)
{
    serverAdress = ServerAdress;
    port = serverPort;
    mountpoint = mountPoint;
    password = moutPassword;
    ismp3format = isMP3ShoutFormat;

}

void ShoutCast::Configure()
{   
    shout_set_host(shout, serverAdress.c_str());
    shout_set_port(shout, port);
    shout_set_protocol(shout, SHOUT_PROTOCOL_HTTP);
    shout_set_password(shout, password.c_str()); // Server password
    shout_set_mount(shout, mountpoint.c_str());

    if(ismp3format)
    shout_set_format(shout, SHOUT_FORMAT_MP3);

    shout_set_user(shout, "source"); // Default user for source is 'source'
    // shout_set_agent(shout, "MyStreamingApp"); // Optionally, set a custom user-agent
    
}

int ShoutCast::Open()
{
    if (shout_open(shout) != SHOUTERR_SUCCESS) {
        std::cerr << "Error connecting to server: " << shout_get_error(shout) << std::endl;
        shout_free(shout);
        return 2;
    }
    return SHOUTERR_SUCCESS;
}

int ShoutCast::Send(const unsigned char* data, size_t len)
{
    if (shout_send(shout, data ,len) != SHOUTERR_SUCCESS) {
        std::cerr << "Error sending data: " << shout_get_error(shout) << std::endl;
        return -1;
    }
    shout_sync(shout);
    return SHOUTERR_SUCCESS;
}

void ShoutCast::Close()
{
    shout_close(shout);
    shout_free(shout);
}

void ShoutCast::ShutDown()
{
    this->Close();
    shout_shutdown();
}
