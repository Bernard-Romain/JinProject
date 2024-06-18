 #pragma once
#include "Player.h"
#include "Room.h"
#include "Door.h"
#include <SFML/Audio.hpp>

class Game {

public:
	Game() = default;
	void	run();

	void onPlayerCollision(Entity* entity);
	void kill(int) const;

private:
	void	processEvents();
	void	load();
	void	render();
	void	update();
	void	save() const;

	void	handleCollisionPlayerDoor(const Door* door);
	void	setCallbacks();

	sf::RenderWindow		mWindow{ sf::VideoMode::getFullscreenModes()[0], "SFML Application", sf::Style::Close};
	std::unique_ptr<Player> player;
	std::vector<std::unique_ptr<Room>> rooms;
	std::vector<std::unique_ptr<Room>>::iterator currentRoom;
	static const sf::Time	TimePerFrame;

	bool win = false;
	sf::Sprite winSprite;
	sf::Texture winTexture;

	bool loose = false;
	sf::Sprite looseSprite;
	sf::Texture looseTexture;

	sf::SoundBuffer winSoundBuffer;
	sf::Sound winSound;

	sf::SoundBuffer looseSoundBuffer;
	sf::Sound looseSound;
};