#include "SoundCloudLoginComponent.hpp"

SoundCloudLoginComponent::SoundCloudLoginComponent()
{
    title.setText(
        "Connect SoundCloud",
        juce::dontSendNotification);

    title.setFont(juce::FontOptions(28.0f));
    title.setColour(
        juce::Label::textColourId,
        juce::Colour(0xff202838));

    description.setText(
        "Connect your SoundCloud account to access your music.",
        juce::dontSendNotification);

    description.setFont(juce::FontOptions(15.0f));
    description.setColour(
        juce::Label::textColourId,
        juce::Colour(0xff8a93a5));

    addAndMakeVisible(title);
    addAndMakeVisible(description);
    addAndMakeVisible(loginButton);
}

void SoundCloudLoginComponent::paint(juce::Graphics& g)
{
    g.setColour(juce::Colour(0xffffffff).withAlpha(0.65f));
    g.fillRoundedRectangle(
        getLocalBounds().toFloat(),
        24.0f);
}

void SoundCloudLoginComponent::resized()
{
    auto area = getLocalBounds().reduced(50);

    title.setBounds(
        area.removeFromTop(45));

    description.setBounds(
        area.removeFromTop(50));

    loginButton.setBounds(
        area.removeFromTop(45).withWidth(220));
}