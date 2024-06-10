#include "Player.h"
#include "Room.h"

class Game {
public:
	Game();
	void	run();

private:
	void	processEvents();
	void	load();
	void	render();
	void	update(sf::Time elapsedTime);
	void	save();

	sf::RenderWindow		mWindow{ sf::VideoMode::getFullscreenModes()[0], "SFML Application", sf::Style::Close};
	std::unique_ptr<Player> player;
	std::vector<std::unique_ptr<Room>> rooms;
	static const sf::Time	TimePerFrame;

};