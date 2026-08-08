#include "MainComponent.hpp"

MainComponent::MainComponent()
{
    setSize(1200, 750);

    addAndMakeVisible(trackList);
    addAndMakeVisible(playerBar);
    addAndMakeVisible(menuButton);

    menuButton.onClick = [this]
    {
        menuOpened = !menuOpened;

        if (menuOpened)
            addAndMakeVisible(navigationPanel);
        else
            navigationPanel.setVisible(false);

        resized();
    };

    playerBar.onExpandedChanged = [this](bool)
    {
        resized();
    };

    addChildComponent(integrationComponent);

    navigationPanel.onIntegrationsClicked = [this]
    {
        integrationComponent.setVisible(true);
        integrationComponent.toFront(false);
        resized();
    };

    playerBar.template setTracks<LocalTrackProvider>("C:\\Users\\nanler\\Music");
}

//==============================================================================
void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(0xfff5f7fb));

    g.setColour(juce::Colour(0xffffffff).withAlpha(0.65f));

    g.fillRoundedRectangle(
        getLocalBounds().toFloat().reduced(16),
        24.0f);

    g.setColour(juce::Colour(0xffdfe5ef));

    g.drawRoundedRectangle(
        getLocalBounds().toFloat().reduced(16),
        24.0f,
        1.0f);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    const int margin = 32;
    const int playerHeight = playerBar.getPreferredHeight();

    menuButton.setBounds(
        getWidth() - 82,
        32,
        50,
        50);

    playerBar.setBounds(
        margin,
        getHeight() - playerHeight - 24,
        getWidth() - margin * 2,
        playerHeight);

    trackList.setBounds(
        margin,
        110,
        getWidth() - margin * 2,
        getHeight() - playerHeight - 150);

    if (menuOpened)
    {
        navigationPanel.setBounds(
            getWidth() - 320,
            100,
            280,
            getHeight() - 120);
    }

    integrationComponent.setBounds(
    40,
    40,
    getWidth() - 80,
    getHeight() - 80);
}

//#include "moc_PlayerWindow.cpp"