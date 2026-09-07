#ifndef COMPONENTS_SEARCH_COMPONENT_HPP_
#define COMPONENTS_SEARCH_COMPONENT_HPP_

#include "core/core.hpp"

#include "gui/schemas/LiquidGlass.hpp"

#include "algorithms/search/Search.hpp"

class SearchComponent : public juce::Component, private juce::TextEditor::Listener, private juce::ListBoxModel
{
public:
    using track_callback = std::function<void(std::vector<std::shared_ptr<LocalTrack>>)>;

public:
    SearchComponent(std::shared_ptr<Search> search, track_callback addTrack);
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    void search();
    void textEditorReturnKeyPressed(juce::TextEditor&) override;

    int getNumRows() override;
    void paintListBoxItem(int, juce::Graphics&, int, int, bool) override;
    void listBoxItemDoubleClicked(int, const juce::MouseEvent&) override;

    std::weak_ptr<Search> searchProvider;
    track_callback addTrack;

    juce::TextEditor searchEditor;
    juce::TextButton searchButton{"Search"};
    juce::ListBox resultsList;

    std::vector<SearchResult> results;
};

#endif // COMPONENTS_SEARCH_COMPONENT_HPP_
