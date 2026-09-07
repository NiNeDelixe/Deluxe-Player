#include "YouTubeSearch.hpp"

void YouTubeSearch::search(const juce::String& query, Callback callback)
{
    juce::URL url = {"https://www.googleapis.com/youtube/v3"};
    url = url.withParameter("part", "snippet");
    url = url.withParameter("q", query);
    url = url.withParameter("type", "video");
    url = url.withParameter("maxResults", juce::String(20));
    url = url.withParameter("key", YouTubeIntegration::getInstance().getApiKey());

    adamski::RestRequest request = adamski::RestRequest(url);
    request = request.get("search");

    auto response = request.execute();
    DBG(response.bodyAsString);

    auto videos_array = *response.body["items"].getArray();

    std::vector<SearchResult> results;

    for (size_t i = 0; i < videos_array.size(); i++)
    {
        auto video = videos_array[i];
        
        SearchResult res = {
            video["id"]["videoId"].toString(), 
            video["snippet"]["title"].toString(), 
            video["snippet"]["channelTitle"].toString(),
            "",
            ""
        };

        results.push_back(res);
    }
    
    

    callback(std::move(results));
}

std::shared_ptr<LocalTrack> YouTubeSearch::createTrack(
    const SearchResult& result)
{
    return std::make_shared<LocalTrack>(
        // result.title,
        // result.artist,
        result.url.toStdString()
    );
}