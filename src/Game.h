#include "Player.h"
#include "Room.h"

class Game {
public:
	void load();
	void render();
	void update();
	void save();
private:
	std::unique_ptr<Player> player;
	std::vector<std::unique_ptr<Room>> rooms;
};