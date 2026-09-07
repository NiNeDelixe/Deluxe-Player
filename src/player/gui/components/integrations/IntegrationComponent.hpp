#ifndef INTEGRATIONS_INTEGRATION_COMPONENT_HPP_
#define INTEGRATIONS_INTEGRATION_COMPONENT_HPP_

#include "core/core.hpp"

#include "integrations/Integration.hpp"

#include "integrations/soundcloud/SoundCloudIntegration.hpp"
#include "integrations/vk/VKIntegration.hpp"
#include "integrations/youtube/YouTubeIntegration.hpp"

class IntegrationComponent : public juce::Component
{
public:
    IntegrationComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    std::vector<Integration*> integrations;

    std::unique_ptr<juce::Component> loginComponent;

    juce::Label title;
    juce::OwnedArray<juce::TextButton> buttons;

    void openIntegration(Integration& integration);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(
        IntegrationComponent)
};

#endif // INTEGRATIONS_INTEGRATION_COMPONENT_HPP_
