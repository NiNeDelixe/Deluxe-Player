#include "YouTubeIntegration.hpp"

YouTubeIntegration::YouTubeIntegration() 
{
    api_base_url = {"https://www.googleapis.com/youtube/v3"};
    api_key = {Integrations::cmake::youtube::api_key.data()};
}

juce::String YouTubeIntegration::getName() const { return "YouTube"; }

juce::String YouTubeIntegration::getDescription() const { return "Integration with youtube"; }

std::unique_ptr<juce::Component> YouTubeIntegration::createLoginComponent()
{ 
    return std::make_unique<YouTubeComponent>(); 
}
