# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/romai/Bureau/Cours/JIN/CAASI/build/_deps/pugixml-src"
  "C:/Users/romai/Bureau/Cours/JIN/CAASI/build/_deps/pugixml-build"
  "C:/Users/romai/Bureau/Cours/JIN/CAASI/build/_deps/pugixml-subbuild/pugixml-populate-prefix"
  "C:/Users/romai/Bureau/Cours/JIN/CAASI/build/_deps/pugixml-subbuild/pugixml-populate-prefix/tmp"
  "C:/Users/romai/Bureau/Cours/JIN/CAASI/build/_deps/pugixml-subbuild/pugixml-populate-prefix/src/pugixml-populate-stamp"
  "C:/Users/romai/Bureau/Cours/JIN/CAASI/build/_deps/pugixml-subbuild/pugixml-populate-prefix/src"
  "C:/Users/romai/Bureau/Cours/JIN/CAASI/build/_deps/pugixml-subbuild/pugixml-populate-prefix/src/pugixml-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/romai/Bureau/Cours/JIN/CAASI/build/_deps/pugixml-subbuild/pugixml-populate-prefix/src/pugixml-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/romai/Bureau/Cours/JIN/CAASI/build/_deps/pugixml-subbuild/pugixml-populate-prefix/src/pugixml-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
