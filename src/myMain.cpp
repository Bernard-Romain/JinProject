#include <iostream>
#include <map>
#include <thread>
#include "myMain.h"
#include <algorithm>
#include "Game.h"
#include <SFML/Graphics.hpp>


using namespace std;

int myMain()
{
	Game game;
	game.run();
	return 0;
}
