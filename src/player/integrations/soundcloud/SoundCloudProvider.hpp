#ifndef SOUNDCLOUD_SOUND_CLOUD_PROVIDER_HPP_
#define SOUNDCLOUD_SOUND_CLOUD_PROVIDER_HPP_

#include "core/core.hpp"

#include "data/TrackProvider.hpp"

class SoundCloudProvider : public TrackProvider
{
public:
    SoundCloudProvider() = default;
    ~SoundCloudProvider() = default;

    virtual std::vector<track_ptr> getTracks(const std::filesystem::path& directory) const;

    virtual track_ptr createTrack(const std::filesystem::path& file_path) const;

private:
    
};

#endif // SOUNDCLOUD_SOUND_CLOUD_PROVIDER_HPP_
