#ifndef CORE_GUI_APP_APPLICATION_HPP_
#define CORE_GUI_APP_APPLICATION_HPP_

#include "gui/windows/PlayerWindow.hpp"

#include "internal_use_only/config.hpp"

class GuiAppApplication;

#if defined(PlayerApp)
#undef PlayerApp
#endif
#define PlayerApp (static_cast<GuiAppApplication*>(GuiAppApplication::getInstance()))

class GuiAppApplication final : public juce::JUCEApplication
{
public:
    //==============================================================================
    GuiAppApplication() {}

    // We inject these as compile definitions from the CMakeLists.txt
    // If you've enabled the juce header with `juce_generate_juce_header(<thisTarget>)`
    // you could `#include <JuceHeader.h>` and use `ProjectInfo::projectName` etc. instead.
    const juce::String getApplicationName() override       { return Deluxe_Player::cmake::project_name.data(); }
    const juce::String getApplicationVersion() override    { return Deluxe_Player::cmake::project_version.data(); }
    bool moreThanOneInstanceAllowed() override             { return true; }

    //==============================================================================
    void initialise(const juce::String& commandLine) override
    {
        // This method is where you should put your application's initialisation code..
        juce::ignoreUnused(commandLine);

        mainWindow.reset(new PlayerWindow(getApplicationName()));
    }

    void shutdown() override
    {
        // Add your application's shutdown code here..

        mainWindow = nullptr; // (deletes our window)
    }

    //==============================================================================
    void systemRequestedQuit() override
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted(const juce::String& commandLine) override
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
        juce::ignoreUnused(commandLine);
    }

    //==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our MainComponent class.
    */
    

private:
    std::unique_ptr<PlayerWindow> mainWindow;
};


#endif // CORE_GUI_APP_APPLICATION_HPP_
