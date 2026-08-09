#include "PlayerBar.hpp"

PlayerBar::PlayerBar()
{
    addAndMakeVisible(expandButton);
    addAndMakeVisible(previousButton);
    addAndMakeVisible(playButton);
    addAndMakeVisible(nextButton);

    expandButton.onClick = [this]
    {
        isExpanded = !isExpanded;
        setExpanded(isExpanded);
        resized();

        if (onExpandedChanged)
            onExpandedChanged(isExpanded);
    };

    playButton.onClick = [this]
    {
        if (tracks.empty())
            return;

        auto& track = tracks[currentTrack];

        if (track->isPlaying())
            track->pause();
        else
            track->play();

        updatePlayButton();
    };

    previousButton.onClick = [this]
    {
        if (tracks.empty())
            return;

        if (currentTrack == 0)
            currentTrack = tracks.size() - 1;
        else
            --currentTrack;

        playTrack(currentTrack);

        if (onTrackChangedFromList)
        {
            onTrackChangedFromList();
        }
        
    };

    nextButton.onClick = [this]
    {
        if (tracks.empty())
            return;

        currentTrack = (currentTrack + 1) % tracks.size();
        playTrack(currentTrack);
        
        if (onTrackChangedFromList)
        {
            onTrackChangedFromList();
        }
    };
}

PlayerBar::~PlayerBar()
{
    for (auto& track : tracks)
        track->stop();
}

void PlayerBar::playTrack(size_t index)
{
    if (index >= tracks.size())
        return;

    for (size_t i = 0; i < tracks.size(); ++i)
    {
        if (i != index)
            tracks[i]->stop();
    }

    currentTrack = index;
    tracks[currentTrack]->play();

    updateTrackInfo();
    updatePlayButton();
    repaint();
}

void PlayerBar::updateTrackInfo()
{
    if (tracks.empty())
    {
        trackName = {};
        artistName = {};
        repaint();
        return;
    }

    const auto& path = tracks[currentTrack]->getFilePath();

    trackName = juce::String(path.stem().string());
    artistName = juce::String(path.parent_path().filename().string());

    repaint();
}

void PlayerBar::updatePlayButton()
{
    if (tracks.empty())
    {
        playButton.setButtonText(">");
        return;
    }

    playButton.setButtonText(
        tracks[currentTrack]->isPlaying() ? "||" : ">");
}

std::shared_ptr<Track> PlayerBar::getCurrentTrack() 
{ 
    return tracks[currentTrack];
}

void PlayerBar::setExpanded(bool expanded)
{
    isExpanded = expanded;
    expandButton.setButtonText(isExpanded ? "⌄" : "^");
}

int PlayerBar::getPreferredHeight() const
{
    return isExpanded ? 280 : 105;
}

void PlayerBar::paintContent(juce::Graphics& g)
{
    g.setColour(juce::Colour(0xff202838));
    g.setFont(18.0f);

    g.drawText(
        trackName,
        120,
        22,
        180,
        25,
        juce::Justification::left);

    g.setColour(juce::Colour(0xff8a93a5));
    g.setFont(14.0f);

    g.drawText(
        artistName,
        120,
        48,
        180,
        22,
        juce::Justification::left);
}

void PlayerBar::resized()
{
    expandButton.setBounds(
        getWidth() / 2 - 20,
        5,
        40,
        25);

    previousButton.setBounds(
        getWidth() / 2 - 125,
        35,
        45,
        35);

    playButton.setBounds(
        getWidth() / 2 - 30,
        28,
        60,
        50);

    nextButton.setBounds(
        getWidth() / 2 + 80,
        35,
        45,
        35);
}