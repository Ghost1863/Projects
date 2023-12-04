#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bat
{
private:
	Vector2f m_position;
	RectangleShape m_shape;

	const float m_speed = 1000.0f;

	bool m_movingright = false;
	bool m_movingleft = false;
public:
	Bat(float startX, float startY);
	FloatRect getPosition();
	RectangleShape getShape();

	void moveleft();
	void moveright();
	void stopleft();
	void stopright();
	void update(Time dt);

	
};


