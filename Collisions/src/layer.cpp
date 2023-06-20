#include "layer.h"

Layer::Layer(const sf::Vector2f& viewSize, sf::Vector2i& parentSize) : m_windowSize(parentSize)
{
	m_view.reset(sf::FloatRect(0, 0, viewSize.x, viewSize.y));
}

sf::Vector2f Layer::mapPixelToView(const sf::Vector2i & point)
{
	float width = static_cast<float>(m_windowSize.x);
	float height = static_cast<float>(m_windowSize.y);
	const sf::FloatRect& viewport = m_view.getViewport();

	sf::FloatRect viewRect(
		0.5f + width * viewport.left,
		0.5f + height * viewport.top,
		0.5f + width * viewport.width,
		0.5f + height * viewport.height
	);

	sf::Vector2f normalised;
	normalised.x = -1.f + 2.f * (point.x - viewRect.left) / viewRect.width;
	normalised.y = 1.f - 2.f * (point.y - viewRect.top) / viewRect.height;

	return m_view.getInverseTransform().transformPoint(normalised);
}






