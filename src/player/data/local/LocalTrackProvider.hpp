#ifndef LOCAL_LOCAL_TRACK_PROVIDER_HPP_
#define LOCAL_LOCAL_TRACK_PROVIDER_HPP_

#include "core/core.hpp"

#include "data/TrackProvider.hpp"

class LocalTrackProvider : public TrackProvider
{
public:
    std::vector<track_ptr> getTracks(const std::filesystem::path& directory) const override;

    track_ptr createTrack(const std::filesystem::path& file_path) const override;

private:
    bool isAudioFile(const std::filesystem::path& file_path) const;
};

#endif // LOCAL_LOCAL_TRACK_PROVIDER_HPP_
