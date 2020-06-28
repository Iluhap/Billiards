using namespace std;
#define PI 3.14159
class Game 
{
private:
	/* Текстуры объектов */
	Texture Background,  
			Home_texture, Restart_texture,
			Home_hover_texture, Restart_hover_texture, Tutorial_texture, Tutorial_hover;
	Sprite  Bg_sprite, 
			Restart_sprite, Home_sprite, Tutorial_sprite;
	/* Экземпляры объектов */
	Table table;
	Cue cue;
	WhiteBall balls[10];
	RedBall play_ball;
	/* Границы поля */
	int left_board = 188;
	int above_board = 103;
	int bottom_board = 620;
	int right_board = 1185;
	int balls_counter = 0;
	bool IsGame;
public:
	Game();
	// Функция отрисовки текстур
	void Draw(RenderWindow& window);
	// Основная функция игры
	bool Start_Game(RenderWindow& window);
	float to_rad(float grad)
	{
		return grad / (180 / PI);
	}
	bool in_action()
	{
		bool flag = false;
		if ( !(play_ball.GetDx() == 0.0 && play_ball.GetDy() == 0.0) )
		{
			flag = true;
		}
		for (int i = 0; i < 10; i++)
		{
			if (!(balls[i].GetDx() == 0.0) && !(balls[i].GetDy() == 0.0))
			{
				flag = true;
			}
		}
		return flag;

	}
	float distance(Ball& first, Ball& second) 
	{
		return sqrt(pow((first.GetX() + 28) - (second.GetX() + 28), 2) + pow((first.GetY()+ 28) - (second.GetY() + 28), 2)); 
	}
	//Считаем векторы движения и скорости сталкивающихся шаров
	void calc_collision(Ball& first, Ball& second);
	//Столкновение шаров
	void collision();
	// Столкновение с границами поля
	void wall_collision();
	// Обновление позиций шаров
	void update_positions(float time);
	// Изменение позиции кия
	void CuePosition(RenderWindow &window)
	{
			cue.pixelPos = Mouse::getPosition(window);
			cue.pos = window.mapPixelToCoords(cue.pixelPos);
			cue.vecX = cue.pos.x - cue.GetSprite().getPosition().x;
			cue.vecY = cue.pos.y - cue.GetSprite().getPosition().y;
			cue.SetRotation(90 - (atan2(cue.vecX, cue.vecY)) * 180 / PI);
			cue.SetPosition(play_ball.GetX(), play_ball.GetY());
	}
	// Конец игры
	void End(RenderWindow& window);
	// Подсказка
	void Tutorial(RenderWindow& window);
};

/*------Реализация методов класса Game------*/
Game::Game()
{
	Home_texture.loadFromFile("images/Game/home.png");
	Home_hover_texture.loadFromFile("images/Game/home_hover.png");

	Restart_texture.loadFromFile("images/Game/restart.png");
	Restart_hover_texture.loadFromFile("images/Game/restart_hover.png");


	Background.loadFromFile("images/Game/Background.png");

	Tutorial_texture.loadFromFile("images/Game/Tutorial/tutorial_button.png");
	Tutorial_hover.loadFromFile("images/Game/Tutorial/tutorial_button_hover.png");
	Tutorial_sprite.setTexture(Tutorial_texture);
	Tutorial_sprite.setPosition(661, 688);

	Bg_sprite.setTexture(Background);
	Home_sprite.setTexture(Home_texture);
	Restart_sprite.setTexture(Restart_texture);

	Bg_sprite.setPosition(0, 0);
	Home_sprite.setPosition(374, 690);
	Restart_sprite.setPosition(742, 690);
	

	table.SetPosition(45, 120);
	play_ball.SetPosition(400, 368);

	cue.GetSprite().setOrigin(- play_ball.GetRadius() * 2,cue.GetSprite().getTextureRect().height / 2);
	cue.SetPosition(play_ball.GetX(), play_ball.GetY());
	
	//Задаємо початкові позиції шарів

	balls[0].SetPosition(941,368);
	balls[1].SetPosition(968,352);
	balls[2].SetPosition(968,385);
	balls[3].SetPosition(996,335);
	balls[4].SetPosition(996,368);
	balls[5].SetPosition(996,400);
	balls[6].SetPosition(1024, 319);
	balls[7].SetPosition(1024, 351);
	balls[8].SetPosition(1024, 384);	
	balls[9].SetPosition(1024, 416);
}

void Game::Draw(RenderWindow& window)
{
	window.draw(Bg_sprite);
	window.draw(table.Get_Table_Sprite());
	window.draw(table.Get_Arrow_Sprite());
	window.draw(Home_sprite);
	window.draw(Restart_sprite);
	window.draw(Tutorial_sprite);
	window.draw(play_ball.GetSprite());
	for (int i = 0; i < 10; i++)
	{
		window.draw(balls[i].GetSprite());
	}
	window.draw(cue.GetSprite());
}

bool Game::Start_Game(RenderWindow& window)
{
	IsGame = true;
	Clock clock;
	int fps = 60;

	while (IsGame)
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
		// Кнопка Home
		if (IntRect(374, 690, 224, 64).contains(Mouse::getPosition(window)))
		{
			Home_sprite.setTexture(Home_hover_texture);
			if (Mouse::isButtonPressed(Mouse::Left)) { window.clear(); IsGame = false; return false; }
		}
		else
		{
			Home_sprite.setTexture(Home_texture);
		}

		//Кнопка Restart
		if (IntRect(742, 690, 278, 64).contains(Mouse::getPosition(window)))
		{
			Restart_sprite.setTexture(Restart_hover_texture);
			if (Mouse::isButtonPressed(Mouse::Left)) { window.clear(); return true; }
		}
		else { Restart_sprite.setTexture(Restart_texture); }

		if (balls_counter == 10)
		{
			End(window);
			balls_counter = 0;
			return true;
		}

		if (IntRect(661, 688, 44, 73).contains(Mouse::getPosition(window)))
		{
			Tutorial_sprite.setTexture(Tutorial_hover);
			if (Mouse::isButtonPressed(Mouse::Left)) { Tutorial(window); }
		}
		else { Tutorial_sprite.setTexture(Tutorial_texture); }

		// Изменения значения на шкале
		if (Mouse::isButtonPressed(Mouse::Left) && IntRect(table.Get_Table_Sprite().getPosition().x, table.Get_Table_Sprite().getPosition().y, table.Get_Table_Sprite().getTextureRect().width, table.Get_Table_Sprite().getTextureRect().height).contains(Mouse::getPosition(window)))
		{
			table.SetPosition(table.GetX(), Mouse::getPosition(window).y - table.GetHeigth() / 2);
		}

		//Отлавливаем координаты кия
		if (!in_action())
		{

			CuePosition(window);
			if (Mouse::isButtonPressed(Mouse::Right))
			{
				play_ball.GetVector().SetVector(cos(to_rad(cue.GetSprite().getRotation() - 180)), sin(to_rad(cue.GetSprite().getRotation() - 180)));
				play_ball.SetDiff(play_ball.GetVector().GetX() * table.GetPower(), play_ball.GetVector().GetY() * table.GetPower());
			}

		}

		// Ищем столкновение шаров
		collision();

		wall_collision();

		update_positions(0.01);

		window.clear();
		this->Draw(window);
		window.display();

		Sleep(1000 / fps);

	}
}

void Game::calc_collision(Ball& first, Ball& second)
{
	Vector v1 = first.GetVector();
	Vector v2 = second.GetVector();
	Vector center1(second.GetX() - first.GetX(), second.GetY() - first.GetY());
	Vector w1 = v1 + center1 * -1;

	float mul = 0.9;
	float v_dx = first.GetDx() + second.GetDx();
	float v_dy = first.GetDy() + second.GetDy();

	first.SetVector(w1);
	first.SetDiff(first.GetVector().GetX() * fabs(v_dx) * mul, first.GetVector().GetY() * fabs(v_dy) * mul);

	Vector center2(first.GetX() - second.GetX(), first.GetY() - second.GetY());
	Vector w2 = v2 + center2 * -1;
	second.SetVector(w2);

	second.SetDiff(second.GetVector().GetX() * fabs(v_dx)* mul, second.GetVector().GetY() * fabs(v_dy)* mul);
}

void Game::collision()
{
	for (int i = 0; i < 10; i++)
	{
		if (distance(play_ball, balls[i]) <= play_ball.GetRadius() * 2)
		{
			//Вычисляем направление векторов сопрекосающихся векторов
			play_ball.SetPosition(play_ball.GetX() - play_ball.GetDx(), play_ball.GetY() - play_ball.GetDy());
			balls[i].SetPosition(balls[i].GetX() - balls[i].GetDx(), balls[i].GetY() - balls[i].GetDy());
			calc_collision(play_ball, balls[i]);
		}
	}

	for (int i = 0; i < 10; i++)
	{
		for (int j = i + 1; j < 10; j++)
		{
			if (distance(balls[i], balls[j]) <= balls[i].GetRadius() * 2)
			{

				//Вычисляем направление векторов сопрекосающихся векторов
				balls[i].SetPosition(balls[i].GetX() - balls[i].GetDx(), balls[i].GetY() - balls[i].GetDy());
				balls[j].SetPosition(balls[j].GetX() - balls[j].GetDx(), balls[j].GetY() - balls[j].GetDy());
				calc_collision(balls[i], balls[j]);
			}
		}
	}
}

void Game::wall_collision()
{
	int counter = 0;
	if (play_ball.GetX() - play_ball.GetRadius() * 2 <= left_board)
	{
		play_ball.SetX(left_board + play_ball.GetRadius() * 2);
		play_ball.SetDiff(-1 * play_ball.GetDx(), play_ball.GetDy());
		counter++;
	}
	if (play_ball.GetX() + play_ball.GetRadius() * 2 >= right_board)
	{
		play_ball.SetX(right_board - play_ball.GetRadius() * 2);
		play_ball.SetDiff(-1 * play_ball.GetDx(), play_ball.GetDy());
		counter++;
	}
	if (play_ball.GetY() - play_ball.GetRadius() * 2 <= above_board)
	{
		play_ball.SetY(above_board + play_ball.GetRadius() * 2);
		play_ball.SetDiff(play_ball.GetDx(), -1 * play_ball.GetDy());
		counter++;
	}
	if (play_ball.GetY() + play_ball.GetRadius() * 2 >= bottom_board)
	{
		play_ball.SetY(bottom_board - play_ball.GetRadius() * 2);
		play_ball.SetDiff(play_ball.GetDx(), -1 * play_ball.GetDy());
		counter++;
	}
	if (counter == 2)
	{
		// Шар попал в лузу
		play_ball.SetPosition(300, 340);
		play_ball.SetDiff(0, 0);
	}
	counter = 0;
	for (int i = 0; i < 10; i++)
	{
		if (balls[i].GetX() < 0 && balls[i].GetY() < 0)
		{
			continue;
		}
		else
		{
			if (balls[i].GetX() - balls[i].GetRadius() * 2 <= left_board)
			{
				balls[i].SetX(left_board + balls[i].GetRadius() * 2);
				balls[i].SetDiff(-1 * balls[i].GetDx(), balls[i].GetDy());
				counter++;
			}
			if (balls[i].GetX() + balls[i].GetRadius() * 2 >= right_board)
			{
				balls[i].SetX(right_board - balls[i].GetRadius() * 2);
				balls[i].SetDiff(-1 * balls[i].GetDx(), balls[i].GetDy());
				counter++;
			}
			if (balls[i].GetY() - balls[i].GetRadius() * 2 <= above_board)
			{
				balls[i].SetY(above_board + balls[i].GetRadius() * 2);
				balls[i].SetDiff(balls[i].GetDx(), -1 * balls[i].GetDy());
				counter++;
			}
			if (balls[i].GetY() + balls[i].GetRadius() * 2 >= bottom_board)
			{
				balls[i].SetY(bottom_board - balls[i].GetRadius() * 2);
				balls[i].SetDiff(balls[i].GetDx(), -1 * balls[i].GetDy());
				counter++;
			}
			if (counter == 2)
			{
				balls[i].SetPosition(-28, -28);
				balls[i].SetDiff(0, 0);
				balls_counter++;
			}
			counter = 0;
		}
	}
}

void Game::update_positions(float time)
{
	float mul;
	if (fabs(play_ball.GetDx()) < 1 && fabs(play_ball.GetDy()) < 1)
	{
		play_ball.SetDiff(0, 0);
		play_ball.GetVector().SetVector(0, 0);
	}
	if (play_ball.GetDx() != 0 && play_ball.GetDy() != 0)
	{
		play_ball.SetDiff(play_ball.GetDx() * (1 - time), play_ball.GetDy() * (1 - time));
	}
	play_ball.SetPosition(play_ball.GetDx() + play_ball.GetX(), play_ball.GetDy() + play_ball.GetY());

	for (int i = 0; i < 10; i++)
	{
		if (fabs(balls[i].GetDx()) < 1 && fabs(balls[i].GetDy()) < 1)
		{
			balls[i].SetDiff(0.0, 0.0);
			balls[i].GetVector().SetVector(0, 0);

		}
		if (balls[i].GetDx() != 0 && balls[i].GetDy() != 0)
		{
			balls[i].SetDiff(balls[i].GetDx() * (1 - time), balls[i].GetDy() * (1 - time));
		}
		balls[i].SetPosition(balls[i].GetX() + balls[i].GetDx(), balls[i].GetY() + balls[i].GetDy());
	}
}

void Game::End(RenderWindow& window)
{
	Texture Backgroud, close_button, close_hover;
	Backgroud.loadFromFile("images/Game/End/gameover.png");
	close_button.loadFromFile("images/Game/End/close.png");
	close_hover.loadFromFile("images/Game/End/close_hover.png");
	Sprite Bg_sprite(Backgroud), close_sprite(close_button);
	Bg_sprite.setPosition(160, 84);
	close_sprite.setPosition(1178, 73);
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

void Game::Tutorial(RenderWindow& window)
{
	Texture Backgroud, close_button, close_hover;
	Backgroud.loadFromFile("images/Game/Tutorial/tutorial.png");
	close_button.loadFromFile("images/Game/Tutorial/close.png");
	close_hover.loadFromFile("images/Game/Tutorial/close_hover.png");
	Sprite Bg_sprite(Backgroud), close_sprite(close_button);
	Bg_sprite.setPosition(160, 84);
	close_sprite.setPosition(1178, 73);
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