#include "core/GuiAppApplication.hpp"

//==============================================================================
// This macro generates the main() routine that launches the app.

// #ifdef JUCE_ANDROID
// START_JUCE_APPLICATION(GuiAppApplication)

// int main(int argc, char const *argv[])
// {
//     return 0; 
// }
// #else
// // juce::JUCEApplicationBase* juce_CreateApplication();
// // juce::JUCEApplicationBase* juce_CreateApplication() { return new GuiAppApplication(); }

// // int main(int argc, char const *argv[])
// // {
// //     juce::JUCEApplicationBase::createInstance = &juce_CreateApplication; 
// //     return juce::JUCEApplicationBase::main(); 
// // }
// #endif
START_JUCE_APPLICATION(GuiAppApplication)