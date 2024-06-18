#include "Entity.h"
#include "Room.h"

class Door : public Entity {
public:
	explicit(false) Door(pugi::xml_node node);

	//Getters
	std::string getDestination() const { return destination; }
private:
	std::string destination;

};