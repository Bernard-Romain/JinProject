#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "pugixml.hpp"

#include "Room.h"

TEST(TestCreationRoomAPartirDuXML, RoomVide) {
    std::string s = R"(<?xml version = "1.0"?>
                       <Room label="testCircle" x="0" y="1" r="2" color="Black" />)";
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(s.c_str());
    ASSERT_TRUE(result) << result.description(); 
    Room room{ doc.child("Circle") };
    std::string c_dump_ref =
        R"(Circle "testCircle", x: 0, y: 1, r: 2, color: "Black"
)";
    EXPECT_EQ(room.dump(""), c_dump_ref);
}
