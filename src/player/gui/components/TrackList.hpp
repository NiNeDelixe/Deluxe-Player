#ifndef COMPONENTS_TRACK_LIST_HPP_
#define COMPONENTS_TRACK_LIST_HPP_

#include "core/core.hpp"

#include <juce_gui_extra/juce_gui_extra.h>

#include "gui/components/TrackComponent.hpp"

#include "data/local/LocalTrackProvider.hpp"

class TrackList : public juce::Component
{
public:
    TrackList();

    void paint(juce::Graphics&) override;
    void resized() override;

    void changeTrack(std::shared_ptr<LocalTrack> track);
    void setTracks(std::vector<std::shared_ptr<LocalTrack>> tracks);

    void recreateList();

public:
    std::function<void(size_t)> onTrackClicked;

private:
    juce::OwnedArray<TrackComponent> track_components;
    std::vector<std::shared_ptr<LocalTrack>> tracks;

    int selectedTrack = -1;

    void selectTrack(int index);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TrackList)
};

#endif // COMPONENTS_TRACK_LIST_HPP_
