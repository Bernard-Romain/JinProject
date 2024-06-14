#include "Entity.h"
#include "Room.h"

class Door : public Entity {
public:
	Door(pugi::xml_node node);
	std::string getDestination() { return destination; }
private:
	std::string destination;
};