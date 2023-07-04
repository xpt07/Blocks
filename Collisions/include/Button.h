#pragma once
#include "ui.h"

class Button : public UI
{
public:

    Button(const sf::Vector2f& viewSize, sf::Vector2i& parentSize, sf::Vector2f position, const std::string& buttonText);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::RectangleShape getShape() { return m_buttonshape; };

    void onMouseMoved(const sf::Vector2i& pixelCoords) override;


    void onMouseButtonPressed(const sf::Vector2i& pixelCoords, const sf::Mouse::Button& button) override;


    void onMouseButtonReleased(const sf::Vector2i& pixelCoords, const sf::Mouse::Button& button) override;


private:
    enum class ButtonState
    {
        Normal,
        Hovered,
        Pressed
    };

    sf::RectangleShape m_buttonshape;
    std::string m_buttonText;
    sf::Vector2f m_buttonSize;
    sf::Color m_buttonFillColor;
    sf::Color m_buttonOutlineColor;
    float m_buttonOutlineThickness;
    ButtonState m_buttonState;

    bool isInside(const sf::Vector2i& pixelCoords) const;
};