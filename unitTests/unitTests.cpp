#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "pugixml.hpp"

#include "Room.h"

TEST(TestCreationRoomAPartirDuXML, RoomVide) {
    std::string s = R"(<?xml version = "1.0"?>
                       <Room label="EmptyRoom" />)";
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(s.c_str());
    ASSERT_TRUE(result) << result.description(); 
    Room room{ doc.child("Room") };
    std::string room_dump_ref =
        R"(Room EmptyRoom [
]
)";
    EXPECT_EQ(room.dump(""), room_dump_ref);
}

TEST(TestCreationRoomAPartirDuXML, RoomSansPorte) {
    std::string s = R"(<?xml version = "1.0"?>
                       <Room label="DoorlessRoom" >
                           <Wall x="0" y="0" sprite="Wall"/>
                           <Monster x="10" y="10" sprite="Monster" speed="20" hp="3"/>
                           <Player x="40" y="40" sprite="Player" speed="20" hp="3"/>
                       </Room>)";
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(s.c_str());
    ASSERT_TRUE(result) << result.description(); // Si jamais result est faux, indique que le test est faux *et* affiche la string result.description() (qui contient la raison de l'erreur)
    
    Room room{ doc.child("Room") };
    std::string room_dump_ref =
        R"(Room DoorlessRoom [
| Wall x: 0, y: 0, 
| Monster x: 10, y: 10, speed: 20, hp: 3, 
| Player x: 40, y: 40, speed: 20, hp: 3, 
]
)";
    EXPECT_EQ(room.dump(""), room_dump_ref);
}

/*
* 
* REFLEXION SUR LES PORTES
* 
* Notre porte peut pas pointer directement une instance de Room, sinon c'est vraiment chiant à la création je pense
* (c'est à dire que la création change suivant l'ordre..)
* 
* Jme dis que le plus simple c'est peut être d'avoir uniquement un label dans une room, et le moment venu de la franchir, 
* on va récupérer ce label, on cherche la room correspondante dans un tableau et voilà.
* 
* A faire plus tard ! Mais du coup ce test sert plus à grand chose ^^
* 
* 
TEST(TestCreationRoomAPartirDuXML, RoomAvecPorte) {
    std::string s = R"(<?xml version = "1.0"?>
                       <Room label="Room1" >
                           <Wall x="0" y="0" sprite="Wall"/>
                           <Monster x="10" y="10" sprite="Monster" speed="20" hp="3"/>
                           <Player x="40" y="40" sprite="Player" speed="20" hp="3"/>
                       </Room>
                       <Room label="Room2" >
                           <Wall x="0" y="0" sprite="Wall"/>
                           <Monster x="10" y="10" sprite="Monster" speed="20" hp="3"/>
                           <Player x="40" y="40" sprite="Player" speed="20" hp="3"/>
                       </Room>)";
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(s.c_str());
    ASSERT_TRUE(result) << result.description(); // Si jamais result est faux, indique que le test est faux *et* affiche la string result.description() (qui contient la raison de l'erreur)

    std::map<std::string, std::unique_ptr<Room>, std::less<>> label2Room;

    for (auto child : doc.children())
    {
        auto room = std::make_unique<Room>(child);
        label2Room[room->getLabel()] = std::move(room);
    }

    Room room{ doc.child("Room") };
    std::string room_dump_ref =
        R"(Room Room1 [
| Wall x: 0, y: 0, 
| Monster x: 10, y: 10, speed: 20, hp: 3, 
| Player x: 40, y: 40, speed: 20, hp: 3, 
]
Room Room2 [
| Wall x: 0, y: 0, 
| Monster x: 10, y: 10, speed: 20, hp: 3, 
| Player x: 40, y: 40, speed: 20, hp: 3, 
]
)";
    EXPECT_EQ(room.dump(""), room_dump_ref);
}
*/