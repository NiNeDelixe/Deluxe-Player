#ifndef SEARCH_YOU_TUBE_SEARCH_HPP_
#define SEARCH_YOU_TUBE_SEARCH_HPP_

#include "algorithms/search/Search.hpp"

#include "integrations/youtube/YouTubeIntegration.hpp"

class YouTubeSearch : public Search
{
public:
    void search(const juce::String& query, Callback callback) override;
    std::shared_ptr<LocalTrack> createTrack(const SearchResult& result) override;

private:
};

#endif // SEARCH_YOU_TUBE_SEARCH_HPP_
