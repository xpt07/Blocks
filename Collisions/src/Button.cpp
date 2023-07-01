#include "Button.h"

Button::Button(const sf::Vector2f& viewSize, sf::Vector2i& parentSize, sf::Vector2f position, const std::string& buttonText)
    : UI(viewSize, parentSize, position), m_buttonText(buttonText)
{
    m_buttonSize = sf::Vector2f(120.0f, 40.0f);
    m_buttonFillColor = sf::Color::Blue;
    m_buttonOutlineColor = sf::Color::White;
    m_buttonOutlineThickness = 2.0f;
    m_buttonState = ButtonState::Normal;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.setView(m_view);

    // Draw the button shape
    sf::RectangleShape buttonShape(m_buttonSize);
    buttonShape.setPosition(m_text.getPosition());
    buttonShape.setFillColor(m_buttonFillColor);
    buttonShape.setOutlineColor(m_buttonOutlineColor);
    buttonShape.setOutlineThickness(m_buttonOutlineThickness);
    target.draw(buttonShape);

    // Draw the button text
    target.draw(m_text);
}

void Button::onMouseMoved(const sf::Vector2i& pixelCoords)
{
    if (isInside(pixelCoords))
    {
        m_buttonState = ButtonState::Hovered;
        m_buttonOutlineColor = sf::Color::Yellow;
    }
    else
    {
        m_buttonState = ButtonState::Normal;
        m_buttonOutlineColor = sf::Color::White;
    }
}

void Button::onMouseButtonPressed(const sf::Vector2i& pixelCoords, const sf::Mouse::Button& button)
{
    if (isInside(pixelCoords) && button == sf::Mouse::Left)
    {
        m_buttonState = ButtonState::Pressed;
        m_buttonFillColor = sf::Color::Red;
    }
}

void Button::onMouseButtonReleased(const sf::Vector2i& pixelCoords, const sf::Mouse::Button& button)
{
    if (isInside(pixelCoords) && button == sf::Mouse::Left && m_buttonState == ButtonState::Pressed)
    {
        // Button was clicked
        // Perform button action here
        std::cout << "Button clicked: " << m_buttonText << std::endl;
    }

    m_buttonState = ButtonState::Normal;
    m_buttonFillColor = sf::Color::Blue;
}

bool Button::isInside(const sf::Vector2i& pixelCoords) const
{
    sf::FloatRect buttonBounds(m_text.getPosition(), m_buttonSize);
    return buttonBounds.contains(static_cast<sf::Vector2f>(pixelCoords));
}
