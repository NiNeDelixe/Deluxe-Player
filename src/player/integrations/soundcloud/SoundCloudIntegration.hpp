#ifndef SOUNDCLOUD_SOUND_CLOUD_INTEGRATION_HPP_
#define SOUNDCLOUD_SOUND_CLOUD_INTEGRATION_HPP_

#include "core/core.hpp"

#include "rest_request/rest_request.h"

#include "integrations/Integration.hpp"
#include "integrations/OAuth.hpp"

#include "gui/components/integrations/soundcloud/SoundCloudLoginComponent.hpp"

class SoundCloudIntegration : public Integration, public OAuth
{
    SIMPLE_DECLARE_CLASS(SoundCloudIntegration)

public:
    SoundCloudIntegration();
    ~SoundCloudIntegration() = default;

    juce::String getName() const override;
    juce::String getDescription() const override;

    juce::String getToken() override;
    juce::String refreshToken() override;

    std::unique_ptr<juce::Component> createLoginComponent() override;
};

#endif // SOUNDCLOUD_SOUND_CLOUD_INTEGRATION_HPP_
