#ifndef SOUNDCLOUD_SOUND_CLOUD_LOGIN_COMPONENT_HPP_
#define SOUNDCLOUD_SOUND_CLOUD_LOGIN_COMPONENT_HPP_

#include "core/core.hpp"

class SoundCloudLoginComponent : public juce::Component
{
public:
    SoundCloudLoginComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    juce::Label title;
    juce::Label description;
    juce::TextButton loginButton{"Connect with SoundCloud"};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SoundCloudLoginComponent)
};

#endif // SOUNDCLOUD_SOUND_CLOUD_LOGIN_COMPONENT_HPP_
