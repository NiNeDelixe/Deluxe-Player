#ifndef INTEGRATIONS_INTEGRATION_HPP_
#define INTEGRATIONS_INTEGRATION_HPP_

#include "core/core.hpp"

class Integration
{
public:
    virtual ~Integration() = default;

    virtual juce::String getName() const = 0;
    virtual juce::String getDescription() const = 0;

    virtual std::unique_ptr<juce::Component> createLoginComponent() = 0;
};

#endif // INTEGRATIONS_INTEGRATION_HPP_
