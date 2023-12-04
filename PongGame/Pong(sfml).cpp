#include <SFML/Graphics.hpp>
#include "Bat.h"
#include"Ball.h"
#include<cstdlib>
#include<sstream>

int main()
{
	VideoMode vm(1920, 1080);

	RenderWindow window(vm, "Pong", Style::Fullscreen);

	int score = 0;
	int lives = 3;

	Bat bat(1920 / 2, 1080 - 20);
	Bat batup(1920 / 2, 0 + 20);
	Ball ball(1900 / 2, 0);

	Text hud;
	Font font;
	font.loadFromFile("fonts/papernotes.ttf ");
	hud.setFont(font);
	hud.setCharacterSize(75);
	hud.setFillColor(Color::Red);
	hud.setPosition(20, 20);

	Clock clock;

	while (window.isOpen())
	{
		//handle player's input//
		/*************************************/
		Event e;
		while (window.pollEvent(e)) {
			if (e.type == e.Closed)
			{
				//quit the game when window is closed
				window.close();
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			bat.moveleft();		
		}
		else
		{
			bat.stopleft();
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			bat.moveright();			
		}
		else
		{
			bat.stopright();
		}

		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			batup.moveleft();
		}
		else
		{
			batup.stopleft();
		}

		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			batup.moveright();
		}
		else
		{
			batup.stopright();
		}
		//updating scene//
		/*************************************/
		
		Time dt = clock.restart();
		
		bat.update(dt);
		batup.update(dt);
		ball.update(dt);
		
		std::stringstream ss;
		ss << "Score:" << score << "  Lives:" << lives;
		hud.setString(ss.str());

		//has ball hit the bottom?
		if (ball.getposition().top > window.getSize().y)
		{
		//reverse
		ball.reboundbottom();
		lives--;
		}
		//check 0 lives
		if (lives < 1)
		{
			score = 0;
			lives = 3;
		}
		//has hitted top
		if (ball.getposition().top < 0)
		{
			//ball.reboundbatortop();
			ball.reboundbottom();
			lives--;
		}
		//has hitted sides
		if (ball.getposition().left < 0 ||
			ball.getposition().left+ball.getposition().width >window.getSize().x)
		{
			ball.reboundsides();
		}
		//has hitted the bat
		if ((ball.getposition().intersects(bat.getPosition()))
			||(ball.getposition().intersects(batup.getPosition())))
		{
			score++;
			ball.reboundbatortop();			
		}
	//drawing scene//
	/*************************************/
		window.clear();
		window.draw(hud);				
		//grab rect shape from bat and draw it
		window.draw(bat.getShape());
		window.draw(ball.getshape());
		window.draw(batup.getShape());
		window.display();
	
	}
}

