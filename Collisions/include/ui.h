#pragma once
#include <iostream>
#include "layer.h"

class UI : public Layer {
public:
	UI(const sf::Vector2f& viewSize, sf::Vector2i& parentSize, sf::Vector2f position); //!<Constructor with view size
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override; //!< Draw the UI
	void setTextString(const std::string& text); //!<Set the string of m_text
	void onMouseMoved(const sf::Vector2i& pixelCoords) override;

protected:
	sf::Font m_font; //!< A font so we can write text
	sf::Text m_text; //!< A text widget which we'll use to write text
};