#include "VKLoginComponent.hpp"

VKLoginComponent::VKLoginComponent()
{
    title.setText("Connect VK", juce::dontSendNotification);
    title.setFont(juce::FontOptions(28.0f));
    title.setColour(
        juce::Label::textColourId,
        juce::Colour(0xff202838));

    description.setText(
        "Connect your Vk account to access your music.",
        juce::dontSendNotification);
    description.setFont(juce::FontOptions(15.0f));
    description.setColour(
        juce::Label::textColourId,
        juce::Colour(0xff8a93a5));

    loginEditor.setTextToShowWhenEmpty(
        "Login",
        juce::Colour(0xff8a93a5));

    passwordEditor.setTextToShowWhenEmpty(
        "Password",
        juce::Colour(0xff8a93a5));
    passwordEditor.setPasswordCharacter('*');

    loginButton.onClick = [this]()
    {
        if (onLoginButtonClicked)
            onLoginButtonClicked(
                loginEditor.getText(),
                passwordEditor.getText());
    };

    addAndMakeVisible(title);
    addAndMakeVisible(description);
    addAndMakeVisible(loginEditor);
    addAndMakeVisible(passwordEditor);
    addAndMakeVisible(loginButton);
}

void VKLoginComponent::paint(juce::Graphics& g)
{
    g.setColour(juce::Colour(0xffffffff).withAlpha(0.65f));
    g.fillRoundedRectangle(
        getLocalBounds().toFloat(),
        24.0f);
}

void VKLoginComponent::resized()
{
    auto area = getLocalBounds().reduced(50);

    title.setBounds(area.removeFromTop(45));
    description.setBounds(area.removeFromTop(50));

    loginEditor.setBounds(
        area.removeFromTop(45).withWidth(320));

    area.removeFromTop(12);

    passwordEditor.setBounds(
        area.removeFromTop(45).withWidth(320));

    area.removeFromTop(20);

    loginButton.setBounds(
        area.removeFromTop(45).withWidth(220));
}