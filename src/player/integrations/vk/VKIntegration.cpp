#include "VKIntegration.hpp"

VKIntegration::VKIntegration() 
{
    auth_base_url = {"https://oauth.vk.com"};
}

juce::String VKIntegration::getName() const { return "VKIntegration"; }

juce::String VKIntegration::getDescription() const 
{ 
    return "Integration for vk"; 
}

juce::String VKIntegration::getToken() 
{ 
    juce::String request_str;
    adamski::RestRequest request = adamski::RestRequest(auth_base_url);

    request = request.post("token");

    request.header("accept", "application/json; charset=utf-8");
    request.header("Content-Type", "application/x-www-form-urlencoded");
    request.header("User-Agent", Integrations::cmake::vk::mobile::vk_user_agent.data());

    request.field("grant_type", "password");
    request.field("client_id", Integrations::cmake::vk::mobile::vk_client_id.data());
    request.field("client_secret", Integrations::cmake::vk::mobile::vk_client_secret.data());
    request.field("username", m_login);
    request.field("password", m_password);
    request.field("scope", "audio,offline");
    request.field("2fa_supported", 1);
    request.field("force_sms", 1);
    request.field("v", m_default_version);

    auto response = request.execute();

    auto token = response.body["access_token"].toString();

    return token; 
}

juce::String VKIntegration::refreshToken() 
{ 
    return juce::String(); 
}

std::unique_ptr<juce::Component> VKIntegration::createLoginComponent() 
{ 
    std::unique_ptr<juce::Component> component = std::make_unique<VKLoginComponent>();
    juce::Component* tempBase = component.get();
    VKLoginComponent* tempDerived = static_cast<VKLoginComponent*>(tempBase);
    tempDerived->onLoginButtonClicked = [=](const juce::String& login, const juce::String& password) -> juce::String
    {
        m_login = login;
        m_password = password;
        return getToken();
    };
    return component;
}
