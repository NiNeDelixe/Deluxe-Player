#include "LocalTrack.hpp"

LocalTrack::LocalTrack(const std::filesystem::path& file_path)
{
    init(file_path);
}

LocalTrack::~LocalTrack()
{
    release();
}

bool LocalTrack::init(const std::filesystem::path& file_path)
{
    release();

    m_filePath = file_path;

    if (ma_decoder_init_file(
            m_filePath.string().c_str(),
            nullptr,
            &m_decoder) != MA_SUCCESS)
    {
        return false;
    }

    m_decoderInitialized = true;

    auto config = ma_device_config_init(ma_device_type_playback);

    config.playback.format = m_decoder.outputFormat;
    config.playback.channels = m_decoder.outputChannels;
    config.sampleRate = m_decoder.outputSampleRate;

    config.dataCallback = dataCallback;
    config.pUserData = this;

    if (ma_device_init(nullptr, &config, &m_device) != MA_SUCCESS)
    {
        ma_decoder_uninit(&m_decoder);
        m_decoderInitialized = false;
        return false;
    }

    m_deviceInitialized = true;

    name = file_path.stem().string();

    return true;
}

void LocalTrack::release()
{
    m_isPlaying = false;

    if (m_deviceInitialized)
    {
        ma_device_uninit(&m_device);
        m_deviceInitialized = false;
    }

    if (m_decoderInitialized)
    {
        ma_decoder_uninit(&m_decoder);
        m_decoderInitialized = false;
    }

    m_filePath.clear();
}

void LocalTrack::play()
{
    if (!m_deviceInitialized || !m_decoderInitialized)
        return;

    m_isPlaying = true;

    ma_device_start(&m_device);
}

void LocalTrack::pause()
{
    if (!m_deviceInitialized)
        return;

    m_isPlaying = false;

    ma_device_stop(&m_device);
}

void LocalTrack::stop()
{
    if (!m_deviceInitialized || !m_decoderInitialized)
        return;

    m_isPlaying = false;

    ma_device_stop(&m_device);

    ma_decoder_seek_to_pcm_frame(&m_decoder, 0);
}

bool LocalTrack::isValid() const 
{ 
    return m_decoderInitialized && m_deviceInitialized; 
}

bool LocalTrack::isPlaying() const
{
    return m_isPlaying.load();
}

const std::filesystem::path& LocalTrack::getFilePath() const
{
    return m_filePath;
}

void LocalTrack::dataCallback(
    ma_device* device,
    void* output,
    const void* input,
    ma_uint32 frame_count)
{
    juce::ignoreUnused(input);

    auto* track =
        static_cast<LocalTrack*>(device->pUserData);

    if (!track || !track->m_isPlaying)
    {
        ma_silence_pcm_frames(
            output,
            frame_count,
            device->playback.format,
            device->playback.channels);

        return;
    }

    ma_uint64 frames_read = 0;

    ma_decoder_read_pcm_frames(
        &track->m_decoder,
        output,
        frame_count,
        &frames_read);

    if (frames_read < frame_count)
    {
        const auto bytesPerFrame =
            ma_get_bytes_per_frame(
                device->playback.format,
                device->playback.channels);

        auto* silenceStart =
            static_cast<ma_uint8*>(output) +
            frames_read * bytesPerFrame;

        ma_silence_pcm_frames(
            silenceStart,
            frame_count - frames_read,
            device->playback.format,
            device->playback.channels);

        track->m_isPlaying = false;
    }
}