 #pragma once
#include "Player.h"
#include "Room.h"
#include "Door.h"

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

	bool win;
	sf::Sprite winSprite;
	sf::Texture winTexture = sf::Texture();

};