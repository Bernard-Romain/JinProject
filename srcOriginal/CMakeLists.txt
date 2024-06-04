
file(GLOB SOURCES CONFIGURE_DEPENDS *.h *.cpp)

add_library(srcOriginal ${SOURCES} )
target_include_directories(srcOriginal PUBLIC ./)

target_link_libraries(srcOriginal PUBLIC pugixml sfml-graphics)
