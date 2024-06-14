#include "Game.h"
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Door.h"

using namespace std;

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);
std::string destination = "void";

Game::Game()
{
}

void Game::load()
{
	printf("Loading\n");

	pugi::xml_document doc;
	if (auto result = doc.load_file("resources/rooms.xml"); !result)
	{
		std::cerr << "Could not open file rooms.xml because " << result.description() << std::endl;
		exit(1);
	}

	for (auto child : doc.children())
	{
		if (child.name() == "Room"sv) {
			auto room = std::make_unique<Room>(child);
			rooms.push_back(std::move(room));
		}
		if (child.name() == "Player"sv) {
			player = std::make_unique<Player>(child);
		}
	}
	currentRoom = rooms.begin();
	(*currentRoom)->discover();
	player->setCollisionCallback(this, &Game::onPlayerCollision);
	player->setKillCallback(this, &Game::kill);

	cout << currentRoom->get()->dump("");
	cout << player->dump("");
}

void Game::onPlayerCollision(Entity* entity) {
	if (entity->getLabel() == "Door"sv) {
		cout << "DOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOR\n";
		if (Door* door = dynamic_cast<Door*>(entity)) {
			std::cout << "Confirmed: It's a door!" << std::endl;

			for (auto it = rooms.begin(); it != rooms.end(); ++it) {
				cout << (*it)->getLabel() << " == " << door->getDestination() << " : ";
				if ((*it)->getLabel() == door->getDestination()) {
					currentRoom = it;
					std::cout << "Switched to room: " << door->getDestination() << std::endl;
					if ((*it)->getState() == Room_State::Undiscovered) (*it)->discover();
					player->reversePosition();
					return;
				}
				else { cout << "false !\n"; }
			}
		}
	}
}

void Game::kill(int i) {
	currentRoom->get()->entities.erase(currentRoom->get()->entities.begin() + i);
	currentRoom->get()->killMonster();
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
	currentRoom->get()->render(&mWindow);
	player->render(&mWindow);
	mWindow.display();
}

void Game::update()
{
	currentRoom->get()->update();
	player->update(currentRoom->get()->entities);
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

		case sf::Event::MouseButtonPressed:
			player->shoot(sf::Mouse::getPosition(mWindow));
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
			update();
		}
		render();
	}
}