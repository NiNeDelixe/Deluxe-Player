#ifndef SEARCH_SEARCH_HPP_
#define SEARCH_SEARCH_HPP_

#include "core/core.hpp"

#include "rest_request/rest_request.h"

#include "media/tracks/LocalTrack.hpp"

struct SearchResult
{
    juce::String id;
    juce::String title;
    juce::String artist;
    juce::String url;
    juce::String source;
};

class Search
{
public:
    using Callback = std::function<void(std::vector<SearchResult>)>;

    virtual ~Search() = default;

    virtual void search(const juce::String& query, Callback callback) = 0;
    virtual std::shared_ptr<LocalTrack> createTrack(const SearchResult& result) = 0;
};

#endif // SEARCH_SEARCH_HPP_
