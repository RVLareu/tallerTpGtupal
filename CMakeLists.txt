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

add_subdirectory(libs/yamlcpp)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_SOURCE_DIR}/libs' como directorio de includes")
include_directories(${PROJECT_SOURCE_DIR}/libs)
include_directories(${SDL2PP_INCLUDE_DIRS})

include_directories(${YAML_CPP_INCLUDE_DIR})

add_executable (client
  src/client/client.cpp
  src/client/main.cpp
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
  src/server/blocking_queue.cpp  
  src/server/client.cpp  
    
  src/common/common_protocol.cpp
  src/common/common_socket.cpp
)

add_executable (server
  src/server/main.cpp
  src/server/server.cpp
  src/server/accept_thread.cpp
  src/server/client.cpp
  src/server/game.cpp
  src/server/board.cpp  
  src/server/blocking_queue.cpp  

  # PIEZAS
  src/server/piece.cpp
  src/server/rook.cpp
  src/server/bishop.cpp
  src/server/pawn.cpp
  src/server/king.cpp
  src/server/queen.cpp
  src/server/knight.cpp
  
  src/common/common_protocol.cpp
  src/common/common_socket.cpp
)

target_link_libraries(client ${SDL2PP_LIBRARIES})
target_link_libraries(client yaml-cpp)


file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
