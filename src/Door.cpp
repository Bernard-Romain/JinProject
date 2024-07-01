#include "Door.h"
#include "Game.h"

Door::Door(pugi::xml_node node, Room* room)
	: Entity(node)
	, destination{ node.attribute("destination").as_string() }
	, room(room)
{}

void Door::collide_with(Player& other) {
	room->getGame()->changeRoom(destination);
}