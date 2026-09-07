#ifndef DATA_TRACK_PROVIDER_HPP_
#define DATA_TRACK_PROVIDER_HPP_

#include "core/core.hpp"

#include <filesystem>
#include <memory>
#include <vector>

#include "media/tracks/LocalTrack.hpp"

class TrackProvider
{
public:
    using track_ptr = std::shared_ptr<LocalTrack>;

public:
    TrackProvider() = default;
    virtual ~TrackProvider() = default;

    virtual std::vector<track_ptr> getTracks(const std::filesystem::path& directory) const = 0;

    virtual track_ptr createTrack(const std::filesystem::path& file_path) const = 0;

private:
    
};

#endif // DATA_TRACK_PROVIDER_HPP_
