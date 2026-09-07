#ifndef TRACKS_TRACK_HPP_
#define TRACKS_TRACK_HPP_

#include "core/core.hpp"

#include <functional>
#include <filesystem>

#include <miniaudio.h>

class LocalTrack
{
public:
    using data_callback =
        std::function<void(ma_device*, void*, const void*, ma_uint32)>;

public:
    LocalTrack() = default;
    LocalTrack(const std::filesystem::path& file_path);
    ~LocalTrack();

    bool init(const std::filesystem::path& file_path);
    void release();

    void play();
    void pause();
    void stop();

    bool isValid() const;

    bool isPlaying() const;

    const std::string& getName() const { return name; }

    const std::filesystem::path& getFilePath() const;

private:
    static void dataCallback(
        ma_device* device,
        void* output,
        const void* input,
        ma_uint32 frame_count);

private:
    std::filesystem::path m_filePath;

    ma_decoder m_decoder{};
    ma_device m_device{};

    bool m_decoderInitialized = false;
    bool m_deviceInitialized = false;

    std::atomic_bool m_isPlaying = false;

    std::string name;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LocalTrack)
};

#endif // TRACKS_TRACK_HPP_
