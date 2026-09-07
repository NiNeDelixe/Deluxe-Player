#ifndef COMPONENTS_PLAYER_BAR_HPP_
#define COMPONENTS_PLAYER_BAR_HPP_

#include "core/core.hpp"

#include <filesystem>

#include "gui/schemas/LiquidGlass.hpp"

#include "media/tracks/LocalTrack.hpp"

class PlayerBar : public LiquidGlass
{
public:
    PlayerBar();
    ~PlayerBar() override;

    void paintContent(juce::Graphics&) override;
    void resized() override;

    void setExpanded(bool expanded);
    int getPreferredHeight() const;

    template<class PROVIDER>
    void setTracks(const std::filesystem::path& directory);
    
    const std::vector<std::shared_ptr<LocalTrack>>& getTracks() const { return tracks; }

    std::shared_ptr<LocalTrack> getCurrentTrack();

    void playTrack(size_t index);

public:
    std::function<void(bool)> onExpandedChanged;

    std::function<void(void)> onTrackChangedFromList;
    std::function<void(void)> onTracksAdded;

private:
    void updateTrackInfo();
    void updatePlayButton();

private:
    bool isExpanded = false;
    size_t currentTrack = 0;

    std::vector<std::shared_ptr<LocalTrack>> tracks;

    juce::TextButton expandButton{"^"};
    juce::TextButton previousButton{"|<"};
    juce::TextButton playButton{">"};
    juce::TextButton nextButton{">|"};

    juce::String trackName;
    juce::String artistName;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerBar)
};

#endif // COMPONENTS_PLAYER_BAR_HPP_

template<class PROVIDER> 
inline void PlayerBar::setTracks(const std::filesystem::path& directory) 
{
    for (auto& track : tracks)
        track->stop();

    tracks.clear();

    PROVIDER provider;
    tracks = provider.getTracks(directory);

    currentTrack = 0;

    if (!tracks.empty())
    {
        updateTrackInfo();

        if (onTracksAdded)
        {
            onTracksAdded();
        }
    }
}
