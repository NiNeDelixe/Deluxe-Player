#include "NavigationPanel.hpp"

NavigationPanel::NavigationPanel()
{
    setGlassRadius(20.0f);
    setGlassOpacity(0.72f);

    addAndMakeVisible(integrationsButton);
    integrationsButton.onClick = [this]
    {
        if (onIntegrationsClicked)
            onIntegrationsClicked();
    };
}

void NavigationPanel::paintContent(juce::Graphics& g)
{
    // g.setColour(juce::Colour(0xffffffff).withAlpha(0.72f));
    // g.fillRoundedRectangle(getLocalBounds().toFloat(), 22.0f);

    // g.setColour(juce::Colour(0xff202838));
    // g.setFont(17.0f);

    // const char* items[] =
    // {
    //     "Home",
    //     "Library",
    //     "Favorites",
    //     "Playlists",
    //     "Albums",
    //     "Artists",
    //     "Genres",
    //     "Recently Played",
    //     "Settings"
    // };

    // for (int i = 0; i < 9; ++i)
    // {
    //     g.drawText(
    //         items[i],
    //         35,
    //         35 + i * 52,
    //         getWidth() - 50,
    //         40,
    //         juce::Justification::centredLeft);
    // }

    // g.setColour(juce::Colour(0xff8a93a5));
    // g.setFont(12.0f);

    // g.drawText(
    //     "PLAYLISTS",
    //     35,
    //     515,
    //     150,
    //     20,
    //     juce::Justification::left);

    // g.setColour(juce::Colour(0xff202838));
    // g.setFont(15.0f);

    // g.drawText(
    //     "Liked Songs",
    //     35,
    //     545,
    //     180,
    //     25,
    //     juce::Justification::left);

    // g.drawText(
    //     "Chill Vibes",
    //     35,
    //     590,
    //     180,
    //     25,
    //     juce::Justification::left);

    // g.drawText(
    //     "Workout",
    //     35,
    //     635,
    //     180,
    //     25,
    //     juce::Justification::left);
}

void NavigationPanel::resized()
{
    integrationsButton.setBounds(
    35,
    35,
    getWidth() - 70,
    40);
}