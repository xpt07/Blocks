#pragma once

#include <SFML/Graphics.hpp>

class Layer : public sf::Drawable
{
public:
	Layer(const sf::Vector2f& viewSize, sf::Vector2i& parentSize); //!< Only avalible constructor
	Layer() = delete; //!< Delete the default constructor
	Layer(const Layer&) = delete; //!< Delete the copy constructor
	virtual void onUpdate(float timestep) {}; //!< Update the scene
	virtual void onKeyPress(const sf::Keyboard::Key& key) {}; //!< On key press
	virtual void onKeyRelease(const sf::Keyboard::Key& key) {}; //!< On key release
	virtual void onMouseMoved(const sf::Vector2i& pixelCoords) {}; //!< On mouse move
	virtual void onMouseButtonPressed(const sf::Vector2i& pixelCoords, const sf::Mouse::Button& button) {}; //!< On key press
	virtual void onMouseButtonReleased(const sf::Vector2i& pixelCoords, const sf::Mouse::Button& button) {}; //!< On key release
	inline sf::View getView() const { return m_view; }; //!< Return the view
protected:
	sf::View m_view; //!< View for the layer
	sf::Vector2i& m_windowSize; //!< Size of the parent window 
	sf::Vector2f mapPixelToView(const sf::Vector2i& point); //!< Map pixel to windows viewport co-ords
private:
	Layer& operator=(const Layer&) {}; //!< Delete the assignment operator
};