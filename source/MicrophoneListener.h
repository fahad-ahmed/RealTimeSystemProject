#ifndef MICROPHONELISTENER_H
#define MICROPHONELISTENER_H

#include <alsa/asoundlib.h>
#include <functional>
#include <thread>
#include <atomic>

class MicrophoneListener {
public:
    using AudioCallback = std::function<void(char* data, size_t size)>;

    MicrophoneListener();
    ~MicrophoneListener();

    bool startCapturing(const AudioCallback& callback);
    void stopCapturing();
    unsigned int rate;

private:
    void captureThreadFunction();
    snd_pcm_t* captureHandle;
    std::thread captureThread;
    std::atomic<bool> capturing;
    AudioCallback userCallback;
};

#endif // MICROPHONELISTENER_H
