#ifndef SCHEMAS_LIQUID_GLASS_HPP_
#define SCHEMAS_LIQUID_GLASS_HPP_

#include <juce_gui_extra/juce_gui_extra.h>

class LiquidGlass : public juce::Component
{
public:
    LiquidGlass();
    ~LiquidGlass() override = default;

    void paint(juce::Graphics& g) override;

    virtual void paintContent(juce::Graphics& g);

    void setGlassOpacity(float opacity);
    void setBlurAmount(float amount);
    void setGlassRadius(float radius);
    void setBorderOpacity(float opacity);
    void setHighlightOpacity(float opacity);
    void setShadowOpacity(float opacity);
    void setShadowRadius(float radius);
    void setShadowOffset(juce::Point<int> offset);

    void setGlassColour(juce::Colour colour);
    void setBorderColour(juce::Colour colour);
    void setHighlightColour(juce::Colour colour);

    float getGlassOpacity() const;
    float getBlurAmount() const;
    float getGlassRadius() const;

    void setBackdropComponent(juce::Component* component);

    void resized() override;

protected:
    void invalidateBackdrop();

private:
    void updateBackdrop();
    void drawBackdropBlur(juce::Graphics& g);
    void drawGlass(juce::Graphics& g);
    void drawBorder(juce::Graphics& g);
    void drawHighlight(juce::Graphics& g);
    void drawShadow(juce::Graphics& g);

    juce::Image backdropImage;
    juce::Component* backdropComponent = nullptr;

    float glassOpacity = 0.68f;
    float blurAmount = 18.0f;
    float glassRadius = 20.0f;

    float borderOpacity = 0.28f;
    float highlightOpacity = 0.22f;

    float shadowOpacity = 0.18f;
    float shadowRadius = 16.0f;

    juce::Point<int> shadowOffset { 0, 8 };

    juce::Colour glassColour { 255, 255, 255 };
    juce::Colour borderColour { 255, 255, 255 };
    juce::Colour highlightColour { 255, 255, 255 };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LiquidGlass)
};

#endif // SCHEMAS_LIQUID_GLASS_HPP_
