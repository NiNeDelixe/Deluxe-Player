#include "core/GuiAppApplication.hpp"


//==============================================================================
// This macro generates the main() routine that launches the app.

juce::JUCEApplicationBase* juce_CreateApplication();
juce::JUCEApplicationBase* juce_CreateApplication() { return new GuiAppApplication(); }

int main(int argc, char const *argv[])
{
    juce::JUCEApplicationBase::createInstance = &juce_CreateApplication; 
    return juce::JUCEApplicationBase::main(); 
}
