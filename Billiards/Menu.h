class Menu;
#include <math.h>
#include "Logic.h"
#include "Game.h"

void FaQ_bar(RenderWindow& window)
{
	Texture Backgroud, close_button, close_hover;
	Backgroud.loadFromFile("images/menu/FaQ/faq.png");
	close_button.loadFromFile("images/menu/FaQ/close.png");
	close_hover.loadFromFile("images/menu/FaQ/close_hover.png");
	Sprite Bg_sprite(Backgroud), close_sprite(close_button);
	Bg_sprite.setPosition(183, 78);
	close_sprite.setPosition(1199, 72);
	bool trigger = false;

	bool IsWindow = true;
	while (IsWindow)
	{
		if (IntRect(1185, 58, 62, 62).contains(Mouse::getPosition(window))) { close_sprite.setTexture(close_hover); trigger = true; }
		else { close_sprite.setTexture(close_button); }

		if ((Mouse::isButtonPressed(Mouse::Left)) && trigger)
		{
			IsWindow = false;
		}
		window.draw(Bg_sprite);
		window.draw(close_sprite);
		window.display();
	}
}

class Menu
{
private:
	Texture NewGame, ExitGame, FaQ, Background, // Текстуры кнопок меню
	NewGame_hover, ExitGame_hover, FaQ_hover;
	Sprite NewGame_sprite, ExitGame_sprite, FaQ_sprite, Background_sprite;
	bool IsMenu;
public:
	Menu();

	void Draw(RenderWindow& window);
	
	void Start_menu(RenderWindow& window);

	void FaQ_bar(RenderWindow& window);
};

/*------Реалізація методів классу Menu------*/
Menu::Menu()
{
	// Загрузка текстур меню
	NewGame.loadFromFile("images/menu/NewGame.png");
	ExitGame.loadFromFile("images/menu/ExitGame.png");
	FaQ.loadFromFile("images/menu/FaQ.png");
	Background.loadFromFile("images/menu/Background.png");

	NewGame_hover.loadFromFile("images/menu/NewGame_hover.png");
	ExitGame_hover.loadFromFile("images/menu/ExitGame_hover.png");
	FaQ_hover.loadFromFile("images/menu/FaQ_hover.png");

	NewGame_sprite.setTexture(NewGame);
	ExitGame_sprite.setTexture(ExitGame);
	FaQ_sprite.setTexture(FaQ);
	Background_sprite.setTexture(Background);

	NewGame_sprite.setPosition(493, 503);
	ExitGame_sprite.setPosition(211, 544);
	FaQ_sprite.setPosition(1032, 544);
	Background_sprite.setPosition(0, 0);

}

void Menu::Draw(RenderWindow& window)
{
	window.draw(Background_sprite);
	window.draw(NewGame_sprite);
	window.draw(ExitGame_sprite);
	window.draw(FaQ_sprite);

}
// Основная функция класса Меню
void Menu::Start_menu(RenderWindow& window)
{
	IsMenu = true;
	int menu_num = 0;
	while (IsMenu)
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				exit(0);
			}
		}

		/*-----Мышь наводиться на кнопки-----*/
		// Кнопка Play
		if (IntRect(493, 503, 385, 100).contains(Mouse::getPosition(window))) {
			NewGame_sprite.setTexture(NewGame_hover);
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				bool flag = true;
				while (flag) 
				{
					Game game;
					window.clear();
					flag = game.Start_Game(window);
				}

			}
		}
		else { NewGame_sprite.setTexture(NewGame); }

		// Кнопка Exit
		if (IntRect(211, 544, 140, 145).contains(Mouse::getPosition(window)))
		{
			ExitGame_sprite.setTexture(ExitGame_hover);
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				window.close(); 
				exit(0);
			}
		}
		else { ExitGame_sprite.setTexture(ExitGame); }
		// Кнопка FaQ
		if (IntRect(1032, 544, 140, 145).contains(Mouse::getPosition(window)))
		{
			FaQ_sprite.setTexture(FaQ_hover);
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				FaQ_bar(window);
			}
		}
		else { FaQ_sprite.setTexture(FaQ); }

		window.clear();
		this->Draw(window);
		window.display();
	}
}

// Вкладка с информауией
void Menu::FaQ_bar(RenderWindow& window)
{
	Texture Backgroud, close_button, close_hover;
	Backgroud.loadFromFile("images/menu/FaQ/faq.png");
	close_button.loadFromFile("images/menu/FaQ/close.png");
	close_hover.loadFromFile("images/menu/FaQ/close_hover.png");
	Sprite Bg_sprite(Backgroud), close_sprite(close_button);
	Bg_sprite.setPosition(183, 78);
	close_sprite.setPosition(1199, 72);
	bool trigger = false;

	bool IsWindow = true;
	while (IsWindow)
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				exit(0);
			}
		}
		if (IntRect(1185, 58, 62, 62).contains(Mouse::getPosition(window))) { close_sprite.setTexture(close_hover); trigger = true; }
		else { close_sprite.setTexture(close_button); }

		if ((Mouse::isButtonPressed(Mouse::Left)) && trigger)
		{
			IsWindow = false;
		}
		window.draw(Bg_sprite);
		window.draw(close_sprite);
		window.display();
	}
}