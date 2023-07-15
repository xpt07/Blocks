#include "ui.h"


UI::UI(const sf::Vector2f& viewSize, sf::Vector2i& parentSize, sf::Vector2f position) : Layer(viewSize, parentSize)
{
	const char* fontfile = "./assets/fonts/consola.ttf";
	if (!m_font.loadFromFile(fontfile))
	{
		char ch;
		std::cout << "Could not load from file: " << fontfile << std::endl;
		std::cin >> ch;
		exit(1);
	}

	m_text.setFont(m_font);
	m_text.setCharacterSize(16);
	m_text.setFillColor(sf::Color::White);
	m_text.setPosition(position);
}

void UI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.setView(m_view);
	target.draw(m_text);
}

void UI::setTextString(const std::string& text)
{
	m_text.setString(text);
}

void UI::onMouseMoved(const sf::Vector2i& pixelCoords)
{

}