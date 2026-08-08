#ifndef WINDOWS_PLAYER_WINDOW_HPP_
#define WINDOWS_PLAYER_WINDOW_HPP_

#include <juce_core/juce_core.h>

#include "gui/components/MainComponent.hpp"

class PlayerWindow final : public juce::DocumentWindow
{
public:
    explicit PlayerWindow(juce::String name)
        : DocumentWindow(
            name, 
            juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(backgroundColourId), 
            allButtons)
    {
        setUsingNativeTitleBar(true);
        setContentOwned(new MainComponent(), true);

        #if JUCE_IOS || JUCE_ANDROID
        setFullScreen (true);
        #else
        setResizable(true, true);
        centreWithSize(getWidth(), getHeight());
        #endif

        setVisible(true);
    }

    void closeButtonPressed() override;

    /* Note: Be careful if you override any DocumentWindow methods - the base
        class uses a lot of them, so by overriding you might break its functionality.
        It's best to do all your work in your content component instead, but if
        you really have to override any DocumentWindow methods, make sure your
        subclass also calls the superclass's method.
    */

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerWindow)
};

#endif // WINDOWS_PLAYER_WINDOW_HPP_
