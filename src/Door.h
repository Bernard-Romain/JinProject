#include "Entity.h"
#include "Room.h"

class Door : public Entity {
public:
	Door(pugi::xml_node node);
private:
	std::string destination;
};