#ifndef COMPONENTS_TRACK_COMPONENT_HPP_
#define COMPONENTS_TRACK_COMPONENT_HPP_

#include "core/core.hpp"

#include <juce_gui_extra/juce_gui_extra.h>

#include "media/tracks/Track.hpp"

class TrackComponent : public juce::Component
{
public:
    TrackComponent(
        int number,
        const juce::String& title,
        const juce::String& artist,
        const juce::String& album,
        const juce::String& duration);

    void paint(juce::Graphics& g) override;
    void resized() override;

    void mouseEnter(const juce::MouseEvent&) override;
    void mouseExit(const juce::MouseEvent&) override;
    void mouseDown(const juce::MouseEvent&) override;

    void setSelected(bool selected);

    std::function<void()> onClicked;

private:
    int number;
    juce::String title;
    juce::String artist;
    juce::String album;
    juce::String duration;

    bool selected = false;
    bool hovered = false;

    std::weak_ptr<Track> track;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TrackComponent)
};

#endif // COMPONENTS_TRACK_COMPONENT_HPP_
