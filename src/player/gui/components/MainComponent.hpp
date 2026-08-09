#ifndef WINDOWS_MainComponent_HPP_
#define WINDOWS_MainComponent_HPP_

#include <juce_gui_extra/juce_gui_extra.h>

#include "gui/components/TrackList.hpp"
#include "gui/components/NavigationPanel.hpp"
#include "gui/components/PlayerBar.hpp"

#include "gui/components/integrations/IntegrationComponent.hpp"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent final : public juce::Component
{
public:
    //==============================================================================
    MainComponent();

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

    const PlayerBar& getPlayerBar() const { return playerBar; }

private:
    //==============================================================================
    // Your private member variables go here...
    TrackList trackList;
    NavigationPanel navigationPanel;
    PlayerBar playerBar;
    IntegrationComponent integrationComponent;

    juce::TextButton menuButton{"="};

    bool menuOpened = false;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
#endif // WINDOWS_MainComponent_HPP_
