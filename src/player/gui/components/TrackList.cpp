#include "TrackList.hpp"

#include "core/GuiAppApplication.hpp"

TrackList::TrackList()
{  

    // const std::array data
    // {
    //     std::tuple{"Dreams", "Fleetwood Mac", "Rumours", "4:17"},
    //     std::tuple{"The Night We Met", "Lord Huron", "Strange Trails", "3:28"},
    //     std::tuple{"Sunset Lover", "Petit Biscuit", "Presence", "3:57"},
    //     std::tuple{"Experience", "Ludovico Einaudi", "In a Time Lapse", "5:15"},
    //     std::tuple{"Space Song", "Beach House", "Depression Cherry", "5:20"},
    //     std::tuple{"Holocene", "Bon Iver", "Bon Iver", "5:36"},
    //     std::tuple{"Intro", "The xx", "xx", "2:07"},
    //     std::tuple{"Youth", "Daughter", "If You Leave", "4:12"}
    // };

    // for (size_t i = 0; i < data.size(); ++i)
    // {
    //     auto* track = tracks.add(new TrackComponent(
    //         static_cast<int>(i + 1),
    //         std::get<0>(data[i]),
    //         std::get<1>(data[i]),
    //         std::get<2>(data[i]),
    //         std::get<3>(data[i])));

    //     const int index = static_cast<int>(i);

    //     track->onClicked = [this, index]
    //     {
    //         selectTrack(index);
    //     };

    //     addAndMakeVisible(track);
    // }
}

void TrackList::paint(juce::Graphics& g)
{
    g.setColour(juce::Colour(0xffffffff).withAlpha(0.55f));
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 20.0f);

    g.setColour(juce::Colour(0xff202838));
    g.setFont(28.0f);
    g.drawText("Tracks", 32, 20, 300, 40,
               juce::Justification::left);
}

void TrackList::resized()
{
    const int top = 75;
    const int height = 58;

    for (int i = 0; i < track_components.size(); ++i)
        track_components[i]->setBounds(20, top + i * height,
                             getWidth() - 40, height - 4);
}

void TrackList::changeTrack(std::shared_ptr<LocalTrack> track) 
{
    auto iter = std::find(tracks.begin(), tracks.end(), track);
    selectTrack(std::distance(tracks.begin(), iter));
}

void TrackList::setTracks(std::vector<std::shared_ptr<LocalTrack>> tracks) 
{
    this->tracks = tracks;

    recreateList();
}

void TrackList::recreateList() 
{
    size_t i = 0;
    for (const auto& track : tracks)
    {
        auto* track_component = track_components.add(new TrackComponent(
            static_cast<int>(i + 1),
            track->getName(),
            track->getName(),
            track->getName(),
            track->getName()));

        const int index = static_cast<int>(i);

        track_component->onClicked = [this, index, track]
        {
            selectTrack(index);
            onTrackClicked(index);
            //track->play();
        };

        addAndMakeVisible(track_component);

        ++i;
    }

    repaint();
    resized();
}

void TrackList::selectTrack(int index)
{
    selectedTrack = index;

    for (int i = 0; i < track_components.size(); ++i)
        track_components[i]->setSelected(i == selectedTrack);
}
