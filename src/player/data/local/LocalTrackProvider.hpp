#ifndef LOCAL_LOCAL_TRACK_PROVIDER_HPP_
#define LOCAL_LOCAL_TRACK_PROVIDER_HPP_

#include "media/tracks/Track.hpp"

#include <filesystem>
#include <memory>
#include <vector>

class LocalTrackProvider
{
public:
    using track_ptr = std::shared_ptr<Track>;

public:
    std::vector<track_ptr> getTracks(const std::filesystem::path& directory) const;

    track_ptr createTrack(const std::filesystem::path& file_path) const;

private:
    bool isAudioFile(const std::filesystem::path& file_path) const;
};

#endif // LOCAL_LOCAL_TRACK_PROVIDER_HPP_
