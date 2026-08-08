#ifndef SOUNDCLOUD_SOUND_CLOUD_INTEGRATION_HPP_
#define SOUNDCLOUD_SOUND_CLOUD_INTEGRATION_HPP_

#include "core/core.hpp"

#include "integrations/Integration.hpp"

#include "gui/components/integrations/soundcloud/SoundCloudLoginComponent.hpp"

class SoundCloudIntegration : public Integration
{
public:
    juce::String getName() const override;
    juce::String getDescription() const override;

    std::unique_ptr<juce::Component> createLoginComponent() override;
};

#endif // SOUNDCLOUD_SOUND_CLOUD_INTEGRATION_HPP_
