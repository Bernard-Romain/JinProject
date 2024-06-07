#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "pugixml.hpp"

#include "Room.h"

TEST(TestCreationRoomAPartirDuXML, RoomVide) {
    std::string s = R"(<?xml version = "1.0"?>
                       <Room />)";
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(s.c_str());
    ASSERT_TRUE(result) << result.description(); 
    Room room{ doc.child("Room") };
    std::string room_dump_ref =
        R"(Room [
]
)";
    EXPECT_EQ(room.dump(""), room_dump_ref);
}

TEST(TestCreationRoomAPartirDuXML, RoomAvecMurs) {
    std::string s = R"(<?xml version = "1.0"?>
                       <Room>
                           <Wall x="0" y="0" sprite="Wall"/>
                           <Wall x="10" y="10" sprite="Wall"/>
                       </Room>)";
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(s.c_str());
    ASSERT_TRUE(result) << result.description(); // Si jamais result est faux, indique que le test est faux *et* affiche la string result.description() (qui contient la raison de l'erreur)
    
    Room room{ doc.child("Room") };
    std::string room_dump_ref =
        R"(Room [
| Wall x: 0, y: 0, 
| Wall x: 10, y: 10, 
]
)";
    EXPECT_EQ(room.dump(""), room_dump_ref);
}
