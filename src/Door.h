#include "Entity.h"
#include "Room.h"

class Door : public Entity {
public:
	explicit(false) Door(pugi::xml_node node);

	std::string getDestination() const { return destination; }
private:
	std::string destination; //Contient le nom de la room à laquelle emmène cette porte

};