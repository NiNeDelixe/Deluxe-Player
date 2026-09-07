#ifndef YOUTUBE_YOU_TUBE_INTEGRATION_HPP_
#define YOUTUBE_YOU_TUBE_INTEGRATION_HPP_

#include "core/core.hpp"

#include "integrations/Integration.hpp"

#include "gui/components/integrations/youtube/YouTubeComponent.hpp"

class YouTubeIntegration : public Integration
{
    SIMPLE_DECLARE_CLASS(YouTubeIntegration)
    
public:
    YouTubeIntegration();
    ~YouTubeIntegration() = default;

    virtual juce::String getName() const override;
    virtual juce::String getDescription() const override;

    virtual std::unique_ptr<juce::Component> createLoginComponent() override;

    juce::String getApiKey() const { return api_key; };

protected:
    juce::String api_key;
};

#endif // YOUTUBE_YOU_TUBE_INTEGRATION_HPP_
