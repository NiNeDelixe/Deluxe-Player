#include "URLUtils.hpp"

juce::URL operator+(const juce::URL &left, const juce::URL &right)
{
    return juce::URL(left.toString(true) + right.toString(true));
}

juce::URL operator/(const juce::URL &left, const juce::URL &right) 
{ 
    return left + juce::URL("/") + right; 
}

juce::URL operator/(const juce::URL &left, const juce::String &right) 
{ 
    return left + juce::URL("/") + right; 
}

juce::URL operator/(const juce::URL &left, const char *const right) 
{ 
    return left / juce::String(right); 
}
