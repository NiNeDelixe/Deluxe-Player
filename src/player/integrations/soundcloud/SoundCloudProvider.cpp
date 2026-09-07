#include "SoundCloudProvider.hpp"

std::vector<SoundCloudProvider::track_ptr> SoundCloudProvider::getTracks(const std::filesystem::path &directory) const
{ 
    return std::vector<track_ptr>();
}

SoundCloudProvider::track_ptr SoundCloudProvider::createTrack(const std::filesystem::path &file_path) const 
{ 
    return track_ptr(); 
}
