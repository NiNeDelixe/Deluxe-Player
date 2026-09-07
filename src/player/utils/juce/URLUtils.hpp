#ifndef JUCE_URLUTILS_HPP_
#define JUCE_URLUTILS_HPP_

#include "juce_core/juce_core.h"

juce::URL operator+(const juce::URL& left, const juce::URL& right);

juce::URL operator/(const juce::URL& left, const juce::URL& right);

juce::URL operator/(const juce::URL& left, const juce::String& right);

juce::URL operator/(const juce::URL& left, const char* const right);

#endif // JUCE_URLUTILS_HPP_
