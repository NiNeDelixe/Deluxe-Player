#include "LiquidGlass.hpp"

LiquidGlass::LiquidGlass()
{
    setOpaque(false);
}

void LiquidGlass::paint(juce::Graphics& g)
{
    updateBackdrop();

    drawShadow(g);
    drawBackdropBlur(g);
    drawGlass(g);
    drawBorder(g);
    drawHighlight(g);

    paintContent(g);
}

void LiquidGlass::paintContent(juce::Graphics&)
{
}

void LiquidGlass::updateBackdrop()
{
    if (backdropComponent == nullptr)
        return;

    auto bounds = getLocalBounds();

    if (bounds.isEmpty())
        return;

    backdropImage = juce::Image(
        juce::Image::ARGB,
        bounds.getWidth(),
        bounds.getHeight(),
        true);

    juce::Graphics imageGraphics(backdropImage);

    auto position = getLocalArea(
        backdropComponent,
        bounds);

    backdropComponent->paintEntireComponent(
        imageGraphics,
        true);

    if (position != juce::Rectangle<int>())
    {
        auto source = backdropImage;

        backdropImage = source.getClippedImage(
            bounds);
    }
}

void LiquidGlass::drawBackdropBlur(juce::Graphics& g)
{
    if (!backdropImage.isValid())
        return;

    if (blurAmount <= 0.0f)
        return;

    juce::Image blurred(
        juce::Image::ARGB,
        backdropImage.getWidth(),
        backdropImage.getHeight(),
        true);

    juce::Graphics blurGraphics(blurred);

    blurGraphics.drawImageAt(
        backdropImage,
        0,
        0);

    juce::ImageConvolutionKernel kernel(25);

    const int radius =
        juce::jlimit(
            1,
            50,
            static_cast<int>(blurAmount));

    kernel.createGaussianBlur(radius);

    kernel.applyToImage(
        blurred,
        blurred,
        blurred.getBounds());

    auto area = getLocalBounds().toFloat();

    juce::Path path;

    path.addRoundedRectangle(
        area,
        glassRadius);

    g.saveState();

    g.reduceClipRegion(
        path.createPathWithRoundedCorners(
            // area,
            glassRadius));

    g.setOpacity(1.0f);

    g.drawImage(
        blurred,
        getLocalBounds().toFloat());

    g.restoreState();
}

void LiquidGlass::drawGlass(juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();

    juce::ColourGradient gradient(
        glassColour.withAlpha(glassOpacity),
        bounds.getX(),
        bounds.getY(),
        glassColour.withAlpha(glassOpacity * 0.45f),
        bounds.getRight(),
        bounds.getBottom(),
        false);

    g.setGradientFill(gradient);

    g.fillRoundedRectangle(
        bounds,
        glassRadius);
}

void LiquidGlass::drawBorder(juce::Graphics& g)
{
    auto bounds = getLocalBounds()
        .toFloat()
        .reduced(0.5f);

    g.setColour(
        borderColour.withAlpha(borderOpacity));

    g.drawRoundedRectangle(
        bounds,
        glassRadius,
        1.0f);
}

void LiquidGlass::drawHighlight(juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();

    juce::Path highlight;

    highlight.addRoundedRectangle(
        bounds.reduced(1.0f),
        glassRadius);

    g.saveState();

    g.reduceClipRegion(highlight);

    juce::ColourGradient gradient(
        highlightColour.withAlpha(highlightOpacity),
        bounds.getX(),
        bounds.getY(),
        highlightColour.withAlpha(0.0f),
        bounds.getX(),
        bounds.getY() + bounds.getHeight() * 0.55f,
        false);

    g.setGradientFill(gradient);

    g.fillRect(
        bounds.getX(),
        bounds.getY(),
        bounds.getWidth(),
        bounds.getHeight() * 0.55f);

    g.restoreState();
}

void LiquidGlass::drawShadow(juce::Graphics& g)
{
    auto bounds = getLocalBounds()
        .toFloat()
        .translated(
            static_cast<float>(shadowOffset.x),
            static_cast<float>(shadowOffset.y));

    juce::Path shadowPath;

    shadowPath.addRoundedRectangle(
        bounds,
        glassRadius);

    juce::DropShadow shadow(
        juce::Colours::black.withAlpha(shadowOpacity),
        static_cast<int>(shadowRadius),
        shadowOffset);

    shadow.drawForPath(
        g,
        shadowPath);
}

void LiquidGlass::setGlassOpacity(float opacity)
{
    glassOpacity = juce::jlimit(0.0f, 1.0f, opacity);
    repaint();
}

void LiquidGlass::setBlurAmount(float amount)
{
    blurAmount = juce::jmax(0.0f, amount);
    invalidateBackdrop();
    repaint();
}

void LiquidGlass::setGlassRadius(float radius)
{
    glassRadius = juce::jmax(0.0f, radius);
    repaint();
}

void LiquidGlass::setBorderOpacity(float opacity)
{
    borderOpacity = juce::jlimit(0.0f, 1.0f, opacity);
    repaint();
}

void LiquidGlass::setHighlightOpacity(float opacity)
{
    highlightOpacity = juce::jlimit(0.0f, 1.0f, opacity);
    repaint();
}

void LiquidGlass::setShadowOpacity(float opacity)
{
    shadowOpacity = juce::jlimit(0.0f, 1.0f, opacity);
    repaint();
}

void LiquidGlass::setShadowRadius(float radius)
{
    shadowRadius = juce::jmax(0.0f, radius);
    repaint();
}

void LiquidGlass::setShadowOffset(juce::Point<int> offset)
{
    shadowOffset = offset;
    repaint();
}

void LiquidGlass::setGlassColour(juce::Colour colour)
{
    glassColour = colour;
    repaint();
}

void LiquidGlass::setBorderColour(juce::Colour colour)
{
    borderColour = colour;
    repaint();
}

void LiquidGlass::setHighlightColour(juce::Colour colour)
{
    highlightColour = colour;
    repaint();
}

float LiquidGlass::getGlassOpacity() const
{
    return glassOpacity;
}

float LiquidGlass::getBlurAmount() const
{
    return blurAmount;
}

float LiquidGlass::getGlassRadius() const
{
    return glassRadius;
}

void LiquidGlass::setBackdropComponent(juce::Component* component)
{
    backdropComponent = component;
    invalidateBackdrop();
    repaint();
}

void LiquidGlass::invalidateBackdrop()
{
    backdropImage = {};
}

void LiquidGlass::resized()
{
    invalidateBackdrop();
}