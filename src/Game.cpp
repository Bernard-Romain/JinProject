#include "Game.h"
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

using namespace std;

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
{
}

void Game::load()
{
	printf("Loading\n");

	pugi::xml_document doc;
	if (auto result = doc.load_file("resources/rooms.xml"); !result)
	{
		std::cerr << "Could not open file visage.xml because " << result.description() << std::endl;
		exit(1);
	}

	for (auto child : doc.children())
	{
		if (child.name() == "Room"sv) {
			auto room = std::make_unique<Room>(child);
			rooms.push_back(std::move(room));
		}
		if (child.name() == "Player"sv) {
			//TODO A IMPLEMENTER

		}
	}
	currentRoom = rooms.begin();

	cout << this->dump("");
}

string Game::dump(std::string const& indent) const {
	ostringstream oss;
	for (auto const& room : rooms) {
		oss << room->dump("");
	}
	return oss.str();
}

void Game::render()
{
	mWindow.clear();
	currentRoom->get()->render();
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
			player.manageInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			player.manageInput(event.key.code, false);
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