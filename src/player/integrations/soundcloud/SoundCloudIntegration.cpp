#include "SoundCloudIntegration.hpp"

SoundCloudIntegration::SoundCloudIntegration() 
{
    api_base_url = {"https://api.soundcloud.com"};
    auth_base_url = {"https://secure.soundcloud.com"};
}

juce::String SoundCloudIntegration::getName() const { return "SoundCloud"; }

juce::String SoundCloudIntegration::getDescription() const
{
    return "Listen to your SoundCloud music";
}

juce::String SoundCloudIntegration::getToken() 
{ 
    juce::String request_str;
    adamski::RestRequest request = adamski::RestRequest(auth_base_url / "oauth" / "token");
    request.header("accept", "application/json; charset=utf-8");
    request.header("Content-Type", "application/x-www-form-urlencoded");

    request.field("grant_type", "authorization_code");
    request.field("client_id", Integrations::cmake::soundcloud::soundcloud_client_id.data());
    request.field("client_secret", Integrations::cmake::soundcloud::soundcloud_client_secret.data());
    request.field("redirect_uri", Integrations::cmake::soundcloud::soundcloud_redirect_uri.data());
    request.field("code_verifier", "");
    request.field("code", "");
    
    return juce::String(); 
}

juce::String SoundCloudIntegration::refreshToken() { return juce::String(); }

std::unique_ptr<juce::Component> SoundCloudIntegration::createLoginComponent()
{
    std::unique_ptr<juce::Component> component = std::make_unique<SoundCloudLoginComponent>();
    juce::Component* tempBase = component.get();
    SoundCloudLoginComponent* tempDerived = static_cast<SoundCloudLoginComponent*>(tempBase);
    tempDerived->onLoginButtonClickedTockenCallback = [=]() -> juce::String
    {
        return "";
    };
    return component;
}