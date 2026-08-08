#include "SoundCloudIntegration.hpp"

juce::String SoundCloudIntegration::getName() const
{
    return "SoundCloud";
}

juce::String SoundCloudIntegration::getDescription() const
{
    return "Listen to your SoundCloud music";
}

std::unique_ptr<juce::Component> SoundCloudIntegration::createLoginComponent()
{
    return std::make_unique<SoundCloudLoginComponent>();
}