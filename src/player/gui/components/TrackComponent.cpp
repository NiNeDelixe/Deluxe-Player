#include "TrackComponent.hpp"

TrackComponent::TrackComponent(
    int number,
    const juce::String& title,
    const juce::String& artist,
    const juce::String& album,
    const juce::String& duration)
    : number(number),
      title(title),
      artist(artist),
      album(album),
      duration(duration)
{
}

void TrackComponent::paint(juce::Graphics& g)
{
    if (selected)
    {
        g.setColour(juce::Colour(0xffe4efff));
        g.fillRoundedRectangle(getLocalBounds().toFloat(), 12.0f);
    }
    else if (hovered)
    {
        g.setColour(juce::Colour(0xfff4f4f4).withAlpha(0.65f));
        g.fillRoundedRectangle(getLocalBounds().toFloat(), 12.0f);
    }

    g.setColour(juce::Colour(0xff252d3b));
    g.setFont(14.0f);

    g.drawText(
        juce::String(number).paddedLeft('0', 2),
        15, 0, 40, getHeight(),
        juce::Justification::centred);

    g.drawText(
        title,
        75, 0, 250, getHeight(),
        juce::Justification::centredLeft);

    g.setColour(juce::Colour(0xff8a93a5));

    g.drawText(
        artist,
        350, 0, 220, getHeight(),
        juce::Justification::centredLeft);

    g.drawText(
        album,
        590, 0, 220, getHeight(),
        juce::Justification::centredLeft);

    g.drawText(
        duration,
        getWidth() - 80, 0, 60, getHeight(),
        juce::Justification::centredRight);
}

void TrackComponent::resized()
{
}

void TrackComponent::mouseEnter(const juce::MouseEvent&)
{
    hovered = true;
    repaint();
}

void TrackComponent::mouseExit(const juce::MouseEvent&)
{
    hovered = false;
    repaint();
}

void TrackComponent::mouseDown(const juce::MouseEvent&)
{
    if (onClicked)
        onClicked();
}

void TrackComponent::setSelected(bool value)
{
    selected = value;
    repaint();
}