#pragma once
#include<SFML/Graphics.hpp>

using namespace sf;

class Ball
{
private:
	Vector2f m_position;
	RectangleShape m_shape;

	float m_speed = 1800.0f;
	float m_directonX = .2f;
	float m_directonY = .2f;

public:

	Ball(float startX, float startY);

	FloatRect getposition();
	RectangleShape getshape();
	float getXvelocity();
	
	void reboundsides();
	void reboundbottom();	
	void reboundbatortop();

	void update(Time dt);
	

};