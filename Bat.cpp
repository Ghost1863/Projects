#include "Bat.h"

Bat::Bat(float startX, float startY)
{
	m_position.x = startX;
	m_position.y = startY;

	m_shape.setSize(sf::Vector2f(100, 5));
	m_shape.setPosition(m_position);
}
FloatRect Bat::getPosition()
{
	return m_shape.getGlobalBounds(); 
}
RectangleShape Bat::getShape() 
{
	return m_shape;
}
void Bat::moveleft()
{
	m_movingleft = true;
}
void Bat::moveright()
{
	m_movingright = true;
}
void Bat::stopleft()
{
	m_movingleft = false;
	

}
void Bat::stopright()
{
	m_movingright = false;
}
void Bat::update(Time dt)
{
	if (m_movingleft)
	{
		if (m_position.x > 0) 
			m_position.x -= m_speed * dt.asSeconds();
		else m_position.x = 1900;
	}

	if (m_movingright)
	{
		if (m_position.x < 1920)
			m_position.x += m_speed * dt.asSeconds();
		else m_position.x = 0;
	}
	
	m_shape.setPosition(m_position);
}

