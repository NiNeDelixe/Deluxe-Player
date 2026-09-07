#include "SearchComponent.hpp"

SearchComponent::SearchComponent(
    std::shared_ptr<Search> search,
    track_callback addTrack)
    : searchProvider(search), addTrack(std::move(addTrack))
{
    addAndMakeVisible(searchEditor);
    addAndMakeVisible(searchButton);
    addAndMakeVisible(resultsList);

    searchEditor.addListener(this);
    searchButton.onClick = [=] { this->search(); };

    resultsList.setModel(this);
}

void SearchComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::white);

    g.setColour(juce::Colours::black);
    g.setFont(18.0f);
    g.drawText(
        "Search",
        10,
        10,
        getWidth() - 20,
        30,
        juce::Justification::centredLeft
    );
}

void SearchComponent::resized()
{
    auto area = getLocalBounds().reduced(10);

    auto searchArea = area.removeFromTop(40);

    searchEditor.setBounds(
        searchArea.removeFromLeft(searchArea.getWidth() - 100)
    );

    searchButton.setBounds(
        searchArea
    );

    area.removeFromTop(10);

    resultsList.setBounds(area);
}

void SearchComponent::search()
{
    auto query = searchEditor.getText().trim();
    if (query.isEmpty())
        return;

    searchProvider.lock()->search(query, [this](auto newResults)
    {
        results = std::move(newResults);
        resultsList.updateContent();
    });
}

void SearchComponent::textEditorReturnKeyPressed(juce::TextEditor&)
{
    search();
}

int SearchComponent::getNumRows()
{
    return static_cast<int>(results.size());
}

void SearchComponent::paintListBoxItem(
    int row, juce::Graphics& g, int, int height, bool)
{
    g.setColour(juce::Colours::black);
    g.drawText(
        results[row].artist + " - " + results[row].title,
        10, 0, getWidth() - 20, height,
        juce::Justification::centredLeft);
}

void SearchComponent::listBoxItemDoubleClicked(
    int row, const juce::MouseEvent&)
{
    // searchProvider.lock()->createTrack(results[row])
    // addTrack();
}