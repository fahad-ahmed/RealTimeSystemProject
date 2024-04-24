#include "MicrophoneListener.h"
#include <iostream>
#include <cmath> // For std::sqrt

MicrophoneListener::MicrophoneListener() :
    rate(44100), // Default rate. This could be adjustable.
    captureHandle(nullptr),
    capturing(false) {
}

MicrophoneListener::~MicrophoneListener() {
    stopCapturing();
    if (captureHandle) {
        snd_pcm_close(captureHandle);
    }
}

bool MicrophoneListener::startCapturing(const AudioCallback& callback) {
    capturing = true;
    userCallback = callback;

    int err;
    // Open PCM device for recording (capture).
    if ((err = snd_pcm_open(&captureHandle, "default", SND_PCM_STREAM_CAPTURE, 0)) < 0) {
        std::cerr << "Cannot open input audio device (" << snd_strerror(err) << ")" << std::endl;
        capturing = false;
        return false;
    }

    // Configure PCM parameters.
    snd_pcm_hw_params_t* hw_params;
    snd_pcm_hw_params_alloca(&hw_params);
    snd_pcm_hw_params_any(captureHandle, hw_params);
    snd_pcm_hw_params_set_access(captureHandle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(captureHandle, hw_params, SND_PCM_FORMAT_S16_LE);
    snd_pcm_hw_params_set_rate_near(captureHandle, hw_params, &rate, nullptr);
    snd_pcm_hw_params_set_channels(captureHandle, hw_params, 1); // Mono audio.

    if ((err = snd_pcm_hw_params(captureHandle, hw_params)) < 0) {
        std::cerr << "Cannot set hardware parameters (" << snd_strerror(err) << ")" << std::endl;
        capturing = false;
        return false;
    }

    // Start the capture thread.
    captureThread = std::thread(&MicrophoneListener::captureThreadFunction, this);

    return true;
}

void MicrophoneListener::stopCapturing() {
    capturing = false;
    if (captureThread.joinable()) {
        captureThread.join();
    }
    if (captureHandle) {
        snd_pcm_close(captureHandle);
        captureHandle = nullptr;
    }
}



void MicrophoneListener::captureThreadFunction() {
    const size_t bufferSize = 4096; // Buffer size in frames. This may need adjustment.
    std::unique_ptr<char[], void(*)(char*)> buffer(new char[bufferSize * 2], [](char* p) { delete[] p; }); // 2 bytes per frame for SND_PCM_FORMAT_S16_LE
    
    //Tune this threashold to decide amount of sound to fire the event.
    const int16_t threshold = 500; // Example threshold for RMS amplitude. This value may need tuning.

    while (capturing) {
        ssize_t frames = snd_pcm_readi(captureHandle, buffer.get(), bufferSize);

        if (frames < 0) {
            frames = snd_pcm_recover(captureHandle, frames, 0);
        }
        if (frames < 0) {
            std::cerr << "ERROR: snd_pcm_readi failed (" << snd_strerror(frames) << ")" << std::endl;
            break;
        }

        if (frames > 0 && capturing) {
            // Calculate RMS amplitude of the captured audio
            int64_t sumOfSquares = 0;
            for (int i = 0; i < frames * 2; i += 2) {
                // Assuming the audio format is S16_LE, combine two bytes to form one 16-bit sample
                int16_t sample = buffer.get()[i] | (buffer.get()[i + 1] << 8);
                sumOfSquares += sample * sample;
            }
            double rms = std::sqrt(sumOfSquares / frames);

            // Fire callback if RMS exceeds threshold
            if (rms > threshold) {
                userCallback(buffer.get(), frames * 2); // 2 bytes per frame
            }
        }
    }
}

