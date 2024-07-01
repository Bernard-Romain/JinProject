#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdio>
#include <pugixml.hpp>

#include "Room.h"
#include "Wall.h"
#include "Player.h"
#include "Monster.h"
#include "Door.h"
#include "Game.h"

using namespace std;

Room::Room(pugi::xml_node node, Game* game)
    : label { node.attribute("label").as_string() }
    , game { game }
{
    static const std::string_view wallStr = "Wall";
    static const std::string_view monsterStr = "Monster";
    static const std::string_view doorStr = "Door";

    for (auto child : node.children())
    {
        std::string_view childName = child.name();
        assert((childName == wallStr) || (childName == monsterStr) || (childName == doorStr));
        
        if (childName == wallStr) {
            entities.push_back(make_unique<Wall>(child));
        } else if (childName == monsterStr) {
            entities.push_back(make_unique<Monster>(child, this));
            monster++;
        } else if (childName == doorStr) {
            doors.push_back(make_unique<Door>(child, this));
        }
    }    
}

void Room::enterRoom() {
    if (state == Room_State::Undiscovered) {
        if (monster > 0) state = Room_State::Active;
        else clearRoom();
    }
}

void Room::killMonster(Entity* entity) {
    monster--;
    auto it = std::find_if(entities.begin(), entities.end(),
        [entity](const std::unique_ptr<Entity>& p) {
            return p.get() == entity;
        });
    if (it != entities.end()) {
        entities.erase(it);
    }
    else {
        std::cerr << "Monster not found" << std::endl;
    }
    if (monster == 0) clearRoom();
}

void Room::clearRoom() {
    state = Room_State::Cleared;
    game->checkIfWin();
    for (auto& door : doors) { 
        entities.push_back(move(door)); //Lorsque la room est Cleared, on met les portes dans entities, pour qu'elles soient affichées
    }
}

void Room::render(sf::RenderWindow* mWindow) const {
    for (auto const& entity : entities) {
        entity.get()->render(mWindow);
    }
}

std::string Room::dump(std::string const& indent) const{

    ostringstream oss;
    oss << indent << "Room " << label << " [" << endl;
    for (auto const& c : entities) {
        oss << c->dump(indent + "| ");
    }
    oss << indent << "]" << endl;
    return oss.str();
}
