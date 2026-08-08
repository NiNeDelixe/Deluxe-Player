#include "LocalTrackProvider.hpp"

#include <algorithm>

std::vector<LocalTrackProvider::track_ptr> LocalTrackProvider::getTracks(const std::filesystem::path& directory) const
{
    std::vector<track_ptr> tracks;

    if (!std::filesystem::exists(directory))
        return tracks;

    for (const auto& entry : std::filesystem::recursive_directory_iterator(directory))
    {
        if (!entry.is_regular_file())
            continue;

        if (!isAudioFile(entry.path()))
            continue;

        auto track = createTrack(entry.path());

        if (track && track->isValid())
            tracks.push_back(track);
    }

    return tracks;
}

LocalTrackProvider::track_ptr LocalTrackProvider::createTrack(const std::filesystem::path& file_path) const
{
    auto track = std::make_shared<Track>(file_path);

    if (!track->isValid())
        return nullptr;

    return track;
}

bool LocalTrackProvider::isAudioFile(const std::filesystem::path& file_path) const
{
    auto extension = file_path.extension().string();

    std::transform(
        extension.begin(),
        extension.end(),
        extension.begin(),
        [](unsigned char c)
        {
            return static_cast<char>(std::tolower(c));
        }
    );

    return extension == ".mp3"
        || extension == ".wav"
        || extension == ".flac"
        || extension == ".ogg"
        || extension == ".m4a"
        || extension == ".aac";
}