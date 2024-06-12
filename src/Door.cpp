#include "Door.h"

Door::Door(pugi::xml_node node)
	: Entity(node)
	, destination{ node.attribute("sprite").as_string() }
{}