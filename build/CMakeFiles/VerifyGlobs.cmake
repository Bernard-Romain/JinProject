# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.29
cmake_policy(SET CMP0009 NEW)

# SOURCES at src/CMakeLists.txt:2 (file)
file(GLOB NEW_GLOB LIST_DIRECTORIES true "C:/Users/romai/Bureau/Cours/JIN/CAASI/src/*.cpp")
set(OLD_GLOB
  "C:/Users/romai/Bureau/Cours/JIN/CAASI/src/Door.cpp"
  "C:/Users/romai/Bureau/Cours/JIN/CAASI/src/Entity.cpp"
  "C:/Users/romai/Bureau/Cours/JIN/CAASI/src/Game.cpp"
  "C:/Users/romai/Bureau/Cours/JIN/CAASI/src/LivingEntity.cpp"
  "C:/Users/romai/Bureau/Cours/JIN/CAASI/src/Monster.cpp"
  "C:/Users/romai/Bureau/Cours/JIN/CAASI/src/MovingEntity.cpp"
  "C:/Users/romai/Bureau/Cours/JIN/CAASI/src/MovingStrategy.cpp"
  "C:/Users/romai/Bureau/Cours/JIN/CAASI/src/Player.cpp"
  "C:/Users/romai/Bureau/Cours/JIN/CAASI/src/Projectile.cpp"
  "C:/Users/romai/Bureau/Cours/JIN/CAASI/src/Room.cpp"
  "C:/Users/romai/Bureau/Cours/JIN/CAASI/src/Wall.cpp"
  "C:/Users/romai/Bureau/Cours/JIN/CAASI/src/myMain.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "C:/Users/romai/Bureau/Cours/JIN/CAASI/build/CMakeFiles/cmake.verify_globs")
endif()

# SOURCES at src/CMakeLists.txt:2 (file)
file(GLOB NEW_GLOB LIST_DIRECTORIES true "C:/Users/romai/Bureau/Cours/JIN/CAASI/src/*.h")
set(OLD_GLOB
  "C:/Users/romai/Bureau/Cours/JIN/CAASI/src/Door.h"
  "C:/Users/romai/Bureau/Cours/JIN/CAASI/src/Entity.h"
  "C:/Users/romai/Bureau/Cours/JIN/CAASI/src/Game.h"
  "C:/Users/romai/Bureau/Cours/JIN/CAASI/src/LivingEntity.h"
  "C:/Users/romai/Bureau/Cours/JIN/CAASI/src/Monster.h"
  "C:/Users/romai/Bureau/Cours/JIN/CAASI/src/MovingEntity.h"
  "C:/Users/romai/Bureau/Cours/JIN/CAASI/src/MovingStrategy.h"
  "C:/Users/romai/Bureau/Cours/JIN/CAASI/src/Player.h"
  "C:/Users/romai/Bureau/Cours/JIN/CAASI/src/Projectile.h"
  "C:/Users/romai/Bureau/Cours/JIN/CAASI/src/Room.h"
  "C:/Users/romai/Bureau/Cours/JIN/CAASI/src/Wall.h"
  "C:/Users/romai/Bureau/Cours/JIN/CAASI/src/myMain.h"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "C:/Users/romai/Bureau/Cours/JIN/CAASI/build/CMakeFiles/cmake.verify_globs")
endif()

# DYNAMIC_LIBS at mainLauncher/CMakeLists.txt:14 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "C:/Users/romai/Bureau/Cours/JIN/CAASI/lib_openal32//*.dll")
set(OLD_GLOB
  "C:/Users/romai/Bureau/Cours/JIN/CAASI/lib_openal32//x64/openal32.dll"
  "C:/Users/romai/Bureau/Cours/JIN/CAASI/lib_openal32//x86/openal32.dll"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "C:/Users/romai/Bureau/Cours/JIN/CAASI/build/CMakeFiles/cmake.verify_globs")
endif()
