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

private:
    juce::OwnedArray<TrackComponent> tracks;

    int selectedTrack = -1;

    void selectTrack(int index);

    LocalTrackProvider provider = LocalTrackProvider();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TrackList)
};

#endif // COMPONENTS_TRACK_LIST_HPP_
