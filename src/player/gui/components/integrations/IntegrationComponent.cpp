#include "IntegrationComponent.hpp"

IntegrationComponent::IntegrationComponent()
{
    integrations.push_back(
        std::make_unique<SoundCloudIntegration>());

    title.setText(
        "Integrations",
        juce::dontSendNotification);

    title.setFont(juce::FontOptions(28.0f));
    title.setColour(
        juce::Label::textColourId,
        juce::Colour(0xff202838));

    addAndMakeVisible(title);

    for (auto& integration : integrations)
    {
        auto* button = buttons.add(
            new juce::TextButton(integration->getName()));

        button->onClick = [this, integration = integration.get()]
        {
            openIntegration(*integration);
        };

        addAndMakeVisible(button);
    }
}

void IntegrationComponent::openIntegration(
    Integration& integration)
{
    loginComponent = integration.createLoginComponent();

    addAndMakeVisible(*loginComponent);

    resized();
}

void IntegrationComponent::paint(juce::Graphics& g)
{
    g.setColour(juce::Colour(0xffffffff).withAlpha(0.65f));

    g.fillRoundedRectangle(
        getLocalBounds().toFloat(),
        24.0f);

    // g.setColour(juce::Colour(0xff202838));
    // g.setFont(28.0f);

    // g.drawText(
    //     "Integrations",
    //     35,
    //     25,
    //     300,
    //     40,
    //     juce::Justification::left);
}

void IntegrationComponent::resized()
{
    title.setBounds(
        35,
        25,
        300,
        40);

    int y = 90;

    for (auto* button : buttons)
    {
        button->setBounds(
            35,
            y,
            250,
            50);

        y += 65;
    }

    if (loginComponent)
    {
        loginComponent->setBounds(
            330,
            30,
            getWidth() - 365,
            getHeight() - 60);
    }
}