#include "Ball.h"


Ball::Ball(float startX, float startY)
{
	m_position.x = startX;
	m_position.y = startY;

	m_shape.setSize(Vector2f(10, 10));
	m_shape.setPosition(m_position);
}
FloatRect Ball::getposition()
{
	return m_shape.getGlobalBounds();
}
RectangleShape Ball::getshape()
{
	return m_shape;
}
float Ball::getXvelocity()
{
	return m_directonX;
}
void Ball::reboundsides()
{
	m_directonX = -m_directonX;
}
void Ball::reboundbottom()
{
	m_position.y = 1080/2;
	m_position.x = 1980/2;
	//m_directonY = -m_directonY;?
}

void Ball::reboundbatortop()
{
	m_directonY = -m_directonY;
}
void Ball::update(Time dt)
	{
	m_position.x += m_directonX * m_speed * dt.asSeconds();
	m_position.y += m_directonY * m_speed * dt.asSeconds();

	m_shape.setPosition(m_position);
	}

