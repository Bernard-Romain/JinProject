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
	printf("Updating");
}

void Game::save()
{
	printf("Saving");
}

void Game::processEvents()
{
	sf::Event event{ sf::Event::Count }; // Initialization to an impossible value (in order to suppress Clang-Tidy warning)
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			save();
			mWindow.close();
			break;

		default:
			// We simply ignore all other events
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