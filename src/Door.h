#include "Entity.h"
#include "Room.h"

class Door : public Entity {
public:
private:
	std::unique_ptr<Room> destination;
};