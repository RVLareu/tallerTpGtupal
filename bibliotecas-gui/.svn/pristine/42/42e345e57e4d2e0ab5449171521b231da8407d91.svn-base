cmake_minimum_required(VERSION 2.8)

project(sdl)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if(APPLE)
  message("Estoy en OSX")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/local/include -L/usr/local/lib -lSDL2")
endif()

# Agrego la libreria SDL2pp habilitando manejo de imagenes y de letras
SET(SDL2PP_WITH_IMAGE YES)
SET(SDL2PP_WITH_TTF YES)
add_subdirectory(libs/libSDL2pp)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_SOURCE_DIR}/libs' como directorio de includes")
include_directories(${PROJECT_SOURCE_DIR}/libs)
include_directories(${SDL2PP_INCLUDE_DIRS})


add_executable (sdlpp-hello
  src/mainSdlHello.cpp  
)

add_executable (sdlpp-events
  src/mainSdlEvents.cpp
  src/Player.cpp
  src/Animation.cpp
)

target_link_libraries(sdlpp-hello ${SDL2PP_LIBRARIES})
target_link_libraries(sdlpp-events ${SDL2PP_LIBRARIES})

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
