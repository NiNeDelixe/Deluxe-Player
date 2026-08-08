#include "PlayerWindow.hpp"

#include "core/GuiAppApplication.hpp"

void PlayerWindow::closeButtonPressed()
{
    // This is called when the user tries to close this window. Here, we'll just
    // ask the app to quit when this happens, but you can change this to do
    // whatever you need.
    
    PlayerApp->systemRequestedQuit();
}
