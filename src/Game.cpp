#include "Game.h"
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

void Game::load()
{
	printf("Loading\n");

	pugi::xml_document doc; //Charge le niveau depuis le fichier rooms.xml, qui permet d'initialiser les rooms
	if (auto result = doc.load_file("resources/rooms.xml"); !result)
	{
		cerr << "Could not open file rooms.xml because " << result.description() << endl;
		exit(1);
	}

	for (auto child : doc.children())
	{
		if (child.name() == "Room"sv) {
			rooms.push_back(make_unique<Room>(child,this));
		}
		if (child.name() == "Player"sv) {
			player = make_unique<Player>(child,this);
		}
	}

	currentRoom = rooms.begin();
	(*currentRoom)->enterRoom(); //Discover permet de dire que l'on découvre la room, changeant son statut suivant les monstres dedans

	cout << currentRoom->get()->dump("");
	cout << player->dump("");

	initialiseSprites();
}

void Game::triggerLoose() {
	loose = true;
	looseSound.play();
}

void Game::checkIfWin() {
	win = true;
	for (auto it = rooms.begin(); it != rooms.end(); ++it) {
		if ((*it)->getState() != Room_State::Cleared)
		{
			win = false;
		}
	}
	if (win) winSound.play();
}

void Game::render()
{
	mWindow.clear();
	currentRoom->get()->render(&mWindow);
	player->render(&mWindow);
	if (win) mWindow.draw(winSprite);
	if (loose) mWindow.draw(looseSprite);
	mWindow.display();
}

void collide(Entity& first, Entity& second) {
	first.collide_with(second);
}

void Game::update()
{
	if (!(win || loose)) //TODO :le changer de place, peut etre ne plus rentrer dans cette boucle quand c'est gagné
	{
		player->update(currentRoom->get()->entities);

		for (auto& entity : currentRoom->get()->entities) {
			entity.get()->update(currentRoom->get()->entities);
			for (auto& entity2 : currentRoom->get()->entities) {
				if (entity2.get()->collide(*entity)) {
					collide(*entity, *entity2);
					collide(*entity2, *entity);
				}
			}
			if (entity.get()->collide(*player.get())) {
				collide(*player.get(), *entity);
				collide(*entity, *player.get());
			}
		}
	}
}

void Game::save () const
{
	//TODO
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

void Game::changeRoom(const string &destination) {
	for (auto it = rooms.begin(); it != rooms.end(); ++it) {
		if ((*it)->getLabel() == destination) {
			currentRoom = it;
			(*it)->enterRoom();
			break;
		}
	}
}

void Game::initialiseSprites() {
	winTexture.loadFromFile("resources/sprites/Win.png");
	winSprite.setScale(sf::Vector2f(3, 3));
	winSprite.setTexture(winTexture);
	winSprite.setPosition(sf::Vector2f(((float)mWindow.getSize().x - winSprite.getGlobalBounds().width) / 2, ((float)mWindow.getSize().y - winSprite.getGlobalBounds().height) / 2));
	looseTexture.loadFromFile("resources/sprites/Loose.png");
	looseSprite.setScale(sf::Vector2f(3, 3));
	looseSprite.setTexture(looseTexture);
	looseSprite.setPosition(sf::Vector2f(((float)mWindow.getSize().x - looseSprite.getGlobalBounds().width) / 2, ((float)mWindow.getSize().y - looseSprite.getGlobalBounds().height) / 2));

	winSoundBuffer.loadFromFile("resources/audios/win.mp3");
	winSound.setBuffer(winSoundBuffer);
	looseSoundBuffer.loadFromFile("resources/audios/loose.mp3");
	looseSound.setBuffer(looseSoundBuffer);
}