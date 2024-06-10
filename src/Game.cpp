#include "Game.h"

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
{
}

void Game::load()
{
	printf("Loading");
}

void Game::render()
{
	mWindow.clear();
	mWindow.display();
}

void Game::update(sf::Time elapsedTime)
{
	//printf("Updating");
}

void Game::save()
{
	printf("Saving");
}

void Game::processEvents()
{
	sf::Event event{ sf::Event::Count }; 
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			player->manageInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			player->manageInput(event.key.code, false);
			break;

		case sf::Event::Closed:
			save();
			mWindow.close();
			break;

		default:
			break;
		}
	}
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	load();
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			update(TimePerFrame);
		}
		render();
	}
}