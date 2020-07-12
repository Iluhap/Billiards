#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <time.h>
#include <Windows.h>
using namespace sf;
#include "Menu.h"

#define PI 3.14159265

using namespace std;

int main()
{
	Menu menu;
	setlocale(LC_ALL, ".1251");
	RenderWindow window(VideoMode(1366, 768), "Billiards");
	while (window.isOpen())
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
		menu.Start_menu(window);
	}
    return 0;
}
