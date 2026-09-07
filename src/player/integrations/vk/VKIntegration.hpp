#ifndef VK_VKINTEGRATION_HPP_
#define VK_VKINTEGRATION_HPP_

#include "core/core.hpp"

#include <rest_request/rest_request.h>

#include "integrations/Integration.hpp"
#include "integrations/OAuth.hpp"

#include "gui/components/integrations/vk/VKLoginComponent.hpp"

class VKIntegration : public Integration, public OAuth
{
    SIMPLE_DECLARE_CLASS(VKIntegration)

public:
    VKIntegration();
    ~VKIntegration() = default;

    virtual juce::String getName() const override;
    virtual juce::String getDescription() const override;

    virtual juce::String getToken() override;
    virtual juce::String refreshToken() override;

    virtual std::unique_ptr<juce::Component> createLoginComponent() override;

private:
    juce::String m_login;
    juce::String m_password;

    juce::String m_default_version = "5.131";
    juce::String m_default_lang = "ru";
};

#endif // VK_VKINTEGRATION_HPP_
