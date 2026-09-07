#pragma once

#include "core/core.hpp"

class YouTubeComponent : public juce::Component
{
public:
    YouTubeComponent();

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

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(YouTubeComponent)
};

