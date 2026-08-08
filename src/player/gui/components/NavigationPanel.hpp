#ifndef COMPONENTS_NAVIGATION_PANEL_HPP_
#define COMPONENTS_NAVIGATION_PANEL_HPP_

#include "gui/schemas/LiquidGlass.hpp"

class NavigationPanel : public LiquidGlass
{
public:
    NavigationPanel();

    void paintContent(juce::Graphics&) override;
    void resized() override;
    
    std::function<void()> onIntegrationsClicked;
    juce::TextButton integrationsButton{"Integrations"};
};

#endif // COMPONENTS_NAVIGATION_PANEL_HPP_
