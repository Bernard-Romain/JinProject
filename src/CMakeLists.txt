
file(GLOB SOURCES CONFIGURE_DEPENDS *.h *.cpp)

add_library(src ${SOURCES} "MovingEntity.cpp" "LivingEntity.h" "LivingEntity.cpp" "Monster.h" "Monster.cpp" "Player.h" "Player.cpp" "Projectile.h" "Projectile.cpp" "Wall.h" "Wall.cpp" "Door.h" "Door.cpp" "Game.h" "Game.cpp")
target_include_directories(src PUBLIC ./)

target_link_libraries(src PUBLIC pugixml sfml-graphics sfml-audio)
