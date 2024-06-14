#pragma once
#include "Player.h"
#include "Room.h"

class Game {

	static std::string destination;

public:
	Game();
	void	run();
	std::string dump(std::string const& indent) const;

	void onPlayerCollision(Entity* entity);

private:
	void	processEvents();
	void	load();
	void	render();
	void	update();
	void	save();

	sf::RenderWindow		mWindow{ sf::VideoMode::getFullscreenModes()[0], "SFML Application", sf::Style::Close};
	std::unique_ptr<Player> player;
	std::vector<std::unique_ptr<Room>> rooms;
	std::vector<std::unique_ptr<Room>>::iterator currentRoom;
	static const sf::Time	TimePerFrame;



};