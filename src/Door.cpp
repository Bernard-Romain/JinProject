#include "Door.h"
#include "Game.h"

Door::Door(pugi::xml_node node, Room* room)
	: Entity(node)
	, destination{ node.attribute("destination").as_string() }
	, room(room)
{}

//TODO : changer le type de ce qui est passé, peut etre mme la logique derriere
void Door::collide_with(Player& other) {
	room->getGame()->handleCollisionPlayerDoor(this);
}