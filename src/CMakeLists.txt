
file(GLOB SOURCES CONFIGURE_DEPENDS *.h *.cpp)

<<<<<<< HEAD
add_library(src ${SOURCES}  "Room.cpp" "Room.h")
=======
add_library(src ${SOURCES}  "Entity.h" "Entity.cpp")
>>>>>>> 1d12173c93f061c1d429b7defd9c6b5142f77294
target_include_directories(src PUBLIC ./)

target_link_libraries(src PUBLIC pugixml sfml-graphics)
