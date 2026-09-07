#ifndef INTEGRATIONS_OAUTH_HPP_
#define INTEGRATIONS_OAUTH_HPP_

#include "core/core.hpp"

class OAuth
{
public:
    OAuth() = default;
    virtual ~OAuth() = default;

    virtual juce::String getToken() = 0;
    virtual juce::String refreshToken() = 0;

protected:
    juce::URL auth_base_url;
};

#endif // INTEGRATIONS_OAUTH_HPP_
