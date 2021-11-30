cmake_minimum_required(VERSION 2.8)

project(sdl)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

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
  src/client/mainSdlHello.cpp
  src/client/renderpiece.cpp
  src/client/spot.cpp
  src/client/chessboard.cpp
  src/client/menu.cpp
  src/client/endScreen.cpp

  src/server/rook.cpp
  src/server/bishop.cpp
  src/server/pawn.cpp
  src/server/king.cpp
  src/server/queen.cpp
  src/server/piece.cpp
  src/server/board.cpp  
  src/server/knight.cpp
  src/server/game.cpp
    
  src/common/common_protocol.cpp
  src/common/common_socket.cpp
)

add_executable (server
  src/server/main.cpp

  src/server/rook.cpp
  src/server/bishop.cpp
  src/server/pawn.cpp
  src/server/king.cpp
  src/server/queen.cpp
  src/server/piece.cpp
  src/server/board.cpp  
  src/server/knight.cpp
  src/server/game.cpp
  
  src/common/common_protocol.cpp
  src/common/common_socket.cpp
)

target_link_libraries(sdlpp-hello ${SDL2PP_LIBRARIES})


file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
