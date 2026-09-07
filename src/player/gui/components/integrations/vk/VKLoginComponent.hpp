#ifndef VK_SOUND_CLOUD_LOGIN_COMPONENT_HPP_
#define VK_SOUND_CLOUD_LOGIN_COMPONENT_HPP_

#include "core/core.hpp"

class VKLoginComponent : public juce::Component
{
public:
    VKLoginComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;

public:
    callback<juce::String(const juce::String&, const juce::String&)> onLoginButtonClicked;

private:
    juce::Label title;
    juce::Label description;

    juce::TextEditor loginEditor;
    juce::TextEditor passwordEditor;

    juce::TextButton loginButton{"Connect with VK"};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VKLoginComponent)
};


#endif // VK_SOUND_CLOUD_LOGIN_COMPONENT_HPP_
